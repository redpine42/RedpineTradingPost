// TurtleBreakout.cpp: implementation of the TurtleBreakout class.
//
//////////////////////////////////////////////////////////////////////

#include "TurtleBreakout.h"
#include "MaxMin.h"
#include "ATRMetric.h"
#include "EMAMetric.h"
#include "StockWatch.h"

#include "CandleStickManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TurtleBreakout::TurtleBreakout(StockWatch * stock, int numBars, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "Turtle Breakout Entry", startTradeTime, endTradeTime),
	  numBars_(numBars)
{

}

TurtleBreakout::~TurtleBreakout()
{

}

bool TurtleBreakout::buy()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	
	CandleStick * cs = CandleStickManager::instance()->getLatestCandleStick(stock_->symbol());
	if(0 != cs)
	{
		double localPrice = cs->closePrice();
		double max = getMax(stock_->symbol(), numBars_);
		if(localPrice >= max)
		{
			return true;
		}
	}
	return false;
}

bool TurtleBreakout::sellShort()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	CandleStick * cs = CandleStickManager::instance()->getLatestCandleStick(stock_->symbol());
	if(0 != cs)
	{
		double localPrice = cs->closePrice();
		double min = getMin(stock_->symbol(), numBars_);

		if(localPrice <= min)
		{
			return true;
		}
	}
	return false;
}
