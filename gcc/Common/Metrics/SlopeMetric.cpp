#include "SlopeMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getSlope(const unsigned int size, CandleData * data, long numSticks)
{
	double slope = 0.0;

	if(numSticks >= size)
	{
		double * priceData = CandleData::getData(data, CandleData::CLOSE, size);

		int outNbElement = 0;
		int outBeg = 0;

		double * slopeDataOut = new double[1];

		TA_RetCode retCodeSlope =  
			TA_LINEARREG_SLOPE(0, 
			                   size-1,
                               priceData,
                               size,
                               &outBeg,
                               &outNbElement,
                               slopeDataOut);
		slope = slopeDataOut[0];

		delete [] priceData;
		delete [] slopeDataOut;
	}
	return slope;
}

double * getAllSlope(const unsigned int size, CandleData * data, long numSticks)
{
	double atr = 0.0;

	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * slopeDataOut = new double[arraySize];
	memset(slopeDataOut,0,arraySize * sizeof(double));

	TA_RetCode retCodeSlope =  
			TA_LINEARREG_SLOPE(0, 
  	                   numSticks-1,
                        closeData,
                        size,
                        &outBeg,
                        &outNbElement,
                        slopeDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],slopeDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] slopeDataOut;

	return ret;
}


double getSlopeVal(const unsigned int size, CandleData * data, long numSticks)
{
	double slope = 0.0;
	if(numSticks >= size)
	{
		double * priceData = CandleData::getData(data, CandleData::CLOSE, size);

		int outNbElement = 0;
		int outBeg = 0;

		double * slopeDataOut = new double[1];

		TA_RetCode retCodeSlope =  
			TA_LINEARREG(0, 
			                   size-1,
                               priceData,
                               size,
                               &outBeg,
                               &outNbElement,
                               slopeDataOut);
		slope = slopeDataOut[0];

		delete [] priceData;
		delete [] slopeDataOut;
	}
	return slope;
}

double * getAllSlopeVal(const unsigned int size, CandleData * data, long numSticks)
{
	double atr = 0.0;

	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * slopeDataOut = new double[arraySize];
	memset(slopeDataOut,0,arraySize * sizeof(double));

	TA_RetCode retCodeSlope =  
			TA_LINEARREG(0, 
  	                   numSticks-1,
                        closeData,
                        size,
                        &outBeg,
                        &outNbElement,
                        slopeDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],slopeDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] slopeDataOut;

	return ret;
}

