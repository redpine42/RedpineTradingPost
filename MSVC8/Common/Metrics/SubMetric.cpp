#include "SubMetric.h"
#include "CandleData.h"
#include "ta_libc.h"

double * getAllSubtaction(double * leftData, double * rightData, const unsigned int arraySize)
{
	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[arraySize];
	memset(dataOut,0,arraySize * sizeof(double));

	TA_RetCode subRet =
		TA_SUB( 0,
			  arraySize - 1, 
			  leftData,
			  rightData,
			  &outBeg,
		      &outNbElement,
		      dataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],dataOut,arraySize*sizeof(double));

	delete [] dataOut;

	return ret;

}
