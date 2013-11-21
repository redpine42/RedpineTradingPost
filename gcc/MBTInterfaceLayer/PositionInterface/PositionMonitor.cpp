#include "PositionMonitor.h"
#include "SymbolData.h"
#include "PurchaseData.h"
#include "PurchaseManager.h"
#include "DataEnums.h"
#include "MsgProducer.h"

#include "ExitStrategy.h"
#include "MonitorOpenOrder.h"
#include "MonitorCloseOrder.h"
#include "MonitorCloseOrderFactory.h"
#include "MonitorOpenOrderFactory.h"
#include "ExitStrategyFactory.h"

PositionMonitor::PositionMonitor(SymbolData * stock, PurchaseData * data)
    : stock_(stock),
	  positionTime_(stock->time()),
      openData_(data),
      closeData_(0),
	  posStatus_(DataEnums::OpenOrderWaiting),
	  startPrice_(data->price_)
{

	reason_ = "Close Trigger";

	exitStrategy_ = ExitStrategyFactory::instance()->getStrategy(stock);

	monitorOpen_ = MonitorOpenOrderFactory::instance()->getMonitorOpenOrder(stock);
	monitorClose_ = MonitorCloseOrderFactory::instance()->getMonitorCloseOrder(stock);
}

void PositionMonitor::closePosition(SymbolData * stock, PurchaseData * data)
{
    positionTime_ = stock->time();
	data->reason_ = reason_;

	if(posStatus_ == DataEnums::OpenFilled)
    {
	    posStatus_ = DataEnums::CloseOrderWaiting;
        closeData_ = data;
		MsgProducer::instance()->sendOrder(*data);
	}
	else if(posStatus_ == DataEnums::OpenOrderWaiting)
	{
        MsgProducer::instance()->cancelOrder(*openData_);
		std::string errMsg = "Order not filled before close Trigger";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::POSITIONMONITOR, errMsg);
	}
}

void PositionMonitor::checkPosition()
{
    if(0 != monitorOpen_ && posStatus_ == DataEnums::OpenOrderWaiting && 
	   stock_->openData()->status_ != PurchaseData::Canceled)
    {
        posStatus_ = monitorOpen_->checkOpenOrder(positionTime_);
    }
    else if(posStatus_ == DataEnums::OpenFilled)
    {
        checkOpenFilledOrder();
    }
    else if(0 != monitorClose_ && posStatus_ == DataEnums::CloseOrderWaiting  && 
		    stock_->closeData()->status_ != PurchaseData::Canceled)
    {
        posStatus_ = monitorClose_->checkCloseClose(positionTime_);
    }
}

void PositionMonitor::checkOpenFilledOrder()
{
    double currentPrice = stock_->getLastPrice();

	bool exit = false;
    if(openData_->typeTrade_ == PurchaseData::Buy)
    {
		exit = exitStrategy_->sell(stock_->symbol(),startPrice_, currentPrice);
	}
    else
	{
		exit = exitStrategy_->buyToCover(stock_->symbol(),startPrice_, currentPrice);
    }
	if(exit)
	{
		reason_ = exitStrategy_->reason();
		createClose(openData_, currentPrice);
	}
}

void PositionMonitor::createClose(PurchaseData * data, double currentPrice)
{
	PurchaseData * closeData = new PurchaseData(*data);
	closeData->price_ = currentPrice;
	closeData->stopPrice_ = 0.0;
	closeData->stopLowerPrice_ = 0.0;
	closeData->stopUpperPrice_ = 0.0;

	if(closeData->typeTrade_ == PurchaseData::Buy)
	{
		closeData->typeTrade_ = PurchaseData::Sell;
	}
	else
    {
		closeData->typeTrade_ = PurchaseData::BuyToCover;
	}

	PurchaseManager::instance()->closeTrade(closeData);
}

void PositionMonitor::updateOrder(PositionMonitorManager::OrderData& pOrd)
{
	if(0 != monitorOpen_ && posStatus_ == DataEnums::OpenOrderWaiting)
	{
		posStatus_ = monitorOpen_->openOrderWaiting(pOrd);
	}
	else if(posStatus_ == DataEnums::OpenFilled)
	{
		posStatus_ = monitorOpen_->openFilled(pOrd);
	}
	else if(0 != monitorClose_ && posStatus_ == DataEnums::CloseOrderWaiting)
	{
		posStatus_ = monitorClose_->closeOrderWaiting(pOrd);
	}
}

PositionMonitor::~PositionMonitor()
{
	stock_->closeData(0);
	stock_->openData(0);

	delete 	exitStrategy_;

	delete monitorOpen_;
	delete monitorClose_;
}

void PositionMonitor::refreshPosition(long quantity, double price)
{
	openData_->price_ = price;
	openData_->size_ = quantity;
}
