// MarketPrice.cpp: implementation of the MarketPrice class.
//
//////////////////////////////////////////////////////////////////////

#include "MarketTPLimitPrice.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "PurchaseData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MarketTPLimitPrice::MarketTPLimitPrice(double takeProfitPips)
: takeProfitPips_(takeProfitPips)
{

}

MarketTPLimitPrice::~MarketTPLimitPrice()
{

}

PriceStrategy::PricingData MarketTPLimitPrice::buy(const std::string & symbol)
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

PriceStrategy::PricingData MarketTPLimitPrice::sellShort(const std::string & symbol)
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

PriceStrategy::PricingData MarketTPLimitPrice::buyToCover(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double openPrice = stock->openData()->price();

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = openPrice - takeProfitPips_;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MarketTPLimitPrice::sell(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double openPrice = stock->openData()->price();

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = openPrice + takeProfitPips_;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}
