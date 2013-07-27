#pragma warning(disable:4786) 

#ifndef ROCMetric_h
#define ROCMetric_h

struct CandleData;

double getROC(const int unsigned size, CandleData * data, long numSticks);

double * getAllROC(const unsigned int size, CandleData * data, long numSticks);

#endif

