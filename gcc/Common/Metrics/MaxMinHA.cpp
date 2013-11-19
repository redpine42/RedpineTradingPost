#include "MaxMinHA.h"
#include "CandleStickManager.h"
#include "ta_libc.h"

double getMaxHA(const std::string & symbol, const int unsigned size)
{
	double max = 99999.0;
	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * csData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::HIGH, numSticks);
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

double getMinHA(const std::string & symbol, const int unsigned size)
{
	double min = -99999.0;

	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * csData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::LOW, numSticks);
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

double * getAllMaxHA(const std::string & symbol, const int unsigned size)
{
	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * csData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::HIGH, numSticks);
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

double * getAllMinHA(const std::string & symbol, const int unsigned size)
{
	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * csData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::LOW, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * minDataOut = new double[arraySize];
	memset(minDataOut,0,arraySize * sizeof(double));


	TA_RetCode taret =
		TA_MIN( 0,
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
