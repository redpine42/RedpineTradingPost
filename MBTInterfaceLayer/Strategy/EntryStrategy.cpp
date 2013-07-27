// EntryStrategy.cpp: implementation of the EntryStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "EntryStrategy.h"
#include "ConfigurationData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EntryStrategy::EntryStrategy(StockWatch * stock, std::string reason, long startTradeTime, long endTradeTime)
	:reason_(reason),
	 stock_(stock),
	 newDay_(false),
	 startTradeTime_(startTradeTime),
	 endTradeTime_(endTradeTime)
{

}

EntryStrategy::~EntryStrategy()
{

}

bool EntryStrategy::isTradingTime(double time)
{	
	if(endTradeTime_ == startTradeTime_)
	{
		return true;
	}
	long locTime = TimeZone::instance()->getSecondsGMT();
	if(endTradeTime_ > startTradeTime_)
	{
		bool tradeTime = locTime < endTradeTime_ &&  // not close of market
						 locTime >= startTradeTime_;
		if(newDay_ && !tradeTime)
		{
			newTradeDay();
			newDay_ = false;
		}
		else if(!newDay_ && tradeTime)
		{
			newDay_ = true;
		}

		return tradeTime;
	}
	else
	{
		bool tradeTime = locTime >= startTradeTime_ ||
						 locTime < endTradeTime_;

		if(newDay_ && !tradeTime)
		{
			newTradeDay();
			newDay_ = false;
		}
		else if(!newDay_ && tradeTime)
		{
			newDay_ = true;
		}
		return tradeTime;
	}

}
