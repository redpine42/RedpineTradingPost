#include "OrderManager.h"
#include "AccountManager.h"
#include "PurchaseData.h"
#include "stdafx.h"
#include "TradeManager.h"
#include "MsgProducer.h"


#define VALUE_BUY 10000
#define VALUE_SELL 10001
#define VALUE_SELLSHT 10002

#define VALUE_DAY 10011
#define VALUE_GTC 10008
#define VALUE_NORMAL 10042
#define VALUE_AGENCY 10020

OrderManager * OrderManager::instance_ = 0;
OrderManager * OrderManager::createInstance(IMbtOrderClientPtr orders)
{
    if(0 == instance_)
    {
        instance_ = new OrderManager(orders);
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, "Order Manager Created");
    }
    return instance_;
}

OrderManager * OrderManager::instance()
{
    if(0 == instance_)
    {
        instance_ = new OrderManager(0);
    }
    return instance_;
}

OrderManager::OrderManager(IMbtOrderClientPtr orders)
    : orders_(orders)
{
    orders_.AddRef();
	
}


void OrderManager::removeInstance()
{
}

OrderManager::~OrderManager()
{
    //Need to clean up any orders.  Leave nothing open.
	closeOut();

    orders_->Disconnect();
    orders_.Release();
    orders_.Detach();
    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, "OrderManager Destoryed" );
}

void OrderManager::closeOut()
{
}


bool OrderManager::checkOrderServer()
{
	DWORD sleepTime = 1000;
	bool status = true;
	if(!orders_->IsConnected())
	{
		TradeManager::instance()->reconnect();

		orders_->Connect();
		status = false;
		std::string msg = "Order Server is not connected.  Attempting to reconnect!";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ORDERMANAGER, msg);

		int cnt = 0;
		while ( cnt < 10)
		{
			if(orders_->IsConnected())
			{
			    IMbtAccountsPtr accounts;
		        accounts = orders_->Accounts;
				accounts->LoadAll();
				status = true;
				Sleep(sleepTime);
				break;
			}
			Sleep(sleepTime);
			++cnt;
		}
	}
	status = AccountManager::instance()->checkAccountStatus();


	return status;
}

void OrderManager::makeOrder(const PurchaseData * data)
{
	IMbtPositionsPtr m_pPositions = orders_->Positions;
	orders_->SilentMode = true;

	long val = m_pPositions->Count;
	for(int i = 0; i < val; ++i)
	{
		IMbtPosition * position = m_pPositions->Item[i];
		long quantity = 0;
		double price = 0.0;
		CString sSymbol = (LPCTSTR)position->Symbol;
		std::string symbol = sSymbol;

		quantity = position->CloseableShares;
		if(quantity != 0)
		{
			price = position->IntradayPrice;
			if(price == 0.0)
			{
				price = position->OvernightPrice;
			}
		}
	}

	if(!checkOrderServer())
	{
		std::string orderMsg = "Atempting to place an order. Order Manager failed in submission of order: ";
		orderMsg += "Order Server is not connected";
		MsgProducer::instance()->sendOrderStatus(data->symbol_, false, orderMsg);
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ORDERMANAGER, orderMsg);

		return;
	}


	int timeInForce = VALUE_GTC;
	int tradeType = data->executionType_;

