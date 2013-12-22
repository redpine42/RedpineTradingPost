// MonitorCloseOrder.cpp: implementation of the MonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "MonitorCloseOrder.h"
#include "SymbolData.h"
#include "PurchaseData.h"
#include "PurchaseManager.h"
#include "TimeWrapper.h"
#include "MsgProducer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const std::string myClassName = "MonitorCloseOrder";

MonitorCloseOrder::MonitorCloseOrder(SymbolData * stock, long startTradeTime, long endTradeTime)
	: stock_(stock),
	  startTradeTime_(startTradeTime),
	  endTradeTime_(endTradeTime)
{

}

MonitorCloseOrder::~MonitorCloseOrder()
{

}

DataEnums::PositionStatus MonitorCloseOrder::closeOrderWaiting(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();

	if(pOrd.eventName_ == "OnHistoryAdded")
	{
		closeData->orderNumber_ = pOrd.orderNumber_;
	}
	if(pOrd.eventName_ == "OnHistoryAdded" &&
	   pOrd.status_ == "Executed")
	{
		closeData->sharesFilled_= pOrd.quantityFilled_;
		closeData->orderNumber_ = pOrd.orderNumber_;
		closeData->price_ = pOrd.price_;
		closeData->timeFilled_ = pOrd.time_;

		if(pOrd.quantityFilled_ < openData->size_)
		{
		    closeData->sharesFilled_ = pOrd.quantityFilled_;
	        closeData->status_ = PurchaseData::PartialFill;
		}
	    if(pOrd.quantityFilled_ == openData->size_)
		{
			std::string msg = "Close Order filled: " + stock_->symbol();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

	        closeData->status_ = PurchaseData::Filled;

			stock_->recordTrade();

			return DataEnums::CloseFilled;
		}
	}
	else if(pOrd.eventName_ == "OnHistoryAdded" && 
			pOrd.status_ == "Order Cancelled" && 
			cancelOrder_)
	{
		std::string msg = "Close Order Canceled: " + stock_->symbol();
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);
		closeData->status_= PurchaseData::Sent;

		MsgProducer::instance()->sendOrder(*closeData);
		cancelOrder_ = false;
		return DataEnums::CloseOrderWaiting;
	}
	else if(pOrd.status_ == "Cancel Reject")
	{
		std::string msg = "Close Order Rejected: " + stock_->symbol();
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

		delete closeData;
		closeData = 0;
		stock_->closeData(0);
		return DataEnums::Rejected;
	}
	else if(pOrd.status_ == "Order Reject")
	{
		std::string msg = "Close Order Rejected: " + stock_->symbol();
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

		delete closeData;
		closeData = 0;
		stock_->closeData(0);
		return DataEnums::Rejected;
	}
	return DataEnums::CloseOrderWaiting;
}

bool MonitorCloseOrder::tradeTime(SymbolData * stock)
{
	if(endTradeTime_ == startTradeTime_)
	{
		return true;
	}
	long time = TimeWrapper::instance()->getSecondsGMT();

	if(endTradeTime_ > startTradeTime_)
	{
		return (time < endTradeTime_ &&  // not close of market
			    time > startTradeTime_);
	}
	else
	{
		return (time > startTradeTime_ ||
			    time < endTradeTime_);
	}

}
