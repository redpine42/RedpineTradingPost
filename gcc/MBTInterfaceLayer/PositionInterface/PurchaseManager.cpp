#include "PurchaseManager.h"
#include "MsgProducer.h"
#include "QuantityAgent.h"
#include "PriceAgent.h"
#include "PositionMonitorManager.h"
#include "SymbolDataList.h"
#include "SymbolData.h"

PurchaseManager * PurchaseManager::instance_ = 0;

PurchaseManager * PurchaseManager::instance()
{
	if(0 == instance_)
	{
		instance_ = new PurchaseManager();
	}
	return instance_;
}

void PurchaseManager::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

PurchaseManager::PurchaseManager(void)
{
}

PurchaseManager::~PurchaseManager(void)
{
	PriceAgent::removeInstance();
	QuantityAgent::removeInstance();
}

void PurchaseManager::trade(PurchaseData * data)
{
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(data->symbol_);
	PurchaseData * openData = stock->openData();
	PurchaseData * closeData = stock->closeData();
	data->status_ = PurchaseData::Sent;

    if(0 == openData)
    {
		QuantityAgent::instance()->newPurchaseRequest(data);
		if(data->size_ != 0)
		{
			PriceAgent::instance()->newPurchaseRequest(data);
			data->executionType_ = PurchaseData::MARKET;

			MsgProducer::instance()->sendOrder(*data);
			stock->openData(data);

			PositionMonitorManager::instance()->openPosition(stock, data);
		}
	}
}

void PurchaseManager::closeTrade(PurchaseData * data)
{
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(data->symbol_);
	PurchaseData * openData = stock->openData();
	PurchaseData * closeData = stock->closeData();
	data->status_ = PurchaseData::Sent;

	if(0 != openData &&
	   0 == closeData)
	{
		PriceAgent::instance()->closePurchaseRequest(data);
		data->executionType_ = PurchaseData::TTO_ORDER;


//		MsgProducer::instance()->sendOrder(*data);
		stock->closeData(data);
		PositionMonitorManager::instance()->closePosition(stock, data);
	}
}

