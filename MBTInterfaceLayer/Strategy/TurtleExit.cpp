// TurtleExit.cpp: implementation of the TurtleExit class.
//
//////////////////////////////////////////////////////////////////////

#include "TurtleExit.h"
#include "MaxMin.h"
#include "StockWatchList.h"
#include "StockWatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TurtleExit::TurtleExit(long startTime, long endTime)
:ExitStrategy("Turtle Exit - 10 bar breakdown", startTime, endTime)
{
}

TurtleExit::~TurtleExit()
{
}
	
bool TurtleExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double localPrice = price;
	if(price > stock->bestAsk())
	{
		localPrice = stock->bestAsk();
	}
	double max = getMax(symbol, 10);

	if(localPrice > max)
	{
		return true;
	}
	return false;
}

bool TurtleExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double localPrice = price;
	if(price < stock->bestBid())
	{
		localPrice = stock->bestBid();
	}
	double min = getMin(symbol, 10);
	if(localPrice < min)
	{
		return true;
	}
	return false;
}


