#include "BBandsHA.h"
#include "CandleStickManager.h"
#include "ta_func.h"

void getBBandsHA(const std::string & symbol, 
				   const int unsigned size, 
				   const double stdHigh, 
				   const double stdLow,
				   double & high,
				   double & low,
				   double & medium)
{
	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * closeData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * highDataOut = new double[numSticks + size];
	double * lowDataOut = new double[numSticks + size];
	double * mediumDataOut = new double[numSticks + size];


	TA_RetCode bBandRet =
			TA_BBANDS(0,
                      numSticks -1,
                      closeData,
					  size,
                      stdHigh, /* From 1 to 100000 */
                      stdLow, /* From 1 to 100000 */
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      highDataOut,
                      mediumDataOut,
					  lowDataOut);

	if(outNbElement == 0)
	{
		high = 0.0;
		medium = 0.0;
		low = 0.0;
	}
	else
	{
		high = highDataOut[outNbElement - 1];
		medium = mediumDataOut[outNbElement - 1];
		low = lowDataOut[outNbElement - 1];
	}

	delete [] closeData;
	delete [] mediumDataOut;
	delete [] lowDataOut;
	delete [] highDataOut;
}

void getAllBBandsHA(const std::string & symbol, 
						const int unsigned size, 
						const double stdHigh, 
						const double stdLow,
						double *& high,
						double *& low,
						double *& medium)
{
	int numSticks = CandleStickManager::instance(-1)->numSticks(symbol);

	double * closeData = CandleStickManager::instance(-1)->getData(symbol, CandleStick::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * highDataOut = new double[arraySize];
	double * lowDataOut = new double[arraySize];
	double * mediumDataOut = new double[arraySize];
	memset(highDataOut,0,arraySize * sizeof(double));
	memset(lowDataOut,0,arraySize * sizeof(double));
	memset(mediumDataOut,0,arraySize * sizeof(double));

	TA_RetCode bBandRet =
			TA_BBANDS(0,
                      numSticks -1,
                      closeData,
					  size,
                      stdHigh, /* From 1 to 100000 */
                      stdLow, /* From 1 to 100000 */
                      TA_MAType_SMA,
                      &outBeg,
                      &outNbElement,
                      highDataOut,
                      mediumDataOut,
					  lowDataOut);


	high = new double[arraySize + outBeg];
	low = new double[arraySize + outBeg];
	medium = new double[arraySize + outBeg];
	memset(high,0,(arraySize + outBeg) * sizeof(double));
	memset(low,0,(arraySize + outBeg) * sizeof(double));
	memset(medium,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&high[outBeg],highDataOut,arraySize*sizeof(double));
	memcpy(&low[outBeg],lowDataOut,arraySize*sizeof(double));
	memcpy(&medium[outBeg],mediumDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] lowDataOut;
	delete [] mediumDataOut;
	delete [] highDataOut;
}

