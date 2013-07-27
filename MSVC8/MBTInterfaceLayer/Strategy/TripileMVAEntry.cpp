// TripileMVAEntry.cpp: implementation of the TripileMVAEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "TripileMVAEntry.h"
#include "EMAMetric.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TripileMVAEntry::TripileMVAEntry(StockWatch * stock, long fast, long medium, long slow, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "Tripile Moving Average Entry", startTradeTime, endTradeTime),
	  fast_(fast),
	  medium_(medium),
	  slow_(slow)
{

}

TripileMVAEntry::~TripileMVAEntry()
{

}


bool TripileMVAEntry::buy()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	std::string symbol = stock_->symbol();

	double fastMVA = getEMA(symbol, fast_);
	double mediumMVA = getEMA(symbol, medium_);
	double slowMVA = getEMA(symbol, slow_);

	if(fastMVA > mediumMVA  && mediumMVA >  slowMVA)
	{
		return true;
	}
	return false;
}

bool TripileMVAEntry::sellShort()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	std::string symbol = stock_->symbol();

	double fastMVA = getEMA(symbol, fast_);
	double mediumMVA = getEMA(symbol, medium_);
	double slowMVA = getEMA(symbol, slow_);

	if(fastMVA < mediumMVA  && mediumMVA < slowMVA)
	{
		return true;
	}
	return false;
}

