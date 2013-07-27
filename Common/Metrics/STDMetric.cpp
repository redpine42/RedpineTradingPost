#include "STDMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include "SlopeMetric.h"

double getSTD(const unsigned int size, CandleData * data, long numSticks)
{
	double stddev = 0.0;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);
	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = 1.0;

	double * stddevDataOut = new double[numSticks + size];

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  numSticks - 1,
			  csData,
			  size,
		  	  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      stddevDataOut);

	if(outNbElement == 0)
	{
		stddev = 0.0;
	}
	else
	{
		stddev = stddevDataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] stddevDataOut;
	
	return stddev;
}

double getSTD(double * doubleSeries, const unsigned int size)
{
	double stddev = 0.0;
	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = 1.0;

	double * stddevDataOut = new double[1];

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  size - 1,
			  doubleSeries,
			  size,
		  	  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      stddevDataOut);

	if(outNbElement == 0)
	{
		stddev = 0.0;
	}
	else
	{
		stddev = stddevDataOut[outNbElement - 1];
	}

	delete [] stddevDataOut;
	
	return stddev;
}

double * getAllSTD(double * doubleSeries, const unsigned int arraySize, const unsigned int size, double dev)
{
	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = dev;

	double * stddevDataOut = new double[arraySize];
	memset(stddevDataOut,0,arraySize * sizeof(double));

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  arraySize - 1, 
			  doubleSeries,
			  size,
			  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      stddevDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],stddevDataOut,arraySize*sizeof(double));

	delete [] stddevDataOut;

	return ret;
}

double * getAllSTD(const unsigned int size, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = 1.0;

	int arraySize = numSticks + size;
	double * stddevDataOut = new double[arraySize];
	memset(stddevDataOut,0,arraySize * sizeof(double));

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  numSticks - 1, 
			  closeData,
			  size,
			  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      stddevDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],stddevDataOut,arraySize*sizeof(double));

	delete [] closeData;
	delete [] stddevDataOut;

	return ret;
}

double * getAllRegressionSTD(const unsigned int size, double optInNbDev, CandleData * data, long numSticks)
{
	double * slopeVal = getAllSlopeVal(size, data, numSticks);

	double * closeVals = CandleData::getData(data, CandleData::CLOSE, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * temp = new double[numSticks];
	memset(temp,0,numSticks * sizeof(double));

	TA_RetCode subret = TA_SUB(0,
							numSticks -1,
							slopeVal,
							closeVals,
							&outBeg,
							&outNbElement,
							temp);


	double * deviation_ = new double[outNbElement + outBeg];
	memset(deviation_,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&deviation_[outBeg],temp,outNbElement*sizeof(double));

	delete [] closeVals;
	delete [] slopeVal;
	delete [] temp;

	temp = new double[numSticks];
	memset(temp,0,numSticks * sizeof(double));

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  numSticks - 1, 
			  deviation_,
			  size,
			  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      temp);

	double * ret = new double[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],temp,outNbElement*sizeof(double));

	delete [] temp;
	delete [] deviation_;
	
	return ret;
}
double getRegressionSTD(const unsigned int size, double optInNbDev, CandleData * data, long numSticks)
{
	double stddev = 0.0;
	double * slopeVal = getAllSlopeVal(size,data,numSticks);

	double * closeVals = CandleData::getData(data, CandleData::CLOSE, numSticks);
	int outNbElement = 0;
	int outBeg = 0;

	double * temp = new double[numSticks];
	memset(temp,0,numSticks * sizeof(double));

	TA_RetCode subret = TA_SUB(0,
							numSticks -1,
							slopeVal,
							closeVals,
							&outBeg,
							&outNbElement,
							temp);


	double * deviation_ = new double[outNbElement + outBeg];
	memset(deviation_,0,(outNbElement + outBeg) * sizeof(double));
	memcpy(&deviation_[outBeg],temp,outNbElement*sizeof(double));

	delete [] closeVals;
	delete [] slopeVal;
	delete [] temp;

	temp = new double[numSticks];
	memset(temp,0,numSticks * sizeof(double));

	TA_RetCode stddevRet =
		TA_STDDEV( 0,
			  numSticks - 1, 
			  deviation_,
			  size,
			  optInNbDev,
			  &outBeg,
		      &outNbElement,
		      temp);

	if(outNbElement == 0)
	{
		stddev = 0.0;
	}
	else
	{
		stddev = temp[outNbElement - 1];
	}

	delete [] temp;
	delete [] deviation_;
	
	return stddev;
}

