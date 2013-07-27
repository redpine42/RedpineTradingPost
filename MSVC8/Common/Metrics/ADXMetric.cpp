#include "ADXMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


double getADX(const int unsigned size, CandleData * data, long numSticks)
{
	double adx = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * adxDataOut = new double[numSticks + 2*size];

	TA_RetCode adxRet =
		TA_ADX( 0,
			  numSticks - 1,
			  highData,
			  lowData,
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      adxDataOut);

	if(outNbElement == 0)
	{
		adx = 0.0;
	}
	else
	{
		adx = adxDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] adxDataOut;

	return adx;
}

double * getAllADX(const int unsigned size, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * adxDataOut = new double[arraySize];
	memset(adxDataOut,0,arraySize * sizeof(double));

	TA_RetCode adxRet =
		TA_ADX( 0,
			  numSticks - 1,
			  highData,
			  lowData,
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      adxDataOut);


	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],adxDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] adxDataOut;

	return ret;
}