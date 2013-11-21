#include "MinusDIMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getMinusDI(const unsigned int size, CandleData * data, long numSticks)
{
	double MinusDI = 0.0;
	double * highData = CandleData::getData(data,CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * MinusDIDataOut = new double[numSticks + size];

	TA_RetCode MinusDIRet =
		TA_MINUS_DI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
				  MinusDIDataOut);

	if(outNbElement == 0)
	{
		MinusDI = 0.0;
	}
	else
	{
		MinusDI = MinusDIDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] MinusDIDataOut;

	return MinusDI;
}

double * getAllMinusDI(const int unsigned size, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * MinusDIDataOut = new double[arraySize];
	memset(MinusDIDataOut,0,arraySize * sizeof(double));

	TA_RetCode MinusDIRet =
		TA_MINUS_DI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
				  MinusDIDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],MinusDIDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] MinusDIDataOut;

	return ret;
}

