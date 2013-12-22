#include "VarMetric.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

double * getAllVar(double * data, const int unsigned size, const unsigned int arraySize)
{
	int outNbElement = 0;
	int outBeg = 0;
	double optInNbDev = 1.0;

	double * stddevDataOut = new double[arraySize];
	memset(stddevDataOut,0,arraySize * sizeof(double));

	TA_RetCode stddevRet =
		TA_VAR( 0,
			  arraySize - 1, 
			  data,
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
