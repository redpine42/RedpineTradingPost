#ifndef PSARMetric_h
#define PSARMetric_h

struct CandleData;

double getPSAR(const double acceleration, const double maximum, CandleData * data, long numSticks);

double * getAllPSAR(const double acceleration, const double maximum, CandleData * data, long numSticks);

#endif

