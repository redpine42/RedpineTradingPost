// SPEntry.cpp: implementation of the SPEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "SPEntry.h"
#include "Hilbert.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SPEntry::SPEntry(StockWatch * stock)
	: EntryStrategy(stock, "Signal Process Entry")
{

}

SPEntry::~SPEntry()
{

}

bool SPEntry::buy()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	std::string symbol = stock_->symbol();

	if(!isTrendMode(symbol))
	{
		if(getPhase(symbol) == PhaseOne)
		{
			return true;
		}
	}
	return false;
}

bool SPEntry::sellShort()
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	std::string symbol = stock_->symbol();

	if(!isTrendMode(symbol))
	{
		if(getPhase(symbol) == PhaseThree)
		{
			return true;
		}
	}
	return false;
}

