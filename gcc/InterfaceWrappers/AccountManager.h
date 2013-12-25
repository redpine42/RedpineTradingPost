#ifndef AccountManager_h
#define AccountManager_h

#ifndef IOrderClient_h
#include "IOrderClient.h"
#endif

#ifndef IAccount_h
#include "IAccount.h"
#endif

class AccountManager
{
public:
    static AccountManager * createInstance(IOrderClient* orders);
    static AccountManager * instance();
    static void removeInstance();

    IAccount * getAccount();
	void setAccount(IAccount* account){myAccount_ = account;}
	void updateBP(double BP, double profitLoss);

	double getEquity();

	double getStartBuyingPower(){return mornOvernightBP_;}

	bool checkAccountStatus();
private:
    void getDefaultAccount(IOrderClient* orders);
    ~AccountManager();
    AccountManager(IOrderClient * orders);

    IAccount* myAccount_;
	double BP_;
	double dailyPL_;
	double mornOvernightBP_;

    static AccountManager * instance_;
};

#endif

