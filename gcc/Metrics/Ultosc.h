#ifndef UltoscMetric_h
#define UltoscMetric_h

struct CandleData;

double getULTOSC(const unsigned int period1, const unsigned int period2, const unsigned int period3, CandleData * data, long numSticks);

double * getAllULTOSC(const unsigned int period1, const unsigned int period2, const unsigned int period3, CandleData * data, long numSticks);

#endif

