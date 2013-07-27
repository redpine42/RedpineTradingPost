// TPSLMonitorClose.cpp: implementation of the TPSLMonitorClose class.
//
//////////////////////////////////////////////////////////////////////

#include "TPSLMonitorClose.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "OrderManager.h"
#include "DataLogger.h"
#include "TimeZone.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TPSLMonitorClose::TPSLMonitorClose(StockWatch * stock, long startTradeTime, long endTradeTime,double pipsStopLoss)
	: MonitorCloseOrder(stock, startTradeTime, endTradeTime),
	  pipsStopLoss_(pipsStopLoss)
{

}

TPSLMonitorClose::~TPSLMonitorClose()
{

}

PositionStatus TPSLMonitorClose::checkCloseClose(long & positionTime)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();
	double currTime = stock_->time();
	double openPrice = stock_->openData()->price();
	double price = stock_->getLastPrice();


	if(openData->typeTrade() == PurchaseData::Buy &&
	    closeData->executionType() != PurchaseData::MARKET && 
		stock_->bestAsk() < openPrice - pipsStopLoss_)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("Stop Loss Executed");
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

	else if(openData->typeTrade() == PurchaseData::SellShort &&
	         closeData->executionType() != PurchaseData::MARKET && 
	         stock_->bestBid() > openPrice + pipsStopLoss_)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("Stop Loss Executed");
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

