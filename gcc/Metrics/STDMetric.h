#ifndef STDMetric_h
#define STDMetric_h

struct CandleData;

double getSTD(const int unsigned size, CandleData * data, long numSticks);

double * getAllSTD(const unsigned int size, CandleData * data, long numSticks);
double getSTD(double * doubleSeries, const unsigned int size);
double * getAllSTD(double * doubleSeries, const unsigned int arraySize, const unsigned int size, double dev);

double * getAllRegressionSTD(const unsigned int size, double std, CandleData * data, long numSticks);
double getRegressionSTD(const unsigned int size, double std, CandleData * data, long numSticks);

#endif

