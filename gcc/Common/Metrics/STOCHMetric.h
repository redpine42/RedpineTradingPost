#pragma warning(disable:4786) 

#ifndef STOCHMetric_h
#define STOCHMetric_h

struct CandleData;

double getStochK(const int unsigned kSize, const int unsigned dSize, CandleData * data, long numSticks);
double * getAllStochK(const int unsigned kSize, const int unsigned dSize, CandleData * data, long numSticks);

double getStoch(const int unsigned kSize, const int unsigned kSlowSize, const int unsigned dSize, CandleData * data, long numSticks);
double * getAllStoch(const int unsigned kSize, const int unsigned kSlowSize, const int unsigned dSize, CandleData * data, long numSticks);

#endif

