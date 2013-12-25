/*
 * IAccounts.h
 *
 *  Created on: Dec 24, 2013
 *      Author: dbrown
 */

#ifndef IAccounts_h
#define IAccounts_h

class IAccounts {
public:
	IAccounts();
	virtual ~IAccounts();

	void loadAll(){}
	int numAccounts(){return numAccounts_;}
	IAccount * getAccount(int indx);

private:
	int numAccounts_;
};

#endif /* IACCOUNTS_H_ */
