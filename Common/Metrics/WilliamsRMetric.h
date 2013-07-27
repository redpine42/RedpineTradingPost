#pragma warning(disable:4786) 

#ifndef WilliamsRMetric_h
#define WilliamsRMetric_h

struct CandleData;

double getWilliamsR(const unsigned int size, CandleData * data, long numSticks);

double * getAllWilliamsR(const int unsigned size, CandleData * data, long numSticks);

#endif

