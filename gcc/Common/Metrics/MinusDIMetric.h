#pragma warning(disable:4786) 

#ifndef MinusDIMetric_h
#define MinusDIMetric_h

struct CandleData;

double getMinusDI(const int unsigned size, CandleData * data, long numSticks);

double * getAllMinusDI(const int unsigned size, CandleData * data, long numSticks);

#endif

