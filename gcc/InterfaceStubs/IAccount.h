/*
 * IAccount.h
 *
 *  Created on: Dec 23, 2013
 *      Author: dbrown
 */

#ifndef IAccount_h
#define IAccount_h

enum AccountState
{
	asLoaded,
	asUnloaded,
	asLoading,
	asReloading,
	asUnavailable
};

class IAccount {
public:
	IAccount();
	virtual ~IAccount();

	double currentEquity();
	double MMRMultiplier();

	AccountState accountState();

	void load();

private:
	double currentEquity_;
	double MMRMultiplier_;
	AccountState accountState_;
};

#endif /* IACCOUNT_H_ */
