// ATRExit.cpp: implementation of the ATRExit class.
//
//////////////////////////////////////////////////////////////////////

#include "ATRExit.h"
#include "ATRMetric.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ATRExit::ATRExit(long startTime, long endTime)
: ExitStrategy("2 * ATR Stop Loss", startTime, endTime)
{
}

ATRExit::~ATRExit()
{
}

bool ATRExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	double atr = getATR(symbol, 20);

	if(atr < .04)
	{
		atr = .04;
	}
	if(price > openPrice + (2.0 * atr))
	{
		return true;
	}
	return false;
}

bool ATRExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	double atr = getATR(symbol, 20);

	if(atr < .04)
	{
		atr = .04;
	}
	if(price < openPrice - (2.0 * atr))
	{
		return true;
	}
	return false;
}

