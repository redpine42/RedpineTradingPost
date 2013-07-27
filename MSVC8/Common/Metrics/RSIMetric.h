#pragma warning(disable:4786) 

#ifndef RSIMetric_h
#define RSIMetric_h

struct CandleData;

double getRSI(const int unsigned size, CandleData * data, long numSticks);

double * getAllRSI(const int unsigned size, CandleData * data, long numSticks);

#endif
