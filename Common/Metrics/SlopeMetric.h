#pragma warning(disable:4786) 

#ifndef SlopeMetric_h
#define SlopeMetric_h

struct CandleData;

double getSlope(const int unsigned size, CandleData * data, long numSticks);
double * getAllSlope(const int unsigned size, CandleData * data, long numSticks);

double getSlopeVal(const int unsigned size, CandleData * data, long numSticks);
double * getAllSlopeVal(const int unsigned size, CandleData * data, long numSticks);

#endif