//	if(ConfigurationData::instance()->equityAcct())
//	{
//		timeInForce = VALUE_DAY;
//	}

    CString sRoute = "MBTX";

    BSTR bstrRetMsg= NULL; // NULL works, but still need to free below ::SysAllocString(L"");
    short success = 0;

	CString sSym = data->symbol_.c_str();

	sSym.MakeUpper();

    if(data->typeTrade_ == PurchaseData::Buy)
    {
	   success = orders_->Submit(VALUE_BUY,
                                 data->size_,
                                 _bstr_t(sSym),
                                 data->price_,
                                 data->stopPrice_,
                                 timeInForce ,
                                 VALUE_AGENCY,
                                 tradeType,
                                 VALUE_NORMAL,
                                 0,
                                 AccountManager::instance()->getAccount(),
                                 _bstr_t(sRoute),
                                 "", data->stopLowerPrice_, data->stopUpperPrice_, 0, 0, 0, 0, 0, "", 0, 0, 0,"", false,
                                 &bstrRetMsg);

	   std::string msg = "Buy: " + data->symbol_;
	   MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, msg);

    }
    else if(data->typeTrade_== PurchaseData::SellShort)
    {
        success = orders_->Submit(VALUE_SELLSHT,
                                  data->size_,
                                  _bstr_t(sSym),
                                  data->price_,
                                  data->stopPrice_,
                                  timeInForce ,
                                  VALUE_AGENCY,
                                  tradeType,
                                  VALUE_NORMAL,
                                  0,
                                  AccountManager::instance()->getAccount(),
                                  _bstr_t(sRoute),
                                  "", data->stopLowerPrice_, data->stopUpperPrice_, 0, 0, 0, 0, 0, "", 0, 0, 0,"", false,
                                  &bstrRetMsg);

	   std::string msg = "Short: " + data->symbol_;
	   MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, msg);
    }
    else if(data->typeTrade_== PurchaseData::Sell)
    {
        success = orders_->Submit(VALUE_SELL,
                                  data->size_,
                                  _bstr_t(sSym),
                                  data->price_,
                                  data->stopPrice_,
                                  timeInForce ,
                                  VALUE_AGENCY,
                                  tradeType,
                                  VALUE_NORMAL,
                                  0,
                                  AccountManager::instance()->getAccount(),
                                  _bstr_t(sRoute),
                                  "", data->stopLowerPrice_, 0.0, 0, 0, 0, 0, 0, "", 0, 0, 0,"", false,
                                  &bstrRetMsg);

	   std::string msg = "Sell: " + data->symbol_;
	   MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, msg);
    }
    else if(data->typeTrade_== PurchaseData::BuyToCover)
    {
        success = orders_->Submit(VALUE_BUY,
                                  data->size_,
                                  _bstr_t(sSym),
                                  data->price_,
                                  data->stopPrice_,
                                  timeInForce ,
                                  VALUE_AGENCY,
                                  tradeType,
                                  VALUE_NORMAL,
                                  0,
                                  AccountManager::instance()->getAccount(),
                                  _bstr_t(sRoute),
                                  "", data->stopLowerPrice_, 0.0, 0, 0, 0, 0, 0, "", 0, 0, 0,"", false,
                                  &bstrRetMsg);

	   std::string msg = "Cover: " + data->symbol_;
	   MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, msg);
    }

	_bstr_t bstr_t(bstrRetMsg);
	std::string msg(bstr_t);
	::SysFreeString(bstrRetMsg);
    
    if(success)
    {
	   std::string orderMsg = "Order Success(" + data->symbol_ + "): ";
	   orderMsg += msg;
	   MsgProducer::instance()->sendOrderStatus(data->symbol_, true, orderMsg);
	   MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, orderMsg);
    }
    else
    {
		std::string orderMsg = "Order Manager failed in submission of order(" + data->symbol_ + "): ";
		orderMsg += msg;
 	    MsgProducer::instance()->sendOrderStatus(data->symbol_, false, orderMsg);
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, orderMsg);
    }
}


void OrderManager::cancelOrder(const std::string & symbol, const std::string & orderNumber)
{
	if(!checkOrderServer())
	{
		std::string orderMsg = "Order Manager failed to cancel order; Order Server not connected (" + symbol + "): ";
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ORDERMANAGER, orderMsg);
		return;
	}
    BSTR bstrRetMsg = NULL; 

	short success = orders_->Cancel(orderNumber.c_str(), &bstrRetMsg);
        
	_bstr_t bstr_t(bstrRetMsg);
	std::string msg(bstr_t);
    ::SysFreeString(bstrRetMsg);

    if(success)
    {
		std::string orderMsg = "Order canceled(" + symbol + "): ";
		orderMsg += msg;
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ORDERMANAGER, orderMsg);
	}
	else
	{
		std::string orderMsg = "Order Manager failed to cancel order(" + symbol + "): ";
		orderMsg += msg;
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ORDERMANAGER, orderMsg);
    }
}

