// HalfBarPrice.cpp: implementation of the HalfBarPrice class.
//
//////////////////////////////////////////////////////////////////////

#include "HalfBarPrice.h"
#include "CandleStickManager.h"
#include "CandleStick.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"
#include "StockWatch.h"
#include "StockWatchList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HalfBarPrice::HalfBarPrice()
{

}

HalfBarPrice::~HalfBarPrice()
{

}

PriceStrategy::PricingData HalfBarPrice::buy(const std::string & symbol)
{
	CandleStick * stick = CandleStickManager::instance()->getLatestCandleStick(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);
	double price = (stick->closePrice() + stick->openPrice())/2.0;
	long lPrice = (long)(price/precision);
	price = lPrice * precision;


	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = price;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData HalfBarPrice::sellShort(const std::string & symbol)
{
	CandleStick * stick = CandleStickManager::instance()->getLatestCandleStick(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);
	double price = (stick->closePrice() + stick->openPrice())/2.0;
	long lPrice = (long)(price/precision);
	price = lPrice * precision;

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = price;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData HalfBarPrice::buyToCover(const std::string & symbol)
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

PriceStrategy::PricingData HalfBarPrice::sell(const std::string & symbol)
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
