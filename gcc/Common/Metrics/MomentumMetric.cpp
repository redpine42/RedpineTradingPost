#include "MomentumMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getMomentum(const unsigned int size, CandleData * data, long numSticks)
{
	double Momentum = 0.0;
	double * priceData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * MomentumData = new double[numSticks + size];

	TA_RetCode retCodeMomentum =  
			TA_MOM(0, 
                   numSticks-1,
                   priceData,
                   size,
                   &outBeg,
                   &outNbElement,
                   MomentumData);
	if(outNbElement == 0)
	{
		Momentum = 0.0;
	}
	else
	{
		Momentum = MomentumData[outNbElement - 1];
	}
	delete [] priceData;
	delete [] MomentumData;
	return Momentum;
}

double * getAllMomentum(const int unsigned size, CandleData * data, long numSticks)
{
	double * priceData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * MomentumData = new double[arraySize];
	memset(MomentumData,0,arraySize * sizeof(double));

	TA_RetCode retCodeMomentum =  
			TA_MOM(0, 
                   numSticks-1,
                   priceData,
                   size,
                   &outBeg,
                   &outNbElement,
                   MomentumData);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],MomentumData,arraySize*sizeof(double));

	delete [] priceData;
	delete [] MomentumData;

	return ret;
}
