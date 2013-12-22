#ifndef CCIMetric_h
#define CCIMetric_h

struct CandleData;

double getCCI(const int unsigned size, CandleData * data, long numSticks);
double * getAllCCI(const int unsigned size, CandleData * data, long numSticks);

double getCCISlope(const int unsigned cciBars, const int unsigned slopeBars, CandleData * data, long numSticks);
double * getAllCCISlope(const int unsigned cciBars, const int unsigned slopeBars, CandleData * data, long numSticks);

#endif

