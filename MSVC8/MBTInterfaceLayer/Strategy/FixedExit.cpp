// FixedExit.cpp: implementation of the ATRExit class.
//
//////////////////////////////////////////////////////////////////////

#include "FixedExit.h"
#include "StockWatch.h"
#include "StockWatchList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FixedExit::FixedExit(std::string & symbol,long startTime, long endTime, double stopLoss, double takeProfit)
: ExitStrategy("Fixed TP/SL", startTime, endTime),
  pipsStopLoss_(stopLoss),
  pipsTakeProfit_(takeProfit)
{
}

FixedExit::~FixedExit()
{
}

bool FixedExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	if(price > openPrice + pipsStopLoss_||
	   price < openPrice - pipsTakeProfit_)
	{
		return true;
	}
	else if (stock->time() > endTradeTime_ && stock->time() < (endTradeTime_ + 900) && price < openPrice)
	{
		return true;
	}
	return false;
}

bool FixedExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	if(price > openPrice + pipsTakeProfit_||
	   price < openPrice - pipsStopLoss_)
	{
		return true;
	}
	else if (stock->time() > endTradeTime_ && stock->time() < (endTradeTime_ + 900) && price > openPrice)
	{
		return true;
	}
	return false;
}

