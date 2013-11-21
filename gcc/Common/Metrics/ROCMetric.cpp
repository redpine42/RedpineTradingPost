#include "ROCMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getROC(const unsigned int size, CandleData * data, long numSticks)
{
	double roc = 0.0;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * rocDataOut = new double[numSticks + size];

	TA_RetCode rocRet =
		TA_ROC( 0,
			  numSticks - 1,
			  csData,
			  size,
			  &outBeg,
		      &outNbElement,
		      rocDataOut);

	if(outNbElement == 0)
	{
		roc = 0.0;
	}
	else
	{
		roc = rocDataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] rocDataOut;
	
	return roc;
}

double * getAllROC(const unsigned int size, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * rocDataOut = new double[arraySize];
	memset(rocDataOut,0,arraySize * sizeof(double));

	TA_RetCode emaRet =
		TA_ROC( 0,
			  numSticks - 1, 
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      rocDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],rocDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] rocDataOut;

	return ret;
}
