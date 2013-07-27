// COTLMonitorCloseOrder.cpp: implementation of the COTLMonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "COTLMonitorCloseOrder.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"
#include "OrderMaker.h"
#include "DataLogger.h"
#include "OrderManager.h"

#include "MACDMetric.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COTLMonitorCloseOrder::COTLMonitorCloseOrder(StockWatch * stock, double trailOnceStopLossTrigger, double trailOnceStopLoss, long startTradeTime, long endTradeTime)
	: MonitorCloseOrder(stock, startTradeTime, endTradeTime),
	  cancelingOrder_(false),
	  MACDExit_(false),
	  stopLossWait_(false)
{
	double precision = ConfigurationData::instance()->precision(stock_->symbol());
	trailOnceStopLossTrigger_ = trailOnceStopLossTrigger * precision;
	trailOnceStopLoss_ = trailOnceStopLoss * precision;
}

COTLMonitorCloseOrder::~COTLMonitorCloseOrder()
{

}

PositionStatus COTLMonitorCloseOrder::checkCloseClose(long & positionTime)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();

	if(!stopLossWait_)
	{
		if(openData->typeTrade() == PurchaseData::Buy &&
			stock_->bestAsk() > openData->price() + trailOnceStopLossTrigger_  && stock_->bestAsk() != 0.0)
		{
			double newPrice = openData->price() + trailOnceStopLoss_;

			closeData->executionType(PurchaseData::STOP_MARKET);
			closeData->reason("Trail Once Stop Loss");
			closeData->price(newPrice);
			closeData->stopPrice(newPrice);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::Sell);
			closeData->tradeStatus(PurchaseData::Canceled);
			closeData->timePlaced(positionTime);

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
				stopLossWait_ = true;
			}
			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
		}
		else if(openData->typeTrade() == PurchaseData::SellShort &&
			    stock_->bestBid() < openData->price() - trailOnceStopLossTrigger_  && stock_->bestBid() != 0.0)
		{
			double newPrice = openData->price() - trailOnceStopLoss_;
	
			closeData->executionType(PurchaseData::STOP_MARKET);
			closeData->reason("Trail Once Stop Loss");
			closeData->price(newPrice);
			closeData->stopPrice(newPrice);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::BuyToCover);
			closeData->tradeStatus(PurchaseData::Canceled);
			closeData->timePlaced(positionTime);


			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
				stopLossWait_ = true;
			}
			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
		}
	}
	else if(openData->typeTrade() == PurchaseData::Buy &&
		MACD3DropExit(stock_) &&
			closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("MACD Exit");
			closeData->price(stock_->bestBid());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::Sell);
			closeData->tradeStatus(PurchaseData::Canceled);

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				MACDExit_ = true;
			}
			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}

	else if(openData->typeTrade() == PurchaseData::SellShort &&
		    MACD3RiseExit(stock_) &&
			closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("MACD Exit");
			closeData->price(stock_->bestAsk());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::BuyToCover);
			closeData->tradeStatus(PurchaseData::Canceled);

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				MACDExit_ = true;
			}

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}
	if(openData->typeTrade() == PurchaseData::Buy &&
			!tradeTime(stock_)  &&
			closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("End of Day Exit");
			closeData->price(stock_->bestBid());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::Sell);
			closeData->tradeStatus(PurchaseData::Canceled);

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
			}

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}

	else if(openData->typeTrade() == PurchaseData::SellShort &&
			!tradeTime(stock_)  &&
			closeData->executionType() != PurchaseData::MARKET)

	{
			closeData->executionType(PurchaseData::MARKET);
			closeData->reason("End of Day Exit");
			closeData->price(stock_->bestAsk());
			closeData->stopPrice(0.0);
			closeData->stopLowerPrice(0.0);
			closeData->stopUpperPrice(0.0);
			closeData->typeTrade(PurchaseData::BuyToCover);
			closeData->tradeStatus(PurchaseData::Canceled);

			DataLogger::instance()->recordDebug("Canceling Order: ", stock_->symbol());
			OrderMaker::instance()->cancelOrder(closeData);
			if(closeData->tradeStatus() == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
			}
			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
	}
	return CloseOrderWaiting;
}

PositionStatus COTLMonitorCloseOrder::closeOrderWaiting(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * closeData = stock_->closeData();

	if(pOrd.eventName_ == "OnHistoryAdded" &&
	   pOrd.status_ == "Executed")
	{
		closeData->sharesFilled(pOrd.quantityFilled_);
		closeData->orderNumber(pOrd.orderNumber_);
		closeData->price(pOrd.price_);
		closeData->timeFilled(pOrd.time_);

		if(pOrd.quantityFilled_ > 0)
		{
		    closeData->sharesFilled(pOrd.quantityFilled_);
	        closeData->tradeStatus(PurchaseData::PartialFill);
		}
	    if(pOrd.quantityFilled_ == pOrd.quantity_)
		{
			DataLogger::instance()->recordDebug("Close Order filled: ", stock_->symbol());

	        closeData->tradeStatus(PurchaseData::Filled);

			stock_->recordTrade();

			return CloseFilled;
		}
	}
	else if(pOrd.eventName_ == "OnHistoryAdded" && 
			pOrd.status_ == "Order Cancelled" &&
			cancelingOrder_)
	{
		DataLogger::instance()->recordDebug("Close Order Canceled: ", stock_->symbol());
		closeData->tradeStatus(PurchaseData::Sent);

		OrderManager::instance()->makeOrder(closeData);
		cancelingOrder_ = false;
		return OpenFilled;
	}
	else if(pOrd.eventName_ == "OnHistoryAdded" && 
			pOrd.status_ == "Order Cancelled" &&
			MACDExit_)
	{
		DataLogger::instance()->recordDebug("Close Order Canceled: ", stock_->symbol());
		closeData->tradeStatus(PurchaseData::Sent);

		OrderManager::instance()->makeOrder(closeData);
		MACDExit_ = false;
		return OpenFilled;
	}
	else if(pOrd.status_ == "Cancel Reject")
	{
		DataLogger::instance()->recordDebug("Cancel Order Rejected: ", stock_->symbol());
		delete closeData;
		closeData = 0;
		stock_->closeData(0);
		return Rejected;
	}
	else if(pOrd.status_ == "Order Reject")
	{
		DataLogger::instance()->recordDebug("Close Order Rejected: ", stock_->symbol());
		delete closeData;
		closeData = 0;
		stock_->closeData(0);
		return Rejected;
	}
	return CloseOrderWaiting;
}
