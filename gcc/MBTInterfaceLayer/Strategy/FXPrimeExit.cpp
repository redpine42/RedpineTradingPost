// FXPrimeExit.cpp: implementation of the ATRExit class.
//
//////////////////////////////////////////////////////////////////////

#include "FXPrimeExit.h"
#include "StockWatch.h"
#include "StockWatchList.h"
#include "CandleStickManager.h"
#include "HACandle.h"
#include "ConfigurationData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FXPrimeExit::FXPrimeExit(std::string & symbol,long startTime, long endTime)
: ExitStrategy("FX Prime Exit", startTime, endTime),
  takeProfitPrice_(0.0)
{
	precision_ = ConfigurationData::instance()->precision(symbol);
}

FXPrimeExit::~FXPrimeExit()
{
}

bool FXPrimeExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	HACandle * haCandle = CandleStickManager::instance()->getLatestHACandleStick(symbol);
	double haOpen = haCandle->openPrice();
	double haClose = haCandle->closePrice();

	int change = (int)((openPrice - price)/precision_);
	if(0.0 == takeProfitPrice_)
	{
		takeProfitPrice_ = openPrice + (20.0 * precision_);
	}
	else if(change >= 30 && change > maxPipsChange_)
	{
		maxPipsChange_ = change;
		int takePips = change - 10;
		takeProfitPrice_ = openPrice - (takePips * precision_);
	}
   
	if(price > takeProfitPrice_)
	{
		return true;
	}
	else if(haClose > haOpen && change > 1)
	{
		return true;
	}

	return false;
}

bool FXPrimeExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	HACandle * haCandle = CandleStickManager::instance()->getLatestHACandleStick(symbol);
	double haOpen = haCandle->openPrice();
	double haClose = haCandle->closePrice();

	int change = (int)((price - openPrice)/precision_);
	if(0.0 == takeProfitPrice_)
	{
		takeProfitPrice_ = openPrice - (20.0 * precision_);
	}
	else if(change >= 30 && change > maxPipsChange_)
	{
		maxPipsChange_ = change;
		int takePips = change - 10;
//		if(longPosition_)
		takeProfitPrice_ = openPrice + (takePips * precision_);
	}
   
	if(price < takeProfitPrice_)
	{
		return true;
	}
	else if(haClose < haOpen && change > 1)
	{
		return true;
	}
	return false;
}

