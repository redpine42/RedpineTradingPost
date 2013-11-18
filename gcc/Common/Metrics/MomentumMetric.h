#pragma warning(disable:4786) 

#ifndef MomentumMetric_h
#define MomentumMetric_h

struct CandleData;

double getMomentum(const int unsigned size, CandleData * data, long numSticks);

double * getAllMomentum(const int unsigned size, CandleData * data, long numSticks);

#endif
