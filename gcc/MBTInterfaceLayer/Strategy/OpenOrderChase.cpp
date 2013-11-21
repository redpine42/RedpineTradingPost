// OpenOrderChase.cpp: implementation of the OpenOrderChase class.
//
//////////////////////////////////////////////////////////////////////

#include "OpenOrderChase.h"
#include "SymbolData.h"
#include "MsgProducer.h"
#include "PurchaseData.h"
#include "TimeZone.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const std::string myClassName = "OpenOrderChase";
OpenOrderChase::OpenOrderChase(SymbolData * stock)
: MonitorOpenOrder(stock)
{

}

OpenOrderChase::~OpenOrderChase()
{

}

DataEnums::PositionStatus OpenOrderChase::checkOpenOrder(long & positionTime)
{
	PurchaseData * openData = stock_->openData();

	if(TimeZone::instance()->getSecondsGMT() > (positionTime + 600) &&
		openData->status_ != PurchaseData::Canceled) 
    {
        // cancel the order
		openData->reason_ = "Limit not executed in 600 seconds";
		openData->status_ = PurchaseData::Canceled;

		std::string errMsg = "Canceling Order: ";
		errMsg += stock_->symbol();
		PositionMonitorManager::instance()->removePosition(stock_->symbol());

		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, errMsg);
		MsgProducer::instance()->cancelOrder(*openData);
    }
	return DataEnums::OpenOrderWaiting;
}

