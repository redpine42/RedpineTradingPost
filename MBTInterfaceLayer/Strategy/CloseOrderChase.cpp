// CloseOrderChase.cpp: implementation of the CloseOrderChase class.
//
//////////////////////////////////////////////////////////////////////

#include "CloseOrderChase.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "OrderManager.h"
#include "DataLogger.h"
#include "TimeZone.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CloseOrderChase::CloseOrderChase(StockWatch * stock, long startTradeTime, long endTradeTime)
	: MonitorCloseOrder(stock, startTradeTime, endTradeTime)
{

}

CloseOrderChase::~CloseOrderChase()
{

}

PositionStatus CloseOrderChase::checkCloseClose(long & positionTime)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();


	if(TimeZone::instance()->getSecondsGMT() > closeData->timePlaced() + 600.0 &&
		openData->typeTrade() == PurchaseData::Buy &&
		closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("Limit not executed in 5 minutes");
			closeData->price(stock_->bestBid());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::Sell);
			closeData->tradeStatus(PurchaseData::Canceled);
			cancelOrder_ = true;

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}

	else if(TimeZone::instance()->getSecondsGMT() > closeData->timePlaced() + 600.0 &&
			openData->typeTrade() == PurchaseData::SellShort &&
			closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("Limit not executed in 5 minutes");
			closeData->price(stock_->bestAsk());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::BuyToCover);
			closeData->tradeStatus(PurchaseData::Canceled);
			cancelOrder_ = true;

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}
	return CloseOrderWaiting;
}

