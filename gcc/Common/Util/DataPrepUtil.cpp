#include "DataPrepUtil.h"
#include <math.h>
//#include "MySQLLayer.h"

DataPrepUtil * DataPrepUtil::instance_ = 0;

DataPrepUtil * DataPrepUtil::instance()
{
	if(0 == instance_)
	{
		instance_ = new DataPrepUtil();
	}
	return instance_;
}

void DataPrepUtil::removeInstance()
{
	if(0 != instance_)
	{
		delete instance_;
		instance_ = 0;
	}
}

DataPrepUtil::DataPrepUtil(void)
{
//	MySQLLayer::instance()->getNormalParams(normMap_);
}

DataPrepUtil::~DataPrepUtil(void)
{
}


void DataPrepUtil::normalizeData(double *data, unsigned long length, std::string id)
{
	double mean = 0.0;
	double stdDev = 0.0;
	double confNZ = 0.0;

	NormMapIter iter;
	iter = normMap_.find(id);
	if(iter == normMap_.end())
	{
		double sum = 0.0;
		double sumSq = 0.0;
		for(unsigned int i = 0; i < length; ++i)
		{
			sum += data[i];
			sumSq += data[i] * data[i];
		}
		mean = sum/length;
		stdDev = StdDev(length, sum, sumSq);
		confNZ = NZ(.95);

		normMap_[id] = NormData(mean,stdDev,confNZ);
//		MySQLLayer::instance()->addNormalParams(id, mean, stdDev, confNZ);
	}
	else
	{
		mean = (*iter).second.mean_;
		stdDev = (*iter).second.stdDev_;
		confNZ = (*iter).second.confNZ_;
	}
	for(unsigned int j = 0; j < length; ++j)
	{
		double normVal = SoftMaxScale(data[j], mean, stdDev, confNZ);
		data[j] = normVal;
	}
}


double DataPrepUtil::SoftMaxUnScale(
    double      SquashedVal,
    double      Mean,
    double      StdDev,
    double      ConfNZ)
{
    double      Val;

    Val = 1.;
    if (SquashedVal < 1.) {
        Val = Mean + (( ConfNZ*StdDev*log(sqrt(-1.+(1./(1.-SquashedVal)))) ) / 3.14159265 );
    }
    return Val;
}
double DataPrepUtil::SoftMaxScale(
    double      Val,
    double      Mean,
    double      StdDev,
    double      ConfNZ)
{
    double      K;
    double      twoPi = 2. * 3.14159265;

    K = (Val - Mean) / (ConfNZ * ( StdDev / twoPi ));

    return 1. / ( 1. + exp(-K) );
}
// Returns z given normally distributed probability **

