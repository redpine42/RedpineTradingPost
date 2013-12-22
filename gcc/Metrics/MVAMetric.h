#ifndef MVAMetric_h
#define MVAMetric_h

struct CandleData;

double getMVA(const int unsigned size, CandleData * data, long numSticks);

double * getAllMVA(const int unsigned size, CandleData * data, long numSticks);

#endif

