#include "ATRMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


double getPSAR(const double acceleration, const double maximum, CandleData * data, long numSticks)
{
	double psar = 0.0;

	double * highData = 0;
	double * lowData = 0;
	highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	lowData = CandleData::getData(data, CandleData::LOW, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * psarDataOut = new double[numSticks];

	TA_RetCode ret =
		TA_SAR( 0,
			  numSticks - 1,
			  highData,
			  lowData,
			  acceleration,
			  maximum,
			  &outBeg,
		      &outNbElement,
		      psarDataOut);

	if(outNbElement == 0)
	{
		psar = 0.0;
	}
	else
	{
		psar = psarDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] psarDataOut;
	
	return psar;
}

double * getAllPSAR(const double acceleration, const double maximum, CandleData * data, long numSticks)
{
	double * highData = 0;
	double * lowData = 0;

	highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	lowData = CandleData::getData(data, CandleData::LOW, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * psarDataOut = new double[numSticks];
	memset(psarDataOut,0,numSticks * sizeof(double));

	TA_RetCode atrRet =
		TA_SAR(0,
			  numSticks - 1,
			  highData,
			  lowData,
			  acceleration,
			  maximum,
			  &outBeg,
		      &outNbElement,
		      psarDataOut);

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],psarDataOut,outNbElement*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] psarDataOut;

	return ret;
}

