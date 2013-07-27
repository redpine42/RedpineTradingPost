// FANNData.cpp: implementation of the FANNData class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <math.h>
#include "FANNData.h"
#include "CandleStickManager.h"
#include "ConfigurationData.h"
#include "MaxMin.h"
#include "EMAMetric.h"
#include "Hilbert.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "ADXMetric.h"
#include "ATRMetric.h"
#include "MinusDIMetric.h"
#include "PlusDIMetric.h"
#include "MomentumMetric.h"
#include "RSIMetric.h"
#include "ROCMetric.h"
#include "SlopeMetric.h"
#include "STOCHMetric.h"
#include "STOCHRSIMetric.h"
#include "WilliamsRMetric.h"
#include "STDMetric.h"


#define TA_REALBODY(IDX)        (int)( fabs( CLOSE_[IDX]/precision_ - OPEN_[IDX]/precision_ ) )
#define TA_UPPERSHADOW(IDX)     (int)( HIGH_[IDX]/precision_ - ( CLOSE_[IDX]/precision_ >= OPEN_[IDX]/precision_ ? CLOSE_[IDX]/precision_ : OPEN_[IDX]/precision_ ) )
#define TA_LOWERSHADOW(IDX)     (int)( ( CLOSE_[IDX]/precision_ >= OPEN_[IDX]/precision_ ? OPEN_[IDX]/precision_ : CLOSE_[IDX]/precision_ ) - LOW_[IDX]/precision_ )
#define TA_HIGHLOWRANGE(IDX)    (int)( HIGH_[IDX]/precision_ - LOW_[IDX]/precision_ )
#define TA_CANDLECOLOR(IDX)     ( CLOSE_[IDX] >= OPEN_[IDX] ? 1.0 : 0.0)

#define TA_REALBODYGAPUP(IDX2,IDX1)     ( min(OPEN_[IDX2],CLOSE_[IDX2]) > max(OPEN_[IDX1],CLOSE_[IDX1])  ? 1.0 : 0.0)
#define TA_REALBODYGAPDOWN(IDX2,IDX1)   ( max(OPEN_[IDX2],CLOSE_[IDX2]) < min(OPEN_[IDX1],CLOSE_[IDX1])  ? 1.0 : 0.0)
#define TA_CANDLEGAPUP(IDX2,IDX1)       ( LOW_[IDX2] > HIGH_[IDX1]  ? 1.0 : 0.0)
#define TA_CANDLEGAPDOWN(IDX2,IDX1)     ( HIGH_[IDX2] < LOW_[IDX1]  ? 1.0 : 0.0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FANNData::FANNData(std::string & symbol)
: precision_(.0001),
  symbol_(symbol)
{
	precision_ = ConfigurationData::instance()->precision(symbol);
	int numSticks = CandleStickManager::instance()->numSticks(symbol);
	if(numSticks > 13)
	{
		numSticks = 13;
	}

	HIGH_ = CandleStickManager::instance()->getData(symbol, CandleStick::HIGH, numSticks);
	LOW_ = CandleStickManager::instance()->getData(symbol, CandleStick::LOW, numSticks);
	CLOSE_ = CandleStickManager::instance()->getData(symbol, CandleStick::CLOSE, numSticks);
	OPEN_ = CandleStickManager::instance()->getData(symbol, CandleStick::OPEN, numSticks);
}

