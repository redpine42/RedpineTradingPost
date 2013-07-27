#include "ATRMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


double getATR(const unsigned int size, CandleData * data, long numSticks)
{
	double atr = 0.0;

	double * highData = 0;
	double * lowData = 0;
	double * closeData = 0;

	highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	closeData = CandleData::getData( data, CandleData::CLOSE,numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * atrDataOut = new double[numSticks + size];

	TA_RetCode atrRet =
		TA_ATR( 0,
			  numSticks - 1,
			  highData,
			  lowData,
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      atrDataOut);

	if(outNbElement == 0)
	{
		atr = 0.0;
	}
	else
	{
		atr = atrDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] atrDataOut;
	
	return atr;
}

double * getAllATR(const unsigned int size, CandleData * data, long numSticks)
{
	double * highData = 0;
	double * lowData = 0;
	double * closeData = 0;

	highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * atrDataOut = new double[arraySize];
	memset(atrDataOut,0,arraySize * sizeof(double));

	TA_RetCode atrRet =
		TA_ATR(0,
			  numSticks -1,
			  highData,
			  lowData,
			  closeData,
			  size,
			  &outBeg,
		      &outNbElement,
		      atrDataOut);  // Not a defect  ATR takes size +1 to get result

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],atrDataOut,outNbElement*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] atrDataOut;

	return ret;
}

