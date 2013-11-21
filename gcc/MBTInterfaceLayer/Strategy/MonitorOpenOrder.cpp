// MonitorOpenOrder.cpp: implementation of the MonitorOpenOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "MonitorOpenOrder.h"
#include "SymbolData.h"
#include "PurchaseData.h"
#include "PurchaseManager.h"
#include "MsgProducer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const std::string myClassName = "MonitorOpenOrder";

MonitorOpenOrder::MonitorOpenOrder(SymbolData * stock)
	: stock_(stock)
{

}

MonitorOpenOrder::~MonitorOpenOrder()
{

}

DataEnums::PositionStatus MonitorOpenOrder::openOrderWaiting(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * openData = stock_->openData();

	if(pOrd.eventName_ == "OnHistoryAdded")
	{
		openData->orderNumber_ = pOrd.orderNumber_;
	}
	if(pOrd.eventName_ == "OnHistoryAdded" &&
	   pOrd.status_ == "Executed")
	{
		openData->orderNumber_ = pOrd.orderNumber_;
		openData->sharesFilled_ = pOrd.quantityFilled_;
		openData->timeFilled_ = pOrd.time_;
		if(pOrd.quantityFilled_ < openData->size_)
		{
		    openData->sharesFilled_ = pOrd.quantityFilled_;
	        openData->status_ = PurchaseData::PartialFill;
		}
	    if(pOrd.quantityFilled_ == openData->size_)
		{
			openData->timeFilled_ = pOrd.time_;
			openData->price_ = pOrd.price_;

			std::string msg = "Open Filled: " + stock_->symbol();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

			openData->status_ = PurchaseData::Filled;
			return DataEnums::OpenFilled;
		}
	}
	else if(pOrd.eventName_ == "OnHistoryAdded" && 
			pOrd.status_ == "Order Cancelled")
	{
		if(stock_->openData()->sharesFilled_ == 0)
		{
			stock_->failedOrder("Open Order Canceled");
			return DataEnums::Canceled;
		}
		return DataEnums::OpenFilled;
	}
	else if(pOrd.status_ == "Order Reject") // Order canceled 
	{
		openData->status_ = PurchaseData::Failed;

		stock_->failedOrder("Open Order Rejected");
		return DataEnums::Rejected;
	}
	return DataEnums::OpenOrderWaiting;
}

DataEnums::PositionStatus MonitorOpenOrder::openFilled(PositionMonitorManager::OrderData& pOrd)
{
	PurchaseData * openData = stock_->openData();
	PurchaseData * closeData = stock_->closeData();

	if(0 == closeData && 
	   openData->typeTrade_ != pOrd.buySell_ &&
	   pOrd.eventName_ == "OnHistoryAdded" &&
	   pOrd.status_ == "Executed")
	{

	    closeData  = new PurchaseData();
		closeData->symbol_ = stock_->symbol();
		closeData->size_ = pOrd.quantity_;
		closeData->price_ = pOrd.price_;
		closeData->stopPrice_ = 0.0;
		closeData->stopLowerPrice_ = 0.0;
		closeData->stopUpperPrice_ = 0.0;
		closeData->status_ = PurchaseData::Sent;
		closeData->typeTrade_ = pOrd.buySell_;
		closeData->executionType_ = pOrd.execType_;
		closeData->timePlaced_ = stock_->time();
		closeData->date_ = stock_->date();

		stock_->closeData(closeData);

		if(0 == closeData)
		{
			return DataEnums::OpenFilled;
		}
		closeData->reason_ = "User Initiated Order";

		if(pOrd.quantityFilled_ == pOrd.quantity_)
		{
			std::string msg = "Operator Close Order filled: " + stock_->symbol();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

			closeData->status_ = PurchaseData::Filled;

			stock_->recordTrade();

			return DataEnums::CloseFilled;
		}
		return DataEnums::CloseOrderWaiting;
	}
	return DataEnums::OpenFilled;
}

