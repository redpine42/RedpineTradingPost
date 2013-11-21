#include "STOCHMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getStochK(const unsigned int kSize, const unsigned int dSize, CandleData * data, long numSticks)
{
	double stochK = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * stochKDataOut = new double[numSticks + kSize];
	double * stochDDataOut = new double[numSticks + kSize];


	TA_RetCode stochRet =
			TA_STOCHF(0,
                      numSticks -1,
                      highData,
                      lowData,
                      closeData,
                      kSize, /* From 1 to 100000 */
                      dSize, /* From 1 to 100000 */
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      stochKDataOut,
                      stochDDataOut );

	if(outNbElement == 0)
	{
		stochK = 0.0;
	}
	else
	{
		stochK = stochKDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] stochKDataOut;
	delete [] stochDDataOut;

	return stochK;
}

double * getAllStochK(const int unsigned kSize, const int unsigned dSize, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + kSize;
	double * stochKDataOut = new double[arraySize];
	double * stochDDataOut = new double[arraySize];
	memset(stochKDataOut,0,arraySize * sizeof(double));
	memset(stochDDataOut,0,arraySize * sizeof(double));

	TA_RetCode stochRet =
			TA_STOCHF(0,
                      numSticks -1,
                      highData,
                      lowData,
                      closeData,
                      kSize, /* From 1 to 100000 */
                      dSize, /* From 1 to 100000 */
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      stochKDataOut,
                      stochDDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],stochKDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] stochDDataOut;
	delete [] stochKDataOut;

	return ret;
}

double getStoch(const int unsigned kSize, const int unsigned kSlowSize, const int unsigned dSize, CandleData * data, long numSticks)
{
	double stoch = 0.0;
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * stochKDataOut = new double[numSticks + kSize];
	double * stochDDataOut = new double[numSticks + kSize];


	TA_RetCode stochRet =
			TA_STOCH(0,
                      numSticks -1,
                      highData,
                      lowData,
                      closeData,
                      kSize, /* From 1 to 100000 */
                      kSlowSize, /* From 1 to 100000 */
                      TA_MAType_SMA,
					  dSize,
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      stochKDataOut,
                      stochDDataOut );

	if(outNbElement == 0)
	{
		stoch = 0.0;
	}
	else
	{
		stoch = stochKDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] stochKDataOut;
	delete [] stochDDataOut;

	return stoch;
}
double * getAllStoch(const int unsigned kSize, const int unsigned kSlowSize, const int unsigned dSize, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + kSize;
	double * stochKDataOut = new double[arraySize];
	double * stochDDataOut = new double[arraySize];
	memset(stochKDataOut,0,arraySize * sizeof(double));
	memset(stochDDataOut,0,arraySize * sizeof(double));

	TA_RetCode stochRet =
			TA_STOCH(0,
                      numSticks -1,
                      highData,
                      lowData,
                      closeData,
                      kSize, /* From 1 to 100000 */
                      kSlowSize, /* From 1 to 100000 */
                      TA_MAType_SMA,
					  dSize,
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      stochKDataOut,
                      stochDDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],stochKDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] stochDDataOut;
	delete [] stochKDataOut;

	return ret;
}