FANNData::~FANNData()
{
	delete [] HIGH_;
	delete [] LOW_;
	delete [] CLOSE_;
	delete [] OPEN_;

}
fann_type * FANNData::getCandleData()
{
	int barIndex = 12;
	fann_type * input = new fann_type[109];
	int i = 0;

	input[i++] = (fann_type)TA_REALBODY(barIndex);
	input[i++] = (fann_type)TA_REALBODY(barIndex-1);
	input[i++] = (fann_type)TA_REALBODY(barIndex-2);
	input[i++] = (fann_type)TA_REALBODY(barIndex-3);
	input[i++] = (fann_type)TA_REALBODY(barIndex-4);
	input[i++] = (fann_type)TA_REALBODY(barIndex-5);
	input[i++] = (fann_type)TA_REALBODY(barIndex-6);
	input[i++] = (fann_type)TA_REALBODY(barIndex-7);
	input[i++] = (fann_type)TA_REALBODY(barIndex-8);
	input[i++] = (fann_type)TA_REALBODY(barIndex-9);
	input[i++] = (fann_type)TA_REALBODY(barIndex-10);
	input[i++] = (fann_type)TA_REALBODY(barIndex-11);

	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-1);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-2);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-3);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-4);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-5);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-6);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-7);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-8);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-9);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-10);
	input[i++] = (fann_type)TA_UPPERSHADOW(barIndex-11);

	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-1);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-2);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-3);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-4);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-5);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-6);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-7);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-8);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-9);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-10);
	input[i++] = (fann_type)TA_LOWERSHADOW(barIndex-11);

	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-1);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-2);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-3);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-4);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-5);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-6);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-7);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-8);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-8);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-10);
	input[i++] = (fann_type)TA_HIGHLOWRANGE(barIndex-11);

	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-1);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-2);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-3);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-4);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-5);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-6);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-7);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-8);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-9);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-10);
	input[i++] = (fann_type)TA_CANDLECOLOR(barIndex-11);

	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-1,barIndex);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-2,barIndex-1);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-3,barIndex-2);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-4,barIndex-3);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-5,barIndex-4);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-6,barIndex-5);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-7,barIndex-6);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-8,barIndex-7);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-9,barIndex-8);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-10,barIndex-9);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-11,barIndex-10);
	input[i++] = (fann_type)TA_REALBODYGAPUP(barIndex-12,barIndex-11);

	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-1,barIndex);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-2,barIndex-1);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-3,barIndex-2);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-4,barIndex-3);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-5,barIndex-4);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-6,barIndex-5);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-7,barIndex-6);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-8,barIndex-7);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-9,barIndex-8);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-10,barIndex-9);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-11,barIndex-10);
	input[i++] = (fann_type)TA_REALBODYGAPDOWN(barIndex-12,barIndex-11);

	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-1,barIndex);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-2,barIndex-1);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-3,barIndex-2);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-4,barIndex-3);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-5,barIndex-4);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-6,barIndex-5);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-7,barIndex-6);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-8,barIndex-7);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-9,barIndex-8);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-10,barIndex-9);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-11,barIndex-10);
	input[i++] = (fann_type)TA_CANDLEGAPUP(barIndex-12,barIndex-11);

	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-1,barIndex);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-2,barIndex-1);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-3,barIndex-2);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-4,barIndex-3);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-5,barIndex-4);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-6,barIndex-5);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-7,barIndex-6);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-8,barIndex-7);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-9,barIndex-8);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-10,barIndex-9);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-11,barIndex-10);
	input[i++] = (fann_type)TA_CANDLEGAPDOWN(barIndex-12,barIndex-11);
	input[i++] = (fann_type)StockWatchList::instance()->getStockWatch(symbol_)->time();

	return input;
}

fann_type * FANNData::getGMMAData()
{
	fann_type * input = new fann_type[13];
	int i = 0;

	input[i++] = getEMA(symbol_,3);
	input[i++] = getEMA(symbol_,5);
	input[i++] = getEMA(symbol_,8);
	input[i++] = getEMA(symbol_,10);
	input[i++] = getEMA(symbol_,15);
	input[i++] = getEMA(symbol_,30);
	input[i++] = getEMA(symbol_,35);
	input[i++] = getEMA(symbol_,40);
	input[i++] = getEMA(symbol_,45);
	input[i++] = getEMA(symbol_,50);
	input[i++] = getEMA(symbol_,55);
	input[i++] = getEMA(symbol_,60);
	input[i++] = (fann_type)StockWatchList::instance()->getStockWatch(symbol_)->time();

	return input;
}

fann_type * FANNData::getHilbertData()
{
	fann_type * input = new fann_type[9];
	int i = 0;

	input[i++] = getPhase(symbol_);
	input[i++] = getTrend(symbol_);
	input[i++] = getPeriod(symbol_);
	input[i++] = getTrend(symbol_);

	double outInPhase = 0.0;
	double outQuadrature = 0.0;
	double outSine = 0.0;
	double outLeadSine = 0.0;
	getPhasor(symbol_,outInPhase, outQuadrature);
	getSine(symbol_, outSine, outLeadSine);
 
	input[i++] = outInPhase;
	input[i++] = outQuadrature;
	input[i++] = outSine;
	input[i++] = outLeadSine;
	input[i++] = (fann_type)StockWatchList::instance()->getStockWatch(symbol_)->time();

	return input;
}

fann_type * FANNData::getMishMashData()
{
	fann_type * input = new fann_type[17];
	int i = 0;

	input[i++] = (fann_type)getEMA(symbol_,18);
	input[i++] = (fann_type)getEMA(symbol_,9);
	input[i++] = (fann_type)getEMA(symbol_,4);
	input[i++] = (fann_type)getADX(symbol_,14);
	input[i++] = (fann_type)getATR(symbol_,14);
	input[i++] = (fann_type)getMinusDI(symbol_,14);
	input[i++] = (fann_type)getPlusDI(symbol_,14);
	input[i++] = (fann_type)getROC(symbol_,14);
	input[i++] = (fann_type)getRSI(symbol_,14);
	input[i++] = (fann_type)getSlope(symbol_,14);
	input[i++] = (fann_type)getMomentum(symbol_,14);
	input[i++] = (fann_type)getStochK(symbol_,14,5);
	input[i++] = (fann_type)getWilliamsR(symbol_,14);
	input[i++] = (fann_type)getRegressionSTD(symbol_,14,1.0);

	double kVal = 0.0;
	double dVal = 0.0;
	getStochRSI(symbol_,14,14,5,kVal, dVal);
	input[i++] = (fann_type)kVal;
	input[i++] = (fann_type)dVal;
	input[i++] = (fann_type)StockWatchList::instance()->getStockWatch(symbol_)->time();

	return input;
}

