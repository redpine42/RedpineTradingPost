/*
 * IOrderClient.h
 *
 *  Created on: Dec 23, 2013
 *      Author: dbrown
 */

#ifndef IOrderClient_h
#define IOrderClient_h

#ifndef IAccounts_h
#include "IAccounts.h"
#endif

class IOrderClient {
public:
	IOrderClient();
	virtual ~IOrderClient();

	IAccounts * accounts(){return accounts_;}

private:
	IAccounts * accounts_;
};

#endif /* IORDERCLIENT_H_ */
