// COTLPriceStrategy.cpp: implementation of the COTLPriceStrategy class.
//
//////////////////////////////////////////////////////////////////////

#include "COTLPriceStrategy.h"

#include <strstream>
#include "StockWatchList.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"
#include "DataLogger.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COTLPriceStrategy::COTLPriceStrategy(double pipsStopLoss)
	: pipsStopLoss_(pipsStopLoss)
{

}

COTLPriceStrategy::~COTLPriceStrategy()
{

}
PriceStrategy::PricingData COTLPriceStrategy::buy(const std::string & symbol)
{
	double precision = ConfigurationData::instance()->precision(symbol);

	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double ask = stock->bestAsk();

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET_TTO;
	data.price = ask;
	data.stopPrice = ask;
	data.stopLowerPrice = ask - (pipsStopLoss_ * precision);
	data.stopUpperPrice = 2 * ask;

    std::strstream strstr;
    strstr << "Ask Price: " << ask << "\nBuy Price: " << data.price << "\nStop Loss: " << data.stopLowerPrice << std::ends;
	std::string  msg = strstr.str();
    strstr.clear();
    strstr.rdbuf()->freeze(0);

	DataLogger::instance()->recordDebug(msg, symbol);
	return data;
}

PriceStrategy::PricingData COTLPriceStrategy::sellShort(const std::string & symbol)
{
	double precision = ConfigurationData::instance()->precision(symbol);

	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double bid = stock->bestBid();

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET_TTO;
	data.price = bid;
	data.stopPrice = bid;
	data.stopLowerPrice = bid + (pipsStopLoss_ * precision);
	data.stopUpperPrice = 0.5 * bid;

    std::strstream strstr;
    strstr << "Bid Price: " << bid << "\nBuy Price: " << data.price << "\nStop Loss: " << data.stopLowerPrice << std::ends;
	std::string  msg = strstr.str();
    strstr.clear();
    strstr.rdbuf()->freeze(0);

	DataLogger::instance()->recordDebug(msg, symbol);
	return data;
}

PriceStrategy::PricingData COTLPriceStrategy::buyToCover(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double bid = stock->bestBid();
	double ask = stock->bestAsk();
	double spread = ask - bid;
	long lPrice = (long)((stock->bestBid())*10000.0);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET;
	data.price = lPrice/10000.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}

PriceStrategy::PricingData COTLPriceStrategy::sell(const std::string & symbol)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	double bid = stock->bestBid();
	double ask = stock->bestAsk();
	double spread = ask - bid;
	long lPrice = (long)((stock->bestAsk())*10000.0);

	PriceStrategy::PricingData data;
	data.tradeType = PurchaseData::MARKET;
	data.price = lPrice/10000.0;
	data.stopPrice = 0.0;
	data.stopLowerPrice = 0.0;
	data.stopUpperPrice = 0.0;

	return data;
}
