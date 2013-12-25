#include "IAccount.h"

#include "AccountManager.h"
#include "OrderManager.h"
#include "TradeManager.h"
#include "MsgProducer.h"
#include "IOrderClient.h"
#include "IAccounts.h"

AccountManager * AccountManager::instance_ = 0;


AccountManager * AccountManager::createInstance(IOrderClient * orders)
{
	if(0 == instance_)
	{
		instance_ = new AccountManager(orders);
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "Account Manager Created");
	}
    return instance_;
}

void AccountManager::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

AccountManager * AccountManager::instance()
{
    return instance_;
}

AccountManager::AccountManager(IOrderClient * orderClient)
    : myAccount_(0),
	  BP_(0.0),
	  mornOvernightBP_(0.0)

{
	getDefaultAccount(orderClient);

	if(0 != myAccount_)
	{
/*	if(0 == myAccount->GetPermedForForex())
	{
		ConfigurationData::instance()->forexAcct(false);
	}
	else
	{
		ConfigurationData::instance()->forexAcct(true);
	}

	if(0 == myAccount->GetPermedForEquities())
	{
		ConfigurationData::instance()->equityAcct(false);
	}
	else
	{
		ConfigurationData::instance()->equityAcct(true);
	}
*/
		mornOvernightBP_ = myAccount_->currentEquity() * myAccount_->MMRMultiplier();
		BP_ = mornOvernightBP_;
	}
}

AccountManager::~AccountManager()
{
    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "Account Manager Destroyed");
}


IAccount* AccountManager::getAccount()
{
	if(0 == myAccount_)
	{
		getDefaultAccount(OrderManager::instance()->orderClient());
	}
    return myAccount_;
}

void AccountManager::updateBP(double BP,  double profitLoss)
{
    BP_ = BP;
	dailyPL_ = profitLoss;
}

double AccountManager::getEquity()
{
	return myAccount_->currentEquity();
}

bool AccountManager::checkAccountStatus()
{
	bool status =  true;
	if(0 == myAccount_)
	{
		getDefaultAccount(OrderManager::instance()->orderClient());
	}
	AccountState accountState = myAccount_->accountState();
	if(accountState == asLoaded)
	{
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "Account Status Ok");
		return true;
	}
	else if(accountState == asUnloaded)
	{
		myAccount_->load();

		std::string msg = "MBTAccount is not loaded.  Attempting to load account.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(accountState == asLoading)
	{
		std::string msg = "MBTAccount is loading.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(accountState == asReloading)
	{
		std::string msg = "MBTAccount is reloading.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(accountState == asUnavailable)
	{
		myAccount_->load();

		std::string msg = "MBTAccount is not loaded(Unavailable).  Will attempt to Load at next check!";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	int cnt = 0;
	while(cnt < 20)
	{
		if(accountState == asLoaded)
		{
			status = true;
			break;
		}
		++cnt;
		sleep(1000);
	}
	return status;
}

void AccountManager::getDefaultAccount(IOrderClient* orderClient)
{
	if( orderClient == NULL )
    {
		std::string msg = "Could not set OrderClient ! ";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ACCOUNTMANAGER, msg);
    }
    else
    {
// TODO:        orderClient->SilentMode = false;
        
        IAccounts * m_pAccounts = orderClient->accounts();
		m_pAccounts->loadAll();
        int iCount = m_pAccounts->numAccounts();
        if(iCount > 0)
        {
            myAccount_ = m_pAccounts->getAccount(0);
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "First Account Loaded");
        }
        try
		{
			myAccount_->load();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "No Accounts, trying Default Account");
		}
		catch(...)
		{
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ACCOUNTMANAGER, "Account Loading Failed");
		}
	}
}
