#pragma once

struct CandleData;

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef CorrSlopeMetric_h
#include "CorrSlopeMetric.h"
#endif

class MetricsCache
{
public:
	static MetricsCache * instance(std::string & symbol);
	virtual ~MetricsCache(void);

	double * getADX(int bars, CandleData * data, long numSticks);
	double * getATR(int bars, CandleData * data, long numSticks);
	double * getEMA(int bars, CandleData * data, long numSticks);
	double * getMinusDI(int bars, CandleData * data, long numSticks);
	double * getPlusDI(int bars, CandleData * data, long numSticks);
	double * getROC(int bars, CandleData * data, long numSticks);
	double * getRSI(int bars, CandleData * data, long numSticks);
	double * getSlope(int bars, CandleData * data, long numSticks);
	double * getSlopeVal(int bars, CandleData * data, long numSticks);
	double * getMVA(int bars, CandleData * data, long numSticks);
	double * getMOM(int bars, CandleData * data, long numSticks);
	double * getStoch(int bars, CandleData * data, long numSticks);
	double * getWilliamsR(int bars, CandleData * data, long numSticks);
	double * getCCI(int bars, CandleData * data, long numSticks);
	double * getCCISlope(int cciBars, int slopeBars, CandleData * data, long numSticks);
	double * getPhase(CandleData * data, long numSticks);
	int * getTrend(CandleData * data, long numSticks);
	
	double * getPeriod(CandleData * data, long numSticks);
	void getPhasor(double *& outInPhase, double *& outQuadrature, CandleData * data, long numSticks);
	void getSine(double *& outSine, double *& outLeadSine, CandleData * data, long numSticks);
	double * getTrendLine(CandleData * data, long numSticks);

	double * getRegressionSTD(int bars, double optInNbDev, CandleData * data, long numSticks);
	void getStochRSI(int rsiBars, int kBars, double *& kData, double *& dData, CandleData * data, long numSticks);

	static void cleanCache();
private:
	MetricsCache(void);

	static MetricsCache * instance_;
	static std::string symbol_;


	typedef std::map<int, double *, std::less<int> > MetricMap;
	typedef MetricMap::iterator MetricMapIter;

	typedef std::map<int, int *, std::less<int> > MetricMapInt;
	typedef MetricMapInt::iterator MetricMapIntIter;

	static MetricMap adxMap_;
	static MetricMap atrMap_;
	static MetricMap emaMap_;
	static MetricMap slopeValMap_;//
	static MetricMap slopeMap_;//
	static MetricMap rocMap_;//
	static MetricMap minusDIMap_;
	static MetricMap momMap_;
	static MetricMap plusDIMap_;
	static MetricMap mvaMap_;
	static MetricMap rsiMap_;
	static MetricMap stochMap_;
	static MetricMap stochKrsiMap_;
	static MetricMap stochDrsiMap_;
	static MetricMap ultoscMap_;
	static MetricMap williamsRMap_;
	static MetricMap cciMap_;
	static MetricMap cciSlopeMap_;
	static MetricMap stdMap_;
	static double * phase_;
	static int * trend_;

	static double * period_;
	static double * outInPhase_;
	static double * outQuadrature_;
	static double * outSine_;
	static double * outLeadSine_;
	static double * trendLine_;

};
