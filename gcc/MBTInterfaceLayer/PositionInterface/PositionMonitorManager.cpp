#include "PositionMonitorManager.h"
#include <strstream>
#include "MsgProducer.h"

#include "PositionMonitor.h"
#include "PositionManager.h"
#include "SymbolData.h"
#include "SymbolDataList.h"
#include "TimeWrapper.h"
#include "PurchaseData.h"

PositionMonitorManager* PositionMonitorManager::instance_ = 0;

PositionMonitorManager * PositionMonitorManager::instance()
{
    if(0 == instance_)
    {
        instance_ = new PositionMonitorManager();
    }
    return instance_;
}

void PositionMonitorManager::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

PositionMonitorManager::~PositionMonitorManager()
{
    PositionsMapIter iter;
    for(iter = positions_.begin(); iter != positions_.end(); ++iter)
    {
        delete (*iter).second;
    }
}
    
void PositionMonitorManager::checkPosition(const std::string & symbol)
{
    PositionsMapIter iter = positions_.find(symbol);
    if(iter != positions_.end())
    {
		PositionMonitor * posMon = (*iter).second;
		if(posMon->status() == DataEnums::CloseFilled)
		{
			removePosition(symbol);
			PositionManager::instance()->positionClosed(symbol);
		}
		else
		{
			posMon->checkPosition();
		}
    }
}

PositionMonitorManager::PositionMonitorManager()
{
}

void PositionMonitorManager::removePosition(const std::string & symbol)
{
    PositionsMapIter iter = positions_.find(symbol);   
    if(iter != positions_.end())
    {
		delete (*iter).second;
	}
	positions_.erase(iter);
}

void PositionMonitorManager::openPosition(SymbolData * stock, PurchaseData * data)
{
    PositionsMapIter iter = positions_.find(stock->symbol());   
    if(iter != positions_.end())
    {
		delete (*iter).second;
	}
	positions_[stock->symbol()] = new PositionMonitor(stock, data);
	stock->openData(data);
}

void PositionMonitorManager::openPosition(SymbolData * stock, PurchaseData * data, DataEnums::PositionStatus posStatus)
{
    PositionsMapIter iter = positions_.find(stock->symbol());   
    if(iter != positions_.end())
    {
		delete (*iter).second;
	}
	PositionMonitor * mon = new PositionMonitor(stock, data);
	mon->status(posStatus);
	positions_[stock->symbol()] = mon;
	stock->openData(data);
}

void PositionMonitorManager::closePosition(SymbolData * stock, PurchaseData * data)
{
    PositionsMapIter iter = positions_.find(stock->symbol());   
    if(iter != positions_.end())
    {
        (*iter).second->closePosition(stock, data);
    }
}


void PositionMonitorManager::updateOrder(OrderData& pOrd)
{
	std::string symbol = pOrd.symbol_;
    PositionsMapIter iter = positions_.find(symbol);   
  	
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
	if(iter != positions_.end())
    {
		PositionMonitor * pm = (*iter).second;
        pm->updateOrder(pOrd);
		if((pm->status() == DataEnums::Rejected || pm->status() == DataEnums::Canceled) &&
			    0 == stock->openData())
		{
			delete (*iter).second;
			positions_.erase(iter);
		}
    }
	else  // No Previous open position
	{
		SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
		if(0 == stock)
		{
			return;
		}
		PurchaseData * openData = stock->openData();
//		PurchaseData * closeData = stock->closeData();

		PurchaseData * data = 0;
		if(0 == openData)
		{
			if(pOrd.eventName_ == "OnHistoryAdded" &&
			   pOrd.status_ == "Executed")
			{
			    data  = new PurchaseData();
				data->symbol_ = symbol;
				data->size_ = pOrd.quantity_;
				data->price_ = pOrd.price_;
				data->status_ = PurchaseData::Sent;
				data->typeTrade_ = pOrd.buySell_;
				data->executionType_ = pOrd.execType_;
				data->timeFilled_ = pOrd.time_;
				data->date_ = TimeWrapper::instance()->getDateStr(TimeWrapper::instance()->getCurrentJDate());
			}
			stock->openData(data);

			if(0 == data)
			{
				return;
			}
			data->reason_ = "User Initiated Order";

	        PositionMonitorManager::instance()->openPosition(stock, data);
			PositionsMapIter niter = positions_.find(symbol);   
		    if(niter != positions_.end())
			{
				(*niter).second->updateOrder(pOrd);
			}
		}
	}
}


void PositionMonitorManager::recreatePosition(std::string & symbol, long quantity, double price, std::string & orderNumber, double closePrice, std::string & date, long time, std::string reason)
{
	std::string tType = "Buy";
	SymbolData * stock = SymbolDataList::instance()->getSymbolData(symbol);
	PurchaseData::TradeType buySell = PurchaseData::Buy;
	if(quantity < 0)
	{
		buySell = PurchaseData::SellShort;
		tType = "Sell";
		quantity = -quantity;
	}
	if(date.empty())
	{
		date = TimeWrapper::instance()->getDateStr(TimeWrapper::instance()->getCurrentJDate());
		time = TimeWrapper::instance()->getSecondsGMT();
	}
    PurchaseData * openData  = new PurchaseData();
	openData->symbol_ = symbol;
	openData->size_ = quantity;
	openData->price_ = price;
	openData->status_ = PurchaseData::Filled;
	openData->typeTrade_ = buySell;
	openData->executionType_ = PurchaseData::LIMIT;
	openData->timeFilled_ =time;
	openData->date_ = date;
	openData->reason_ = "Restart - Reload Postition";
	openData->sharesFilled_ = quantity;

	PositionMonitorManager::instance()->openPosition(stock, openData,DataEnums::OpenFilled);
	PositionMonitor * monitor;

    PositionsMapIter iter = positions_.find(symbol);
    if(iter != positions_.end())
    {
		monitor = (*iter).second;
        monitor->status(DataEnums::OpenFilled);
    }

	PurchaseData::TradeType closeBuySell = PurchaseData::Sell;
	if(buySell == PurchaseData::SellShort)
	{
		closeBuySell = PurchaseData::Buy;
	}

	if(0 != closePrice && !orderNumber.empty())
	{
	    PurchaseData * closeData  = new PurchaseData();
		closeData->symbol_ = symbol;
		closeData->size_ = quantity;
		closeData->price_ = closePrice;
		closeData->status_ = PurchaseData::Sent;
		closeData->typeTrade_ = closeBuySell;
		closeData->executionType_ = PurchaseData::LIMIT;
		closeData->timeFilled_ = time;
		closeData->date_ = date;
		closeData->orderNumber_ = orderNumber;

		monitor->status(DataEnums::CloseOrderWaiting);
		stock->closeData(closeData);
		// should set the close data in the positionMonitor
	}
	std::strstream strstr;
	strstr << "\n\n" << symbol
		<< ":\n" << reason
		   << "\nQuantity: " << quantity
		   << "\nPrice: " << price
		   << "\nTrade Type: " << tType << std::ends;
	std::string  msg = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::POSITIONMONITORMANAGER, msg);
}

