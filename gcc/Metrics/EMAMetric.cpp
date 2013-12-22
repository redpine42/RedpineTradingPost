#include "EMAMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getEMA(const unsigned int size, CandleData * data, long numSticks)
{
	double mva = 0.0;

	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * mvaDataOut = new double[numSticks + size];

	TA_RetCode atrRet =
		TA_EMA( 0,
			  numSticks - 1,
			  csData,
			  size,
			  &outBeg,
		      &outNbElement,
		      mvaDataOut);

	if(outNbElement == 0)
	{
		mva = 0.0;
	}
	else
	{
		mva = mvaDataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] mvaDataOut;
	
	return mva;
}

double * getAllEMA(const unsigned int size, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * emaDataOut = new double[arraySize];
	memset(emaDataOut,0,arraySize * sizeof(double));

	TA_RetCode emaRet =
		TA_EMA( 0,
			  numSticks - 1, 
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      emaDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],emaDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] emaDataOut;

	return ret;
}
