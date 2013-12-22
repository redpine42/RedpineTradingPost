#include "MVAMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getMVA(const unsigned int size, CandleData * data, long numSticks)
{
	double mva = 0.0;
	double * csData = 0;
	csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * mvaDataOut = new double[numSticks + size];

	TA_RetCode atrRet =
			TA_MA( 0,
				  numSticks - 1,
				  csData,
				  size,
				  TA_MAType_SMA, //SMA
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

double * getAllMVA(const int unsigned size, CandleData * data, long numSticks)
{
	double * csData = 0;
	csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * mvaDataOut = new double[arraySize];
	memset(mvaDataOut,0,arraySize * sizeof(double));

	TA_RetCode atrRet =
			TA_MA( 0,
				  numSticks - 1,
				  csData,
				  size,
				  TA_MAType_SMA, //SMA
				  &outBeg,
			      &outNbElement,
			      mvaDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],mvaDataOut,arraySize*sizeof(double));

	delete [] csData;
	delete [] mvaDataOut;

	return ret;
}

