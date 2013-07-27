#include "MACDMetric.h"
#include "CandleData.h"
#include "ta_libc.h"

#include <iostream>


bool MACD3DropExit(CandleData * data, long numSticks)
{
	int fast = 12;
	int slow = 26;
	int period = 9;
	int numHist = 4;

	bool drop = false;

	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * outMACD = new double[numSticks + fast];
	double * outMACDSignal = new double[numSticks + fast];
	double * outMACDHist = new double[numSticks + fast];

	TA_RetCode ret = TA_MACD(0,
							 numSticks - 1,
							 closeData,
							 fast,
							 slow,
							 period,
							 &outBeg,
							 &outNbElement,
							 outMACD,
							 outMACDSignal,
						     outMACDHist);


	if(outNbElement >= 4)
	{
		int i = outNbElement - 4;
		double histVal = outMACDHist[i++];
		for(; i < outNbElement; ++i)
		{
			if(histVal > outMACDHist[i])
			{
				drop = true;
				histVal = outMACDHist[i];
			}
			else
			{
				drop = false;
				break;
			}
		}
	}

	delete [] closeData;
	delete [] outMACD;
	delete [] outMACDSignal;
	delete [] outMACDHist;

	return drop;
}

bool MACD3RiseExit(CandleData * data, long numSticks)
{
	int fast = 12;
	int slow = 26;
	int period = 9;
	int numHist = 4;

	int candleSize = slow + numHist + 7;

	bool rise = false;

	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * outMACD = new double[numSticks + fast];
	double * outMACDSignal = new double[numSticks + fast];
	double * outMACDHist = new double[numSticks + fast];

	TA_RetCode ret = TA_MACD(0,
							 numSticks - 1,
							 closeData,
							 fast,
							 slow,
							 period,
							 &outBeg,
							 &outNbElement,
							 outMACD,
							 outMACDSignal,
						     outMACDHist);


	if(outNbElement >= 4)
	{
		int i = outNbElement - 4;
		double histVal = outMACDHist[i++];
		for(; i < outNbElement; ++i)
		{
			if(histVal < outMACDHist[i])
			{
				rise = true;
				histVal = outMACDHist[i];
			}
			else
			{
				rise = false;
				break;
			}
		}
	}

	delete [] closeData;
	delete [] outMACD;
	delete [] outMACDSignal;
	delete [] outMACDHist;

	return rise;
}

double getMACDHist(const int unsigned fast, const int unsigned slow, const int unsigned period, CandleData * data, long numSticks)
{
	double macdHist = 0.0;
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * outMACD = new double[numSticks + fast];
	double * outMACDSignal = new double[numSticks + fast];
	double * outMACDHist = new double[numSticks + fast];

	TA_RetCode ret = TA_MACD(0,
							 numSticks - 1,
							 closeData,
							 fast,
							 slow,
							 period,
							 &outBeg,
							 &outNbElement,
							 outMACD,
							 outMACDSignal,
						     outMACDHist);


	if(outNbElement == 0)
	{
		macdHist = 0.0;
	}
	else
	{
		macdHist = outMACDHist[outNbElement - 1];
	}

	delete [] closeData;
	delete [] outMACD;
	delete [] outMACDSignal;
	delete [] outMACDHist;

	return macdHist;
}

double * getAllMACDHist(const int unsigned fast, const int unsigned slow, const int unsigned period, CandleData * data, long numSticks)
{
	double macdHist = 0.0;
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + fast;

	double * outMACD = new double[arraySize];
	memset(outMACD,0,arraySize * sizeof(double));
	double * outMACDSignal = new double[arraySize];
	memset(outMACDSignal,0,arraySize * sizeof(double));
	double * outMACDHist = new double[arraySize];
	memset(outMACDHist,0,arraySize * sizeof(double));

	TA_RetCode macdRet = TA_MACD(0,
							 numSticks - 1,
							 closeData,
							 fast,
							 slow,
							 period,
							 &outBeg,
							 &outNbElement,
							 outMACD,
							 outMACDSignal,
						     outMACDHist);


	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],outMACDHist,arraySize*sizeof(double));

	delete [] closeData;
	delete [] outMACD;
	delete [] outMACDSignal;
	delete [] outMACDHist;

	return ret;
}
