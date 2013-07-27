// COTLMonitorOpenOrder.cpp: implementation of the COTLMonitorOpenOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "COTLMonitorOpenOrder.h"
#include "StockWatch.h"
#include "PurchaseData.h"
#include "ConfigurationData.h"
#include "DataLogger.h"
#include "OrderManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COTLMonitorOpenOrder::COTLMonitorOpenOrder(StockWatch * stock,double pipsStopLoss)
	: MonitorOpenOrder(stock),
	  pipsStopLoss_(pipsStopLoss)
{

}

COTLMonitorOpenOrder::~COTLMonitorOpenOrder()
{

}

PositionStatus COTLMonitorOpenOrder::openOrderWaiting(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * openData = stock_->openData();
	PositionStatus status = MonitorOpenOrder::openOrderWaiting(pOrd);
	double precision = ConfigurationData::instance()->precision(stock_->symbol());

	if(status == OpenFilled &&
	   openData->executionType() != PurchaseData::MARKET_TTO)
	{
		PurchaseData * closeData = new PurchaseData(*openData);

		stock_->closeData(closeData);
		double newPrice = openData->price();

		if(pOrd.buySell_ == PurchaseData::Buy)
		{
			newPrice -= pipsStopLoss_ * precision;
			closeData->typeTrade(PurchaseData::Sell);
		}
		else if(pOrd.buySell_ == PurchaseData::SellShort)
		{
			newPrice +=  pipsStopLoss_ * precision;
			closeData->typeTrade(PurchaseData::BuyToCover);
		}
	
		closeData->executionType(PurchaseData::STOP_MARKET);
		closeData->reason("User Initiated Order - Stop Loss");
		closeData->price(newPrice);
		closeData->stopPrice(newPrice);
		closeData->stopLowerPrice(0.0);
		closeData->stopUpperPrice(0.0);
		DataLogger::instance()->recordDebug("Creating Stop Market Order: ", stock_->symbol());
		closeData->tradeStatus(PurchaseData::Sent);

		OrderManager::instance()->makeOrder(closeData);

	}
	return status;
}

PositionStatus COTLMonitorOpenOrder::openFilled(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();

	if(0 == closeData && 
	   pOrd.eventName_ == "OnSubmit" &&
	   openData->executionType() == PurchaseData::MARKET_TTO )
	{
		closeData = new PurchaseData(*openData);
		stock_->closeData(closeData);
		closeData->orderNumber(pOrd.orderNumber_);
		closeData->reason("Stop Loss");
		return CloseOrderWaiting;
	}
	else if(0 != closeData &&
			pOrd.eventName_ == "OnSubmit" &&
			(closeData->executionType() == PurchaseData::STOP_MARKET ||
			 closeData->executionType() == PurchaseData::MARKET))
	{
		closeData->orderNumber(pOrd.orderNumber_);
		return CloseOrderWaiting;
	}
	return OpenFilled;
}


PositionStatus COTLMonitorOpenOrder::checkOpenOrder(long & positionTime)
{
	return OpenOrderWaiting;
}

