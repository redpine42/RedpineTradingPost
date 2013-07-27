// NormalCloseMonitor.cpp: implementation of the NormalCloseMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "NormalCloseMonitor.h"
#include "SymbolData.h"
#include "PurchaseData.h"
#include "MsgProducer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const std::string myClassName = "NormalCloseMonitor";

NormalCloseMonitor::NormalCloseMonitor(SymbolData * stock, long startTradeTime, long endTradeTime)
	: MonitorCloseOrder(stock, startTradeTime, endTradeTime),
	  cancelingOrder_(false)
{

}

NormalCloseMonitor::~NormalCloseMonitor()
{

}
//////////////////////////////////////////////////////////////////////

DataEnums::PositionStatus NormalCloseMonitor::checkCloseClose(long & positionTime)
{
	PurchaseData * closeData = stock_->closeData();
	PurchaseData * openData = stock_->openData();

	if(openData->typeTrade_ == PurchaseData::Buy &&
			!tradeTime(stock_)  &&
			closeData->executionType_ != PurchaseData::MARKET)

	{
			closeData->executionType_ = PurchaseData::MARKET;
			closeData->reason_ = "End of Day Exit";
			closeData->price_ = stock_->bestBid();
			closeData->stopPrice_ = 0.0;
			closeData->stopLowerPrice_ = 0.0;
			closeData->stopUpperPrice_ = 0.0;
			closeData->typeTrade_ = PurchaseData::Sell;
			closeData->status_ = PurchaseData::Canceled;

			MsgProducer::instance()->sendOrder(*closeData);

			std::string msg = "Canceling Order: " + stock_->symbol();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

			if(closeData->status_ == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
			}

	}

	else if(openData->typeTrade_ == PurchaseData::SellShort &&
			!tradeTime(stock_)  &&
			closeData->executionType_ != PurchaseData::MARKET)

	{
			closeData->executionType_ = PurchaseData::MARKET;
			closeData->reason_ = "End of Day Exit";
			closeData->price_ = stock_->bestAsk();
			closeData->stopPrice_ = 0.0;
			closeData->stopLowerPrice_ = 0.0;
			closeData->stopUpperPrice_ = 0.0;
			closeData->typeTrade_ = PurchaseData::BuyToCover;
			closeData->status_ = PurchaseData::Canceled;

			MsgProducer::instance()->sendOrder(*closeData);

			std::string msg = "Canceling Order: " + stock_->symbol();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);

			if(closeData->status_ == PurchaseData::Canceled)
			{
				cancelingOrder_ = true;
			}
	}
	return DataEnums::CloseOrderWaiting;
}

