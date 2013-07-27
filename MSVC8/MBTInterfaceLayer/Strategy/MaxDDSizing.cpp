// MaxDDSizing.cpp: implementation of the MaxDDSizing class.
//
//////////////////////////////////////////////////////////////////////

#include "MaxDDSizing.h"
#include "AccountManager.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "CandleStickManager.h"
#include "ConfigurationData.h"
#include "PairPricing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MaxDDSizing::MaxDDSizing(MaxDDMSAData * data)
: margPer_(data->marginPercentage_),
  maxDDPer_(data->maxDDPercent_),
  maxDD_(data->maxHistDrawDown_)
{
	if(maxDDPer_ == 0.0)
	{
		maxDDPer_ = .00001;
	}
	if(maxDD_ == 0)
	{
		maxDD_ = 1.0;
	}
}

MaxDDSizing::~MaxDDSizing()
{

}
int MaxDDSizing::buy(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}


int MaxDDSizing::sellShort(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}

int MaxDDSizing::calculateSize(const std::string & symbol, const double price)
{

	double pairPrice = PairPricing::instance()->getUSDCost(symbol, price);

	std::string lSymbol = symbol;
	long quantity = 0;

 	MaxDDMSAData * data = ConfigurationData::instance()->msaData(symbol);
    double equity = data->currentEquity_;
    double BP = AccountManager::instance()->getBP();

	CandleStick * stick = CandleStickManager::instance()->getCandleStick(lSymbol);

	double margPerSz = pairPrice * margPer_/100.0;
//	double thisBP = (equity - margPerSz)/(0.01 * maxDDPer_ * maxDD_);
//	double thisBP = (equity - (maxDD_ * maxDDPer_/100.0)/(margPer_ * 100.0 * pairPrice));
	double thisBP = (equity - (maxDDPer_ * 0.01 *(equity * maxDD_))) * (100.0/margPer_);

	if(thisBP < 0.0)
	{
		return 0;
	}
	if(thisBP > equity/margPerSz)
	{
		thisBP = equity/margPerSz;
	}
	if(thisBP < BP)
	{
		thisBP = thisBP/pairPrice;
		quantity = (long)(thisBP/10000.0);
		quantity = quantity * 10000;

	}
    return quantity;
}


