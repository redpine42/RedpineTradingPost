#pragma warning(disable:4786) 

#ifndef MaxMin_h
#define MaxMin_h

struct CandleData;

double getMax(const int unsigned size, CandleData * data, long numSticks);
double getMin(const int unsigned size, CandleData * data, long numSticks);

double * getAllMax(const int unsigned size, CandleData * data, long numSticks);
double * getAllMin(const int unsigned size, CandleData * data, long numSticks);

#endif