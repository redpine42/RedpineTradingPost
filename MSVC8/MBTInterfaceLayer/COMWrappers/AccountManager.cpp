#include "AccountManager.h"
#include "OrderManager.h"
#include "TradeManager.h"
#include "MsgProducer.h"

AccountManager * AccountManager::instance_ = 0;


AccountManager * AccountManager::createInstance(IMbtOrderClientPtr orders)
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

AccountManager::AccountManager(IMbtOrderClientPtr orderClient)
    : myAccount_(0),
	  mornOvernightBP_(0.0),
	  BP_(0.0)
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
		mornOvernightBP_ = myAccount_->CurrentEquity * myAccount_->MMRMultiplier;
		BP_ = mornOvernightBP_;
	}
}

AccountManager::~AccountManager()
{
    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "Account Manager Destroyed");
}


IMbtAccountPtr AccountManager::getAccount()
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
	return myAccount_->CurrentEquity;
}

bool AccountManager::checkAccountStatus()
{
	bool status =  true;
	if(0 == myAccount_)
	{
		getDefaultAccount(OrderManager::instance()->orderClient());
	}
	if(myAccount_->State == asLoaded)
	{
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "Account Status Ok");
		return true;
	}
	else if(myAccount_->State == asUnloaded)
	{
		myAccount_->Load();

		std::string msg = "MBTAccount is not loaded.  Attempting to load account.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(myAccount_->State == asLoading)
	{
		std::string msg = "MBTAccount is loading.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(myAccount_->State == asReloading)
	{
		std::string msg = "MBTAccount is reloading.";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	else if(myAccount_->State == asUnavailable)
	{
		myAccount_->Load();

		std::string msg = "MBTAccount is not loaded(Unavailable).  Will attempt to Load at next check!";
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, msg);
		status = false;
	}
	int cnt = 0;
	while(cnt < 20)
	{
		if(myAccount_->State == asLoaded)
		{
			status = true;
			break;
		}
		++cnt;
		DWORD waitTime = 1000;
		Sleep(waitTime);
	}
	return status;
}

void AccountManager::getDefaultAccount(IMbtOrderClientPtr orderClient)
{
	if( orderClient == NULL )
    {
		std::string msg = "Could not set OrderClient ! ";
		msg += MB_ICONINFORMATION;
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ACCOUNTMANAGER, msg);
    }
    else
    {
        CString sMsg;

        orderClient->SilentMode = false;
        
        IMbtAccountsPtr m_pAccounts = orderClient->Accounts;
		m_pAccounts->LoadAll();
        int iCount = m_pAccounts->Count;
        if(iCount > 0)
        {
            myAccount_ = m_pAccounts->Item[0];
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "First Account Loaded");
        }
        try
		{
			myAccount_->Load();
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::ACCOUNTMANAGER, "No Accounts, trying Default Account");
		}
		catch(...)
		{
			MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::ACCOUNTMANAGER, "Account Loading Failed");
		}
	}
}