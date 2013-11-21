// ExitStrategy.cpp: implementation of the ExitStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "ExitStrategy.h"
#include "TimeZone.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExitStrategy::ExitStrategy(std::string reason, long startTradeTime, long endTradeTime)
	: reason_(reason),
	  startTradeTime_(startTradeTime),
	  endTradeTime_(endTradeTime)
{

}

ExitStrategy::~ExitStrategy()
{

}

bool ExitStrategy::tradeTime()
{
	if(endTradeTime_ == startTradeTime_)
	{
		return true;
	}
	long time = TimeZone::instance()->getSecondsGMT();

	if(endTradeTime_ > startTradeTime_)
	{
		return (time < endTradeTime_ &&  // not close of market
			    time > startTradeTime_);
	}
	else
	{
		return (time > startTradeTime_ ||
			    time < endTradeTime_);
	}

}
