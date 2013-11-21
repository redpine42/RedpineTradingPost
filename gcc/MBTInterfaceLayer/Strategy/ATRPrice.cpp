// ATRPrice.cpp: implementation of the ATRPrice class.
//
//////////////////////////////////////////////////////////////////////

#include "ATRPrice.h"
#include "StockWatchList.h"
#include "StockWatch.h"
#include "ATRMetric.h"
#include "PurchaseData.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ATRPrice::ATRPrice()
{

}

ATRPrice::~ATRPrice()
{

}

PriceStrategy::PricingData ATRPrice::buy(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double atr = 0.5 * getATR(symbol, 20);
	long lPrice = (long)((stock->bestBid() - atr)*100.0);

	PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = lPrice/100.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData ATRPrice::sellShort(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double atr = 0.5 * getATR(symbol, 20);
	long lPrice = (long)((stock->bestAsk() - atr)*100.0);

	PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = lPrice/100.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData ATRPrice::buyToCover(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double atr = 0.5 * getATR(symbol, 20);
	long lPrice = (long)((stock->bestBid() + atr)*100.0);

	PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = lPrice/100.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData ATRPrice::sell(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double atr = 0.5 * getATR(symbol, 20);
	long lPrice = (long)((stock->bestAsk() + atr)*100.0);

	PricingData data;
	data.tradeType = PurchaseData::LIMIT;
	data.price = lPrice/100.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}
