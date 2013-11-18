#include "DivMetric.h"
#include "CandleData.h"
#include "ta_libc.h"

double * getAllDivision(double * leftData, double * rightData, const unsigned int arraySize)
{
	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[arraySize];
	memset(dataOut,0,arraySize * sizeof(double));

	TA_RetCode subRet =
		TA_DIV( 0,
			  arraySize - 1, 
			  leftData,
			  rightData,
			  &outBeg,
		      &outNbElement,
		      dataOut);

	double * ret = new double[arraySize + outBeg];
	memset(ret,0,(arraySize + outBeg) * sizeof(double));
	memcpy(&ret[outBeg],dataOut,arraySize*sizeof(double));
	for(int i = 0; i < arraySize + outBeg; ++i)
	{
		if(ret[i] != ret[i] || !(ret[i] <= DBL_MAX && ret[i] >= -DBL_MAX))
		{
			ret[i] = 0.0;
		}

	}

	delete [] dataOut;

	return ret;

}
