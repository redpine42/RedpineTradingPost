#include "PositionManager.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"

#include "OrderHistoryData.h"
#include "OpenOrderData.h"
#include "PositionUpdate.h"
#include "AccountData.h"
#include "PurchaseData.h"
#include "PurchaseManager.h"
#include "SymbolData.h"
#include "SymbolDataList.h"
#include "PositionMonitorManager.h"
#include "TimeWrapper.h"
#include <pthread.h>

PositionManager * PositionManager::instance_ = 0;


PositionManager * PositionManager::instance()
{
	if(0 == instance_)
	{
		instance_ = new PositionManager();
	}
	return instance_;
}
PositionManager::PositionManager()
{
}

PositionManager::~PositionManager(void)
{
}

void PositionManager::historyUpdate(OrderHistoryData * pHist)
{
	pthread_mutex_lock(&mutex_);

	PositionMonitorManager::OrderData orderData;
	orderData.symbol_ = pHist->symbol_;
	orderData.quantity_ = pHist->quantity_;
	orderData.quantityFilled_ = pHist->sharesFilled_;
	orderData.price_ = pHist->price_;
	orderData.status_ = pHist->event_;
	orderData.orderNumber_ = pHist->orderNumber_;
	orderData.eventName_ = pHist->eventType_;
	orderData.time_ = TimeWrapper::instance()->stringToSecondsGMT(pHist->time_);

	std::string buySell = pHist->buySell_;
	if(buySell == "BUY")
	{
		orderData.buySell_ = PurchaseData::Buy;
	}
	else if(buySell == "SELL")
	{
		orderData.buySell_ = PurchaseData::Sell;
	}
	else if(buySell == "SHORT")
	{
		orderData.buySell_ = PurchaseData::SellShort;
	}
	else
	{
		orderData.buySell_ = PurchaseData::NoTrade;
	}

	orderData.execType_ = (PurchaseData::ExecutionType)pHist->execType_;



	PositionMonitorManager::instance()->updateOrder(orderData);

	pthread_mutex_unlock(&mutex_);

}

void PositionManager::orderUpdate(OpenOrderData *data)
{
	pthread_mutex_lock(&mutex_);

	PositionMonitorManager::OrderData orderData;
	orderData.symbol_ = data->symbol_;
	orderData.quantity_ = data->quantity_;
	orderData.quantityFilled_ = data->sharesFilled_;
	orderData.price_ = data->price_;
	orderData.status_ = data->currentEvent_;
	orderData.orderNumber_ = data->orderNumber_;
	orderData.eventName_ = data->eventType_;
	orderData.time_ = TimeWrapper::instance()->stringToSecondsGMT(data->time_);

	std::string buySell = data->buySell_;
	if(buySell == "BUY")
	{
		orderData.buySell_ = PurchaseData::Buy;
	}
	else if(buySell == "SELL")
	{
		orderData.buySell_ = PurchaseData::Sell;
	}
	else if(buySell == "SHORT")
	{
		orderData.buySell_ = PurchaseData::SellShort;
	}
	else
	{
		orderData.buySell_ = PurchaseData::NoTrade;
	}
	PositionMonitorManager::instance()->updateOrder(orderData);

	pthread_mutex_unlock(&mutex_);
}

void PositionManager::positionUpdate(PositionData *data)
{
}

void PositionManager::accountUpdate(AccountData * data)
{
}

void PositionManager::purchaseUpdate(PurchaseData *data)
{
	pthread_mutex_lock(&mutex_);

	PurchaseManager::instance()->trade(data);
	openPositions_.insert(data->symbol_);

	pthread_mutex_unlock(&mutex_);

}

void PositionManager::l1DataUpdate(L1Data * data)
{
	pthread_mutex_lock(&mutex_);

	SymbolData * symbolData = SymbolDataList::instance()->getSymbolData(data->symbol_);
	symbolData->updateLevel1(data);
    PositionMonitorManager::instance()->checkPosition(data->symbol_);

	pthread_mutex_unlock(&mutex_);

}

bool PositionManager::positionExists(std::string & symbol)
{
	PositionSetIter iter;
	iter = openPositions_.find(symbol);
	return (iter != openPositions_.end());
}

void PositionManager::updateOrderStatus(std::string & symbol, bool success, std::string & message)
{
	SymbolData * symbolData = SymbolDataList::instance()->getSymbolData(symbol);
	if(success)
	{
		symbolData->updateTradeStatus(PurchaseData::Executed);
	}
	else
	{
		openPositions_.erase(symbol);
		symbolData->updateTradeStatus(PurchaseData::Failed);
		PositionMonitorManager::instance()->removePosition(symbol);
		SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
		stock->failedOrder(symbol);
	}
}

void PositionManager::positionClosed(const std::string & symbol)
{
	openPositions_.erase(symbol);
}
