#ifndef EMAMetric_h
#define EMAMetric_h

struct CandleData;

double getEMA(const int unsigned size, CandleData * data, long numSticks);

double * getAllEMA(const unsigned int size, CandleData * data, long numSticks);

#endif

