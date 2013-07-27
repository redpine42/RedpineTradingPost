// EqualPriceQuantity.cpp: implementation of the EqualPriceQuantity class.
//
//////////////////////////////////////////////////////////////////////

#include "EqualPriceQuantity.h"
#include "AccountManager.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "ConfigurationData.h"
#include "PairPricing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EqualPriceQuantity::EqualPriceQuantity()
{

}

EqualPriceQuantity::~EqualPriceQuantity()
{

}

int EqualPriceQuantity::buy(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}


int EqualPriceQuantity::sellShort(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}

int EqualPriceQuantity::calculateSize(const std::string & symbol, const double price)
{
	// Check for default size usage
	int defaultLotSize = ConfigurationData::instance()->defaultLotSize(symbol);
	if(defaultLotSize > 0)
	{
		// Amount returned is always base pair dollars
		return defaultLotSize * 10000;
	}
	else if (defaultLotSize == 0)
	{
		return 0;
	}
	long quantity = 0;

    double startBP = AccountManager::instance()->getStartBuyingPower();
    double BP = AccountManager::instance()->getBP();

    double thisBP = startBP/5.0;

	//  Is there enough buying power
	if(thisBP < BP)
	{
		double pairPrice = PairPricing::instance()->getUSDCost(symbol, price);
		thisBP = thisBP/pairPrice;

		// round quantity to even lot size
		quantity = (long)(thisBP/10000.0);
		quantity = quantity * 10000;
	}
	// Quantity is in base pair currency.
    return quantity;
}

