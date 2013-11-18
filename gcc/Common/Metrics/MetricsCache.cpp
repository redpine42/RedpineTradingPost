#include "MetricsCache.h"
#include "ADXMetric.h"
#include "ATRMetric.h"
#include "EMAMetric.h"
#include "MVAMetric.h"
#include "SlopeMetric.h"
#include "RSIMetric.h"
#include "StochMetric.h"
#include "MomentumMetric.h"
#include "ROCMetric.h"
#include "MinusDIMetric.h"
#include "PlusDIMetric.h"
#include "StochRSIMetric.h"
#include "WilliamsRMetric.h"
#include "CCIMetric.h"
#include "STDMetric.h"
#include "Hilbert.h"
#include "CandleData.h"

MetricsCache * MetricsCache::instance_ = 0;
std::string MetricsCache::symbol_ = "";

MetricsCache::MetricMap MetricsCache::adxMap_;
MetricsCache::MetricMap MetricsCache::atrMap_;
MetricsCache::MetricMap MetricsCache::emaMap_;
MetricsCache::MetricMap MetricsCache::slopeValMap_;
MetricsCache::MetricMap MetricsCache::slopeMap_;
MetricsCache::MetricMap MetricsCache::rocMap_;
MetricsCache::MetricMap MetricsCache::minusDIMap_;
MetricsCache::MetricMap MetricsCache::momMap_;
MetricsCache::MetricMap MetricsCache::plusDIMap_;
MetricsCache::MetricMap MetricsCache::mvaMap_;
MetricsCache::MetricMap MetricsCache::rsiMap_;
MetricsCache::MetricMap MetricsCache::stochMap_;
MetricsCache::MetricMap MetricsCache::stochKrsiMap_;
MetricsCache::MetricMap MetricsCache::stochDrsiMap_;
MetricsCache::MetricMap MetricsCache::ultoscMap_;
MetricsCache::MetricMap MetricsCache::williamsRMap_;
MetricsCache::MetricMap MetricsCache::cciMap_;
MetricsCache::MetricMap MetricsCache::cciSlopeMap_;
MetricsCache::MetricMap MetricsCache::stdMap_;
double * MetricsCache::phase_ = 0;
int * MetricsCache::trend_ = 0;
double * MetricsCache::period_ = 0;;
double * MetricsCache::outInPhase_ = 0;
double * MetricsCache::outQuadrature_ = 0;
double * MetricsCache::outSine_ = 0;
double * MetricsCache::outLeadSine_ = 0;
double * MetricsCache::trendLine_ = 0;



MetricsCache::MetricsCache(void)
{
}

MetricsCache::~MetricsCache(void)
{
}

MetricsCache * MetricsCache::instance(std::string & symbol)
{
	if(symbol_ != symbol)
	{
		cleanCache();
		symbol_ = symbol;
	}
	if(0 == instance_)
	{
		instance_ = new MetricsCache();
	}
	return instance_;
}

