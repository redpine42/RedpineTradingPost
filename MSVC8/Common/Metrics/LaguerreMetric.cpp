#include "LaguerreMetric.h"
#include "CandleData.h"


double getLaguerre(const double gamma,  unsigned int & size, CandleData * data, long numSticks)
{
	double * allData = getAllLaguerre(gamma, size, data, numSticks);
	double ret = allData[size - 1];

	delete [] allData;

	return ret;
}

double * getAllLaguerre(const double gamma, unsigned int & size, CandleData * data, long numSticks)
{
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	size = numSticks;

	double L0 = 0;
	double L1 = 0;
	double L2 = 0;
	double L3 = 0;
	double L0A = 0;
	double L1A = 0;
	double L2A = 0;
	double L3A = 0;
	double LRSI = 0;
	double CU = 0;
	double CD = 0;

	double * val1 = new double[size];
	for(int i = 0; i < size; ++i)
	{
		L0A = L0;
		L1A = L1;
		L2A = L2;
		L3A = L3;
		L0 = (1 - gamma) * closeData[i] + gamma * L0A;
		L1 = - gamma * L0 + L0A + gamma * L1A;
		L2 = - gamma * L1 + L1A + gamma * L2A;
		L3 = - gamma * L2 + L2A + gamma * L3A;

		CU = 0;
		CD = 0;
      
		if (L0 >= L1) 
		{
			CU = L0 - L1; 
		}
		else 
		{
			CD = L1 - L0;
		}
		if (L1 >= L2)
		{
			CU = CU + L1 - L2; 
		}
		else 
		{
			CD = CD + L2 - L1;
		}
		if (L2 >= L3)
		{
			CU = CU + L2 - L3;
		}
		else
		{
			CD = CD + L3 - L2;
		}
		if (CU + CD != 0) 
		{
			LRSI = CU / (CU + CD);
		}
		val1[i] = LRSI;
	}
	delete [] closeData;

	return val1;
}

