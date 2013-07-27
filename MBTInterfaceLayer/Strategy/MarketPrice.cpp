// MarketPrice.cpp: implementation of the MarketPrice class.
//
//////////////////////////////////////////////////////////////////////

#include "MarketPrice.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "PurchaseData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MarketPrice::MarketPrice()
{

}

MarketPrice::~MarketPrice()
{

}

PriceStrategy::PricingData MarketPrice::buy(const std::string & symbol)
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

PriceStrategy::PricingData MarketPrice::sellShort(const std::string & symbol)
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

PriceStrategy::PricingData MarketPrice::buyToCover(const std::string & symbol)
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

PriceStrategy::PricingData MarketPrice::sell(const std::string & symbol)
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
