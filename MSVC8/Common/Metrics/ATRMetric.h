#pragma warning(disable:4786) 

#ifndef ATRMetric_h
#define ATRMetric_h

struct CandleData;

double getATR(const int unsigned size, CandleData * data, long numSticks);

double * getAllATR(const int unsigned size, CandleData * data, long numSticks);

#endif

