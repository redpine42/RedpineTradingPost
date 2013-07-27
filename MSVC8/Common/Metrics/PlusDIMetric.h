#pragma warning(disable:4786) 

#ifndef PlusDIMetric_h
#define PlusDIMetric_h

struct CandleData;

double getPlusDI(const int unsigned size, CandleData * data, long numSticks);

double * getAllPlusDI(const int unsigned size, CandleData * data, long numSticks);

#endif

