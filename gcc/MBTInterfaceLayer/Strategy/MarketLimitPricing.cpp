// MarketLimitPricing.cpp: implementation of the MarketLimitPricing class.
//
//////////////////////////////////////////////////////////////////////

#include "MarketLimitPricing.h"

#include "StockWatchList.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MarketLimitPricing::MarketLimitPricing()
{

}

MarketLimitPricing::~MarketLimitPricing()
{

}

PriceStrategy::PricingData MarketLimitPricing::buy(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	
	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET;
	data.price = stock->bestAsk();
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MarketLimitPricing::sellShort(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET;
	data.price = stock->bestBid();
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MarketLimitPricing::buyToCover(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;//MARKET_TRAIL;
	data.price = stock->getLastPrice();
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MarketLimitPricing::sell(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;//MARKET_TRAIL;
	data.price = stock->getLastPrice();
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}
