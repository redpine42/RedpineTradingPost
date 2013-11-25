#ifndef AccountManager_h
#define AccountManager_h

#ifndef stdafx_h
#include "stdafx.h"
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AccountManager
{
public:
    static AccountManager * createInstance(IMbtOrderClientPtr orders);
    static AccountManager * instance();
    static void removeInstance();

    IMbtAccountPtr getAccount();
	void setAccount(IMbtAccountPtr account){myAccount_ = account;}
	void updateBP(double BP, double profitLoss);

	double getEquity();

	double getStartBuyingPower(){return mornOvernightBP_;}

	bool checkAccountStatus();
private:
    void getDefaultAccount(IMbtOrderClientPtr orders);
    ~AccountManager();
    AccountManager(IMbtOrderClientPtr orders);

    IMbtAccountPtr myAccount_;
	double BP_;
	double dailyPL_;
	double mornOvernightBP_;

    static AccountManager * instance_;
};

#endif

