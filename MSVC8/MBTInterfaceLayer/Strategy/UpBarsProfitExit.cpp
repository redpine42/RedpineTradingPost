// UpBarsProfitExit.cpp: implementation of the UpBarsProfitExit class.
//
//////////////////////////////////////////////////////////////////////

#include "UpBarsProfitExit.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "ConsitentMove.h"
#include "PurchaseData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UpBarsProfitExit::UpBarsProfitExit(long startTime, long endTime)
: ExitStrategy("Two ticks!", startTime, endTime)
{
}

UpBarsProfitExit::~UpBarsProfitExit()
{

}

bool UpBarsProfitExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);

	if(stock->time() > (stock->openData()->timePlaced() + 120) && 
	   movesDown(symbol,2))
	{
		reason_ = "Two ticks Down!";
		return true;
	}
	return false;
}

bool UpBarsProfitExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);

	if(stock->time() > (stock->openData()->timePlaced() + 120) && 
	   movesUp(symbol,2))
	{
		reason_ = "Two ticks Up!";
		return true;
	}
	return false;
}

