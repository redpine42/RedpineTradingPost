#include "RSIMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


double getRSI(const unsigned int size, CandleData * data, long numSticks)
{
	double rsi = 0.0;
	double * priceData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * rsiData = new double[numSticks+size];

	TA_RetCode retCodeSlope =  
			TA_RSI(0, 
	               numSticks-1,
                   priceData,
                   size,
                   &outBeg,
                   &outNbElement,
                   rsiData);

	if(outNbElement == 0)
	{
		rsi = 0.0;
	}
	else
	{
		rsi = rsiData[outNbElement - 1];
	}

	delete [] priceData;
	delete [] rsiData;
	
	return rsi;
}

double * getAllRSI(const int unsigned size, CandleData * data, long numSticks)
{
	double * priceData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * rsiData = new double[arraySize];
	memset(rsiData,0,arraySize * sizeof(double));

	TA_RetCode retCodeSlope =  
			TA_RSI(0, 
	               numSticks-1,
                   priceData,
                   size,
                   &outBeg,
                   &outNbElement,
                   rsiData);

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],rsiData,outNbElement*sizeof(double));

	delete [] priceData;
	delete [] rsiData;
	
	return ret;
}