double DataPrepUtil::NZ(
    double      YPR)
{
    long        Done, InLimit;
    double      EETol, ErrTol;
    double      S2PI, ETol;
    double      Y1, Y2, Y3, YA, YP1, YP2, YP3, YIU, YK;
    long        YIP;
    double      Z, Z1, ZB, ZCD, ZJ, ZT, ZZ;

    S2PI   = 2.5066282746; // Sqrt(2*PI())
    ErrTol = 0.000005;
    ETol   = ErrTol * S2PI;
  
    if (YPR < 0.01) YPR = 0.01;
    if (YPR > 0.99) YPR = 0.99;

    YIP = 0;
    if (YPR < .5) {
        YPR = 1. - YPR;
        YIP = 1;
    } else
    if (YPR == .5) {
        return 0.;
    }

    Y1  = 0;
    YP1 = 0.5;
    YIU = 2.;
    Y2  = 1.;
    YP2 = .84134474607;
    YK  = (Y2-Y1)/(log(1./YP1-1.)-log(1./YP2-1.));
    YA  = Y2 + YK * log(1./YP2-1.);
    Y3  = YA - YK * log(1./YPR-1.);

    Done = 0;
    while (!Done) {
        ZCD = 0;
        Z   = Y3;
        ZZ  = Z * Z;
        if (fabs(Z) >= 2.) {
            ZB = 1.;
            Z1 = 1.;
            ZT = 1.;
            ZJ = 1.;
            EETol = Z * ETol * exp(ZZ/2.);
            InLimit = 0;
            while (!InLimit) {
                ZB = 1. / ( 1. + ZJ * ZB / ZZ );
                Z1 = ( ZB - 1. ) * Z1;
                ZT = ZT + Z1;
                if (fabs(Z1) > EETol) {
                    ZJ = ZJ + 1.;
                } else {
                    InLimit = 1;
                }
            }
            ZCD = 1. - ZT * exp( - ZZ / 2. ) / ( S2PI * Z );
        } else {
            Z1 = Z;
            ZT = Z1;
            ZJ = 1.;
            InLimit = 0;
            while (!InLimit) {
                Z1 = - Z1 * ZZ * ( 2.*ZJ - 1. ) / ( 2.*ZJ * ( 2.*ZJ + 1. ) );
                ZT = ZT + Z1;
                if (fabs(Z1) > ETol) {
                    ZJ = ZJ + 1.;
                } else {
                    InLimit = 1;
                }
            }
            ZCD = .5 + ZT / S2PI;
        }
        YP3 = ZCD;
        if (fabs(YP3 - YPR) < ErrTol) {
            Done = 1;
        }
        if (!Done) {
            if (YP3 > 1. - ErrTol && YIU == 1.) {
                Y3 = Y3 - (Y3 - Y1) / 2.;
            } else
            if (YP3 > 1. - ErrTol && YIU == 2.) {
                Y3 = Y3 - (Y3 - Y2) / 2.;
            } else
            if (YP3 < .5 + ErrTol && YIU == 1.) {
                Y3 = Y3 - (Y3 - Y2) / 2.;
            } else
            if (YP3 < .5 - ErrTol && YIU == 2.) {
                Y3 = Y3 - (Y3 - Y1) / 2.;
            }

            if (fabs(YPR-YP1) < fabs(YPR-YP2)) {
                YP2 = YP3;
                Y2  = Y3;
                YIU = 2.;
            } else {
                YP1 = YP3;
                Y1  = Y3;
                YIU = 1.;
            }
            YK = (Y2-Y1)/(log(1./YP1-1.)-log(1./YP2-1.));
            YA = Y2 + YK * log(1./YP2-1.);
            Y3 = YA - YK * log(1./YPR-1.);
        }

    } // while !Done

    return YIP == 0 ? Y3 : -Y3;
}
double DataPrepUtil::StdDev(
    double      pN,     // Number
    double      pSx,    // Sum
    double      pSxSq)  // Sum of Squares
{
    double      lnMean;

    if (pN > 1) {
        lnMean = pSx/pN;
        return sqrt( (pSxSq - (pN*lnMean*lnMean)) / (pN-1.) );
    }
    return 0.;
}

void DataPrepUtil::denormalizeData(double data, std::string & id)
{
	NormMapIter iter;
	iter = normMap_.find(id);
	if(iter != normMap_.end())
	{
		double mean = (*iter).second.mean_;
		double stdDev = (*iter).second.stdDev_;
		double confNZ = (*iter).second.confNZ_;

		data = SoftMaxUnScale(data,mean,stdDev,confNZ);
	}
	else
	{
		data = 0.0;
	}
}


void DataPrepUtil::fannNormalize(double * data, unsigned long dataSize, double minVal, double maxVal)
{
	double max = data[0];
	double min = data[0];
	unsigned long i = 0;
	for(i = 0; i < dataSize; ++i)
	{
		if(data[i] > max)
		{
			max = data[i];
		}
		else if (data[i] < min)
		{
			min = data[i];
		}
	}
    for(i = 0; i < dataSize; ++i)
	{
			data[i]= (((maxVal-minVal)*(data[i]-min))/(max-min))+minVal;
    }
}
