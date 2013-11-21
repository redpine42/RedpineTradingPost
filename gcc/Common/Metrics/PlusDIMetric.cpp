#include "PlusDIMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getPlusDI(const unsigned int size, CandleData * data, long numSticks)
{
	double PlusDI = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * PlusDIDataOut = new double[numSticks+size];

	TA_RetCode PlusDIRet =
			TA_PLUS_DI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      PlusDIDataOut);

	if(outNbElement == 0)
	{
		PlusDI = 0.0;
	}
	else
	{
		PlusDI = PlusDIDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] PlusDIDataOut;

	return PlusDI;
}

double * getAllPlusDI(const int unsigned size, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * PlusDIDataOut = new double[arraySize];
	memset(PlusDIDataOut,0,arraySize * sizeof(double));

	TA_RetCode PlusDIRet =
			TA_PLUS_DI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      PlusDIDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],PlusDIDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] PlusDIDataOut;

	return ret;
}

