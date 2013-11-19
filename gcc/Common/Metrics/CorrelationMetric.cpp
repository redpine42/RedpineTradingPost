#include "CorrelationMetric.h"
#include "CandleData.h"
#include "MeanMetric.h"
#include "math.h"


double * getAllCorrelation(double * data1, double * data2, const unsigned int dataSize, const unsigned int bars)
{
	int outNbElement = 0;
	int outBeg = 0;

	double * meanX = getAllMean(data1, dataSize, bars);
	double * meanY = getAllMean(data2, dataSize, bars);

	double * corrDataOut = new double[dataSize];
	memset(corrDataOut,0,dataSize * sizeof(double));

	for(int i = bars; i < dataSize+1; ++i)
	{
		double sumX = 0.0;
		double sumY = 0.0;
		double sumXY = 0.0;
		double diffX = 0.0;
		double diffY = 0.0;
		double x2 = 0.0;
		double y2 = 0.0;

		for(int j = i - bars; j < i; ++j)
		{
			diffX = data1[j] - meanX[i-1];
			diffY = data2[j] - meanY[i-1];
			sumX += diffX;
			sumY += diffY;
			sumXY += diffX * diffY;
			x2 += diffX * diffX;
			y2 += diffY * diffY;
		}
		corrDataOut[i-1] = sumXY/(sqrt(x2) * sqrt(y2));
	}
	return corrDataOut;
}
