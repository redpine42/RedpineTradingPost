#ifndef ADXMetric_h
#define ADXMetric_h

struct CandleData;

double getADX(const int unsigned size, CandleData * data, long numSticks);

double * getAllADX(const int unsigned size, CandleData * data, long numSticks);

#endif

