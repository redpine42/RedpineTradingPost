// MatchBidPrice.cpp: implementation of the MatchBidPrice class.
//
//////////////////////////////////////////////////////////////////////

#include "MatchBidPrice.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MatchBidPrice::MatchBidPrice(int pipsTrail)
: pipsTrail_(pipsTrail)
{

}

MatchBidPrice::~MatchBidPrice()
{

}

PriceStrategy::PricingData MatchBidPrice::buy(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = stock->bestBid() + precision;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MatchBidPrice::sellShort(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = stock->bestAsk() - precision;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MatchBidPrice::buyToCover(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;//MARKET_TRAIL;
	data.price = stock->getLastPrice() + precision;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;//pipsTrail_ * precision;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData MatchBidPrice::sell(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double precision = ConfigurationData::instance()->precision(symbol);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::LIMIT;//MARKET_TRAIL;
	data.price = stock->getLastPrice() - precision;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;//pipsTrail_ * precision;
	data.stopUpperPrice = 0.0;

	return data;
}