double * MetricsCache::getADX(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = adxMap_.find(bars);
	if(iter == adxMap_.end())
	{
		adxMap_[bars] = getAllADX(bars, data, numSticks);
		ret = adxMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getATR(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = atrMap_.find(bars);
	if(iter == atrMap_.end())
	{
		atrMap_[bars] = getAllATR(bars, data, numSticks);
		ret = atrMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}


double * MetricsCache::getEMA(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = emaMap_.find(bars);
	if(iter == emaMap_.end())
	{
		emaMap_[bars] = getAllEMA(bars, data, numSticks);
		ret = emaMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getMinusDI(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = minusDIMap_.find(bars);
	if(iter == minusDIMap_.end())
	{
		minusDIMap_[bars] = getAllMinusDI(bars, data, numSticks);
		ret = minusDIMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getPlusDI(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = plusDIMap_.find(bars);
	if(iter == plusDIMap_.end())
	{
		plusDIMap_[bars] = getAllPlusDI(bars, data, numSticks);
		ret = plusDIMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getROC(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = rocMap_.find(bars);
	if(iter == rocMap_.end())
	{
		rocMap_[bars] = getAllROC(bars, data, numSticks);
		ret = rocMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getRSI(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = rsiMap_.find(bars);
	if(iter == rsiMap_.end())
	{
		rsiMap_[bars] = getAllRSI(bars, data, numSticks);
		ret = rsiMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getSlope(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = slopeMap_.find(bars);
	if(iter == slopeMap_.end())
	{
		slopeMap_[bars] = getAllSlope(bars, data, numSticks);
		ret = slopeMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getSlopeVal(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = slopeValMap_.find(bars);
	if(iter == slopeValMap_.end())
	{
		slopeValMap_[bars] = getAllSlopeVal(bars, data, numSticks);
		ret = slopeValMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getMVA(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = mvaMap_.find(bars);
	if(iter == mvaMap_.end())
	{
		mvaMap_[bars] = getAllMVA(bars, data, numSticks);
		ret = mvaMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getMOM(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = momMap_.find(bars);
	if(iter == momMap_.end())
	{
		momMap_[bars] = getAllMomentum(bars, data, numSticks);
		ret = momMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getWilliamsR(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = williamsRMap_.find(bars);
	if(iter == williamsRMap_.end())
	{
		williamsRMap_[bars] = getAllWilliamsR(bars, data, numSticks);
		ret = williamsRMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getCCI(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = cciMap_.find(bars);
	if(iter == cciMap_.end())
	{
		cciMap_[bars] = getAllCCI(bars, data, numSticks);
		ret = cciMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}
double * MetricsCache::getCCISlope(int cciBars, int slopeBars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	int bars = (cciBars * 1000) + slopeBars;
	iter = cciSlopeMap_.find(bars);
	if(iter == cciSlopeMap_.end())
	{
		cciSlopeMap_[bars] = getAllCCISlope(cciBars, slopeBars, data, numSticks);
		ret = cciSlopeMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

double * MetricsCache::getPhase(CandleData * data, long numSticks)
{
	if(phase_ == 0)
	{
		phase_ = getPhaseAll(data, numSticks);
	}
	return phase_;
}

int * MetricsCache::getTrend(CandleData * data, long numSticks)
{
	if(trend_ == 0)
	{
		trend_ = isTrendModeAll(data, numSticks);
	}
	return trend_;
}

double * MetricsCache::getPeriod(CandleData * data, long numSticks)
{
	if(period_ == 0)
	{
		period_ = getPeriodAll(data, numSticks);
	}
	return period_;
}

void MetricsCache::getPhasor(double *& outInPhase, double *& outQuadrature, CandleData * data, long numSticks)
{
	if(outInPhase_ == 0)
	{
		getPhasorAll(outInPhase_, outQuadrature_, data, numSticks);
	}
	outInPhase = outInPhase_;
	outQuadrature = outQuadrature_;
}

void MetricsCache::getSine(double *& outSine, double *& outLeadSine, CandleData * data, long numSticks)
{
	if(outSine_ == 0)
	{
		getSineAll(outSine_,outLeadSine_, data, numSticks);
	}
	outSine = outSine_;
	outLeadSine = outLeadSine_;
}

double * MetricsCache::getTrendLine(CandleData * data, long numSticks)
{
	if(trendLine_ == 0)
	{
		trendLine_ = getTrendAll(data, numSticks);
	}
	return trendLine_;
}



double * MetricsCache::getStoch(int bars, CandleData * data, long numSticks)
{
	double * ret = 0;
	MetricMapIter iter;
	iter = stochMap_.find(bars);
	if(iter == stochMap_.end())
	{
		stochMap_[bars] = getAllStochK(bars,5, data, numSticks);
		ret = stochMap_[bars];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}

void MetricsCache::getStochRSI(int rsiBars,int kBars, double *& kData, double *& dData, CandleData * data, long numSticks)
{
	int key = rsiBars * 1000;
	key +=  kBars;
	MetricMapIter iter;
	iter = stochKrsiMap_.find(key);
	if(iter == stochKrsiMap_.end())
	{
		getAllStochRSI(rsiBars, kBars, 5,kData, dData, data, numSticks);
		stochKrsiMap_[key] = kData;
		stochDrsiMap_[key]= dData;
	}
	else
	{
		kData = (*iter).second;
		dData = stochDrsiMap_[key];
	}
}

double * MetricsCache::getRegressionSTD(int bars, double optInNbDev, CandleData * data, long numSticks)
{
	int key = (int)(optInNbDev * 20000.0);
	key +=  bars;
	double * ret = 0;
	MetricMapIter iter;
	iter = stdMap_.find(key);
	if(iter == stdMap_.end())
	{
		stdMap_[key] = getAllRegressionSTD(bars, optInNbDev, data, numSticks);
		ret = stdMap_[key];
	}
	else
	{
		ret = (*iter).second;
	}
	return ret;
}




void MetricsCache::cleanCache()
{
	delete [] trend_;
	delete [] phase_;
	delete [] period_;
	delete [] outInPhase_;
	delete [] outQuadrature_;
	delete [] outSine_;
	delete [] outLeadSine_;
	delete [] trendLine_;

	period_ = 0;
	outInPhase_ = 0;
	outQuadrature_ = 0;
	outSine_ = 0;
	outLeadSine_ = 0;
	trendLine_ = 0;

	trend_ = 0;
	phase_ = 0;

	double * data;
	MetricMapIter mapIter;
	for(mapIter = atrMap_.begin(); mapIter != atrMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	atrMap_.erase(atrMap_.begin(), atrMap_.end());

	for(mapIter = adxMap_.begin(); mapIter != adxMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	adxMap_.erase(adxMap_.begin(), adxMap_.end());

	for(mapIter = emaMap_.begin(); mapIter != emaMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	emaMap_.erase(emaMap_.begin(), emaMap_.end());

	for(mapIter = slopeMap_.begin(); mapIter != slopeMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	slopeMap_.erase(slopeMap_.begin(), slopeMap_.end());

	for(mapIter = slopeValMap_.begin(); mapIter != slopeValMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	slopeValMap_.erase(slopeValMap_.begin(), slopeValMap_.end());

	for(mapIter = rocMap_.begin(); mapIter != rocMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	rocMap_.erase(rocMap_.begin(), rocMap_.end());

	for(mapIter = minusDIMap_.begin(); mapIter != minusDIMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	minusDIMap_.erase(minusDIMap_.begin(), minusDIMap_.end());

	for(mapIter = momMap_.begin(); mapIter != momMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	momMap_.erase(momMap_.begin(), momMap_.end());

	for(mapIter = plusDIMap_.begin(); mapIter != plusDIMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	plusDIMap_.erase(plusDIMap_.begin(), plusDIMap_.end());

	for(mapIter = mvaMap_.begin(); mapIter != mvaMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	mvaMap_.erase(mvaMap_.begin(), mvaMap_.end());

	for(mapIter = stochKrsiMap_.begin(); mapIter != stochKrsiMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	stochKrsiMap_.erase(stochKrsiMap_.begin(), stochKrsiMap_.end());

	for(mapIter = stochDrsiMap_.begin(); mapIter != stochDrsiMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	stochDrsiMap_.erase(stochDrsiMap_.begin(), stochDrsiMap_.end());

	for(mapIter = rsiMap_.begin(); mapIter != rsiMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	rsiMap_.erase(rsiMap_.begin(), rsiMap_.end());

	for(mapIter = stochMap_.begin(); mapIter != stochMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	stochMap_.erase(stochMap_.begin(), stochMap_.end());

	for(mapIter = ultoscMap_.begin(); mapIter != ultoscMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	ultoscMap_.erase(ultoscMap_.begin(), ultoscMap_.end());

	for(mapIter = williamsRMap_.begin(); mapIter != williamsRMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	williamsRMap_.erase(williamsRMap_.begin(), williamsRMap_.end());

	for(mapIter = cciMap_.begin(); mapIter != cciMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	cciMap_.erase(cciMap_.begin(), cciMap_.end());
	
	for(mapIter = cciSlopeMap_.begin(); mapIter != cciSlopeMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	cciSlopeMap_.erase(cciSlopeMap_.begin(), cciSlopeMap_.end());
	
	for(mapIter = stdMap_.begin(); mapIter != stdMap_.end(); ++mapIter)
	{
		data = (*mapIter).second;
		delete [] data;
	}
	stdMap_.erase(stdMap_.begin(), stdMap_.end());
	}
