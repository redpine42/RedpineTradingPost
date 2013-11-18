#include "MeanMetric.h"

double * getAllMean(double * data, const unsigned int arraySize, const int unsigned size)
{
	double * ret = new double[arraySize];
	double sum = 0.0;
	for(int i = 0; i < size; ++i)
	{
		ret[i] = 0.0;
		sum +=data[i];
	}
	ret[size-1] = sum/size;
	for(int i = size; i < arraySize; ++i)
	{
		sum -= data[i-size];
		sum += data[i];
		ret[i]= sum/size;
	}
	return ret;
}
