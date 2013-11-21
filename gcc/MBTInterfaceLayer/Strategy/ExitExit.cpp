// TPExit.cpp: implementation of the ATRExit class.
//
//////////////////////////////////////////////////////////////////////

#include "ExitExit.h"
#include "SymbolData.h"
#include "SymbolDataList.h"
#include "PurchaseData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExitExit::ExitExit(std::string & symbol,long startTime, long endTime)
: ExitStrategy("Exit Exit", startTime, endTime)
{
}

ExitExit::~ExitExit()
{
}

bool ExitExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
	PurchaseData * openData = stock->openData();
	if(0 == openData || openData->status_ != PurchaseData::Filled)
	{
		return false;
	}
	return true;
}

bool ExitExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
	PurchaseData * openData = stock->openData();
	if(0 == openData || openData->status_ != PurchaseData::Filled)
	{
		return false;
	}
	return true;
}

