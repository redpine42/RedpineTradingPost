// MaxDDSizing.cpp: implementation of the MaxDDSizing class.
//
//////////////////////////////////////////////////////////////////////

#include "MyMaxDDSizing.h"
#include "AccountManager.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "CandleStickManager.h"
#include "ConfigurationData.h"
#include "PairPricing.h"
#include "DataLogger.h"
#include <strstream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyMaxDDSizing::MyMaxDDSizing(MaxDDData * data)
	: maxDDData_(data)
{
}

MyMaxDDSizing::~MyMaxDDSizing()
{

}
int MyMaxDDSizing::buy(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}


int MyMaxDDSizing::sellShort(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}

int MyMaxDDSizing::calculateSize(const std::string & symbol, const double price)
{
	long quantity = 0;

	double pairPrice = PairPricing::instance()->getUSDCost(symbol, price);
	double pipValue = PairPricing::instance()->getUSDPipVal(symbol, price);

	double winLoss = (double)maxDDData_->numWins_/(double)maxDDData_->numTrades_;
	double equity = AccountManager::instance()->getEquity();
	if(equity < 500.0)
	{
		equity = 0.0;
	}

	double winRisk = winLoss * equity;
	double allowedRisk = winRisk * maxDDData_->percentRisk_;

	int maxLotsToRisk = (int)((allowedRisk/100.0)/pairPrice);
	int lotsToRisk = maxLotsToRisk;
	if(pipValue != 0 && maxDDData_->maxDDPips_ != 0)
	{
		lotsToRisk = (int)(allowedRisk/(pipValue * (double)maxDDData_->maxDDPips_));
	}
	if(lotsToRisk < maxLotsToRisk)
	{
		quantity = lotsToRisk * 10000;
	}
	else
	{
		quantity = maxLotsToRisk * 10000;
	}
	
	if(quantity > 2000000)
	{
		quantity = 2000000;
	}
    std::strstream strstr;
	strstr << "\n\nNew DD Sizing\nPair Price: " << pairPrice 
		   << "\nMax DD Pips: " << maxDDData_->maxDDPips_
		   << "\nPercent Risk: " << maxDDData_->percentRisk_ 
		   << "\nPip Value: " << pipValue 
		   << "\nWin Loss: " << winLoss 
		   << "\nEquity: " << equity 
		   << "\nAllowed Risk: " << allowedRisk 
		   << "\nMax Lots To Risk: " << maxLotsToRisk 
		   << "\nLots To Risk: " << lotsToRisk 
		   << "\nQuantity Lots: " << quantity <<std::ends;
	std::string  msg = strstr.str();
	strstr.clear();
    strstr.rdbuf()->freeze(0);

	DataLogger::instance()->recordDebug(msg, symbol);

    return quantity;
}


