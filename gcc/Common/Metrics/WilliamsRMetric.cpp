#include "WilliamsRMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


double getWilliamsR(const unsigned int size, CandleData * data, long numSticks)
{
	double WilliamsR = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * WilliamsRDataOut = new double[numSticks+size];

	TA_RetCode WilliamsRRet =
			TA_WILLR( 0,
				  numSticks-1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      WilliamsRDataOut);

	if(outNbElement == 0)
	{
		WilliamsR = 0.0;
	}
	else
	{
		WilliamsR = WilliamsRDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] WilliamsRDataOut;

	return WilliamsR;
}

double * getAllWilliamsR(const int unsigned size, CandleData * data, long numSticks)
{
	double WilliamsR = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * WilliamsRDataOut = new double[arraySize];
	memset(WilliamsRDataOut,0,arraySize * sizeof(double));

	TA_RetCode WilliamsRRet =
			TA_WILLR( 0,
				  numSticks-1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      WilliamsRDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],WilliamsRDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] WilliamsRDataOut;

	return ret;
}
