// Ultosc.cpp: implementation of the Ultosc class.
//
//////////////////////////////////////////////////////////////////////

#include "Ultosc.h"
#include "CandleData.h"
#include "ta_libc.h"

double getULTOSC(const unsigned int period1, const unsigned int period2, const unsigned int period3, CandleData * data, long numSticks)
{
	double ultosc = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH,numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * ultoscDataOut = new double[numSticks + period3];

	TA_RetCode ultoscRet =
			TA_ULTOSC( 0,
				  numSticks -1,
				  highData,
				  lowData,
				  closeData,
				  period1,
				  period2,
				  period3,
				  &outBeg,
			      &outNbElement,
			      ultoscDataOut);

	if(outNbElement == 0)
	{
		ultosc = 0.0;
	}
	else
	{
		ultosc = ultoscDataOut[outNbElement - 1];
	}

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] ultoscDataOut;

	return ultosc;
}

double * getAllULTOSC(const unsigned int period1, const unsigned int period2, const unsigned int period3, CandleData * data, long numSticks)
{
	double ultosc = 0.0;

	double * highData = CandleData::getData(data, CandleData::HIGH,numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int arraySize = numSticks + period1;
	double * ultoscDataOut = new double[arraySize];
	memset(ultoscDataOut,0,arraySize * sizeof(double));

	TA_RetCode ultoscRet =
			TA_ULTOSC( 0,
				  numSticks -1,
				  highData,
				  lowData,
				  closeData,
				  period1,
				  period2,
				  period3,
				  &outBeg,
			      &outNbElement,
			      ultoscDataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],ultoscDataOut,arraySize*sizeof(double));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] ultoscDataOut;

	return ret;
}

