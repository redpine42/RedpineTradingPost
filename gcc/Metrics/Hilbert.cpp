#include "Hilbert.h"
#include "CandleData.h"
#include "ta_libc.h"
#include <string.h>

int isTrendMode(CandleData * data, long numSticks)
{
	int retVal = 0;

	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int * dataOut = new int[numSticks];
	memset(dataOut,0,numSticks * sizeof(int));

	TA_RetCode ret =
		TA_HT_TRENDMODE( 0,
                         numSticks-1,
                         csData,
		 				 &outBeg,
			    		 &outNbElement,
                         dataOut );


	if(outNbElement != 0)
	{
		retVal = dataOut[outNbElement - 1];
	}
	delete [] csData;
	delete [] dataOut;

	return retVal;
}

int * isTrendModeAll(CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int * dataOut = new int[numSticks];
	memset(dataOut,0,numSticks * sizeof(int));

	TA_RetCode ret =
		TA_HT_TRENDMODE( 0,
                         numSticks-1,
                         csData,
		 				 &outBeg,
			    		 &outNbElement,
                         dataOut );


	int * retVal = new int[numSticks + outBeg];
	memset(retVal,0,(numSticks + outBeg) * sizeof(int));
	memcpy(&retVal[outBeg],dataOut,numSticks*sizeof(int));

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

Phase getPhaseEnum(CandleData * data, long numSticks)
{
	Phase phaseVal = PhaseTwo;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[1];

	TA_RetCode ret =
			TA_HT_DCPHASE( 0,
                            numSticks -1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut );


	double trend = dataOut[0];

	delete [] csData;
	delete [] dataOut;
	if(trend > 0.0 && trend < 90.0)
	{
		phaseVal = PhaseTwo;
	}
	else if(trend > 90.0 && trend < 180.0)
	{
		phaseVal = PhaseThree;
	}
	else if(trend > 180.0 && trend < 270.0)
	{
		phaseVal = PhaseFour;
	}
	else if(trend > 270.0 && trend < 360.0)
	{
		phaseVal = PhaseOne;
	}
	
	return phaseVal;
}

double getPhase(CandleData * data, long numSticks)
{
	double retVal = 0.0;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
		TA_HT_DCPHASE( 0,
                       numSticks-1,
                       csData,
						&outBeg,
		    		    &outNbElement,
                        dataOut );


	if(outNbElement != 0)
	{
		retVal = dataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] dataOut;

	return retVal;
}
double * getPhaseAll(CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
			TA_HT_DCPHASE( 0,
                            numSticks-1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut );


	double * retVal = new double[numSticks + outBeg];
	memset(retVal,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&retVal[outBeg],dataOut,numSticks*sizeof(double));

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

Phase getPhaseEnum(double val)
{
	Phase phaseVal = PhaseTwo;
	if(val > 0.0 && val < 90.0)
	{
		phaseVal = PhaseOne;
	}
	else if(val > 90.0 && val < 180.0)
	{
		phaseVal = PhaseTwo;
	}
	else if(val > 180.0 && val < 270.0)
	{
		phaseVal = PhaseThree;
	}
	else if(val > 270.0 && val < 360.0)
	{
		phaseVal = PhaseFour;
	}
	return phaseVal;
}


double getPeriod(CandleData * data, long numSticks)
{
	double retVal = 0.0;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
		TA_HT_DCPERIOD( 0,
                       numSticks-1,
                       csData,
						&outBeg,
		    		    &outNbElement,
                        dataOut );


	if(outNbElement != 0)
	{
		retVal = dataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

double * getPeriodAll(CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
			TA_HT_DCPERIOD( 0,
                            numSticks-1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut );


	double * retVal = new double[numSticks + outBeg];
	memset(retVal,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&retVal[outBeg],dataOut,numSticks*sizeof(double));

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

void getPhasor(double outInPhase, double outQuadrature, CandleData * data, long numSticks)
{
	outInPhase = 0.0;
	outQuadrature = 0.0;

	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut1 = new double[numSticks];
	memset(dataOut1,0,numSticks * sizeof(double));
	double * dataOut2 = new double[numSticks];
	memset(dataOut2,0,numSticks * sizeof(double));

	TA_RetCode ret =
		TA_HT_PHASOR( 0,
                       numSticks-1,
                       csData,
						&outBeg,
		    		    &outNbElement,
                        dataOut1,
						dataOut2);


	if(outNbElement != 0)
	{
		outInPhase = dataOut1[outNbElement - 1];
		outQuadrature = dataOut2[outNbElement - 1];
	}

	delete [] csData;
	delete [] dataOut1;
	delete [] dataOut2;
}

void getPhasorAll(double *& outInPhase, double *& outQuadrature, CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut1 = new double[numSticks];
	memset(dataOut1,0,numSticks * sizeof(double));
	double * dataOut2 = new double[numSticks];
	memset(dataOut2,0,numSticks * sizeof(double));

	TA_RetCode ret =
			TA_HT_PHASOR( 0,
                            numSticks-1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut1,
							dataOut2);


	outInPhase = new double[numSticks + outBeg];
	memset(outInPhase,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&outInPhase[outBeg],dataOut1,numSticks*sizeof(double));

	outQuadrature = new double[numSticks + outBeg];
	memset(outQuadrature,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&outQuadrature[outBeg],dataOut2,numSticks*sizeof(double));

	delete [] csData;
	delete [] dataOut1;
	delete [] dataOut2;
}

void getSine(double outSine, double outLeadSine, CandleData * data, long numSticks)
{
	outSine = 0.0;
	outLeadSine = 0.0;

	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut1 = new double[numSticks];
	memset(dataOut1,0,numSticks * sizeof(double));
	double * dataOut2 = new double[numSticks];
	memset(dataOut2,0,numSticks * sizeof(double));

	TA_RetCode ret =
		TA_HT_SINE( 0,
                       numSticks-1,
                       csData,
						&outBeg,
		    		    &outNbElement,
                        dataOut1,
						dataOut2);


	if(outNbElement != 0)
	{
		outSine = dataOut1[outNbElement - 1];
		outLeadSine = dataOut2[outNbElement - 1];
	}

	delete [] csData;
	delete [] dataOut1;
	delete [] dataOut2;
}

void getSineAll(double *& outSine, double *& outLeadSine, CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut1 = new double[numSticks];
	memset(dataOut1,0,numSticks * sizeof(double));

	double * dataOut2 = new double[numSticks];
	memset(dataOut2,0,numSticks * sizeof(double));

	TA_RetCode ret =
			TA_HT_SINE( 0,
                            numSticks-1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut1,
							dataOut2);


	outSine = new double[numSticks + outBeg];
	memset(outSine,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&outSine[outBeg],dataOut1,numSticks*sizeof(double));

	outLeadSine = new double[numSticks + outBeg];
	memset(outLeadSine,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&outLeadSine[outBeg],dataOut2,numSticks*sizeof(double));

	delete [] csData;
	delete [] dataOut1;
	delete [] dataOut2;
}

double getTrend(CandleData * data, long numSticks)
{
	double retVal = 0.0;
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
		TA_HT_TRENDLINE( 0,
                       numSticks-1,
                       csData,
						&outBeg,
		    		    &outNbElement,
                        dataOut );


	if(outNbElement != 0)
	{
		retVal = dataOut[outNbElement - 1];
	}

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

double * getTrendAll(CandleData * data, long numSticks)
{
	double * csData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	double * dataOut = new double[numSticks];
	memset(dataOut,0,numSticks * sizeof(double));

	TA_RetCode ret =
			TA_HT_TRENDLINE( 0,
                            numSticks-1,
                            csData,
							&outBeg,
			    		    &outNbElement,
                            dataOut );


	double * retVal = new double[numSticks + outBeg];
	memset(retVal,0,(numSticks + outBeg) * sizeof(double));
	memcpy(&retVal[outBeg],dataOut,numSticks*sizeof(double));

	delete [] csData;
	delete [] dataOut;

	return retVal;
}

