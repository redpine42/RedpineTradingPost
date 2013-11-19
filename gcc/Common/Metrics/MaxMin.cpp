#include "MaxMin.h"
#include "CandleData.h"
#include "ta_libc.h"

double getMax(const int unsigned size, CandleData * data, long numSticks)
{
	double max = 99999.0;

	double * csData = CandleData::getData(data, CandleData::HIGH, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * maxDataOut = new double[numSticks + size];

	TA_RetCode taret =
			TA_MAX( 0,
				  numSticks - 1,
				  csData,
				  size,
				  &outBeg,
			      &outNbElement,
				  maxDataOut);

	if(outNbElement != 0)
	{
		max = maxDataOut[outNbElement - 1];
	}


	delete [] csData;
	delete [] maxDataOut;

	return max;
}

double getMin(const int unsigned size, CandleData * data, long numSticks)
{
	double min = -99999.0;

	double * csData = CandleData::getData(data, CandleData::LOW, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * minDataOut = new double[numSticks + size];

	TA_RetCode taret =
			TA_MIN( 0,
				  numSticks - 1,
				  csData,
				  size,
				  &outBeg,
			      &outNbElement,
				  minDataOut);

	if(outNbElement != 0)
	{
		min = minDataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] minDataOut;

	return min;
}

double * getAllMax(const int unsigned size, CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::HIGH, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * maxDataOut = new double[arraySize];
	memset(maxDataOut,0,arraySize * sizeof(double));

	TA_RetCode taret =
		TA_MAX( 0,
			  numSticks - 1,
			  csData,
			  size,
			  &outBeg,
		      &outNbElement,
			  maxDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],maxDataOut,arraySize*sizeof(double));

	delete [] csData;
	delete [] maxDataOut;

	return ret;
}

double * getAllMin(const int unsigned size, CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::LOW, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * minDataOut = new double[arraySize];
	memset(minDataOut,0,arraySize * sizeof(double));


	TA_RetCode taret =
		TA_MAX( 0,
			  numSticks - 1,
			  csData,
			  size,
			  &outBeg,
		      &outNbElement,
			  minDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],minDataOut,arraySize*sizeof(double));

	delete [] csData;
	delete [] minDataOut;
	return ret;
}
