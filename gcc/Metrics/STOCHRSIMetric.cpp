#include "STOCHRSIMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

void getStochRSI(const int unsigned period,
				 const int unsigned kSize, 
				 const int unsigned dSize,
				 double & stochK,
				 double & stochD, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * stochKDataOut = new double[numSticks + kSize];
	double * stochDDataOut = new double[numSticks + kSize];


	TA_RetCode stochRet =
			TA_STOCHRSI(0,
                      numSticks -1,
                      closeData,
					  period,
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
		stochD = 0.0;
	}
	else
	{
		stochK = stochKDataOut[outNbElement - 1];
		stochD = stochDDataOut[outNbElement - 1];
	}

	delete [] closeData;
	delete [] stochKDataOut;
	delete [] stochDDataOut;
}

void getAllStochRSI(const int unsigned period,
				 const int unsigned kSize, 
				 const int unsigned dSize,
				 double *& kData,
				 double *& dData, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + kSize;
	double * stochKDataOut = new double[arraySize];
	double * stochDDataOut = new double[arraySize];
	memset(stochKDataOut,0,arraySize * sizeof(double));
	memset(stochDDataOut,0,arraySize * sizeof(double));

	TA_RetCode stochRet =
			TA_STOCHRSI(0,
                      numSticks -1,
                      closeData,
					  period,
                      kSize, /* From 1 to 100000 */
                      dSize, /* From 1 to 100000 */
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      stochKDataOut,
                      stochDDataOut);

	kData = new double[arraySize + outBeg];
	dData = new double[arraySize + outBeg];
	memset(kData,0,(arraySize + outBeg) * sizeof(double));
	memset(dData,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&kData[outBeg],stochKDataOut,arraySize*sizeof(double));
	memcpy(&dData[outBeg],stochDDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] stochDDataOut;
	delete [] stochKDataOut;

}
