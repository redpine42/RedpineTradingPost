#include "CorrSlopeMetric.h"
#include "CorrelationMetric.h"
#include "SlopeMetric.h"
#include "CandleStickManager.h"
#include "CandleStickManagerFactory.h"
#include "ta_libc.h"

CorrSlope getCorrSlope(const std::string & symbol1, const std::string & symbol2, const int unsigned slopeBars, const int unsigned corrSize)
{
	CorrSlope data;
	data.corr_ = 0.0;
	data.slope_ = 0.0;

	CandleStickManager * csm = CandleStickManagerFactory::instance()->getManager(3600);
	int numSticks = csm->numSticks(symbol1);

	double * closeData1 = 0;
	double * closeData2 = 0;
	csm->getAlignedData(symbol1, symbol2, closeData1, closeData2, CandleStick::CLOSE, numSticks);

	data.corr_ = getCorrelation(closeData1, closeData2, numSticks, corrSize);

	delete [] closeData1;
	delete [] closeData2;

	data.slope_ = getSlope(symbol2, slopeBars);

	return data;
}

CorrSlope * getAllCorrSlope(const std::string & symbol1, const std::string & symbol2, const int unsigned slopeBars, const int unsigned corrSize)
{
	CandleStickManager * csm = CandleStickManagerFactory::instance()->getManager(3600);
	int numSticks = csm->numSticks(symbol1);

	double * closeData1 = 0;
	double * closeData2 = 0;
	csm->getAlignedData(symbol1, symbol2, closeData1, closeData2, CandleStick::CLOSE, numSticks);

	int arraySize = numSticks + corrSize;
	CorrSlope * corrDataArray = new CorrSlope[arraySize];
	memset(corrDataArray,0,arraySize * sizeof(CorrSlope));

	double * corrDataOut = getAllCorrelation(closeData1, closeData2, numSticks, corrSize);
	double * slopeDataOut = getAllSlope(symbol2, slopeBars);

	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = 1.0;

	int stdSize = arraySize + 5;
	double * stddevDataOut = new double[stdSize];
	memset(stddevDataOut,0,stdSize * sizeof(double));

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  stdSize - 1, 
			  corrDataOut,
			  5,
			  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      stddevDataOut);

	double * stddev = new double[stdSize + outBeg];
	memset(stddev,0,(stdSize + outBeg) * sizeof(double));
	memcpy(&stddev[outBeg],stddevDataOut,arraySize*sizeof(double));

	for(int i = 0; i < numSticks; ++i)
	{
		corrDataArray[i].corr_ = corrDataOut[i];
		corrDataArray[i].stddev_ = stddev[i];
		corrDataArray[i].slope_ = slopeDataOut[i];
	}


	delete [] closeData1;
	delete [] closeData2;
	delete [] corrDataOut;
	delete [] slopeDataOut;
	delete [] stddevDataOut;
	delete [] stddev;

	return corrDataArray;
}

