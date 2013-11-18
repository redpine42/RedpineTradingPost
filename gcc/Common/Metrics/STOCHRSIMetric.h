#pragma warning(disable:4786) 

#ifndef STOCHRSIMetric_h
#define STOCHRSIMetric_h

struct CandleData;

void getStochRSI(const int unsigned period,
				 const int unsigned kSize, 
				 const int unsigned dSize,
				 double & kData,
				 double & dData, CandleData * data, long numSticks);

void getAllStochRSI(const int unsigned period,
				 const int unsigned kSize, 
				 const int unsigned dSize,
				 double *& kData,
				 double *& dData, CandleData * data, long numSticks);

#endif

