#include "CCIMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double getCCI(const unsigned int size, CandleData * data, long numSticks)
{
	double CCI = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * CCIDataOut = new double[numSticks+size];

	TA_RetCode CCIRet =
			TA_CCI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      CCIDataOut);

	if(outNbElement == 0)
	{
		CCI = 0.0;
	}
	else
	{
		CCI = CCIDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] CCIDataOut;

	return CCI;
}

double * getAllCCI(const int unsigned size, CandleData * data, long numSticks)
{
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + size;
	double * CCIDataOut = new double[arraySize];
	memset(CCIDataOut,0,arraySize * sizeof(double));

	TA_RetCode CCIRet =
			TA_CCI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  size,
				  &outBeg,
			      &outNbElement,
			      CCIDataOut);

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],CCIDataOut,outNbElement*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] CCIDataOut;

	return ret;
}

double getCCISlope(const int unsigned cciBars, const int unsigned slopeBars, CandleData * data, long numSticks)
{
	double slope = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + cciBars;
	double * CCIDataOut = new double[arraySize];
	memset(CCIDataOut,0,arraySize * sizeof(double));

	TA_RetCode CCIRet =
			TA_CCI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  cciBars,
				  &outBeg,
			      &outNbElement,
			      CCIDataOut);

	int newSize = outNbElement+outBeg;

	double * ret = new double[newSize];
	memset(ret,0,(newSize) * sizeof(double));
	memcpy(&ret[outBeg],CCIDataOut,outNbElement*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] CCIDataOut;

	double * slopeDataOut = new double[newSize];
	memset(slopeDataOut,0,(newSize) * sizeof(double));

	TA_RetCode retCodeSlope =  
		TA_LINEARREG_SLOPE(0, 
		                   newSize - 1,
                            ret,
                            slopeBars,
                            &outBeg,
                            &outNbElement,
                            slopeDataOut);

	if(outNbElement == 0)
	{
		slope = 0.0;
	}
	else
	{
		slope = slopeDataOut[outNbElement - 1];
	}
	delete [] ret;
	delete [] slopeDataOut;

	return slope;
}

double * getAllCCISlope(const int unsigned cciBars, const int unsigned slopeBars, CandleData * data, long numSticks)
{
	double slope = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + cciBars;
	double * CCIDataOut = new double[arraySize];
	memset(CCIDataOut,0,arraySize * sizeof(double));

	TA_RetCode CCIRet =
			TA_CCI( 0,
				  numSticks - 1,
				  highData,
				  lowData,
				  closeData,
				  cciBars,
				  &outBeg,
			      &outNbElement,
			      CCIDataOut);

	int newSize = outNbElement+outBeg;
	double * cciRet = new double[newSize];
	memset(cciRet,0,(newSize) * sizeof(double));
	memcpy(&cciRet[outBeg],CCIDataOut,outNbElement*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] CCIDataOut;

	double * slopeDataOut = new double[newSize];
	memset(slopeDataOut,0,newSize * sizeof(double));

	TA_RetCode retCodeSlope =  
		TA_LINEARREG_SLOPE(0, 
		                   newSize - 1,
                            cciRet,
                            slopeBars,
                            &outBeg,
                            &outNbElement,
                            slopeDataOut);

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],slopeDataOut,outNbElement*sizeof(double));
	delete [] cciRet;
	delete [] slopeDataOut;


	return ret;
}
