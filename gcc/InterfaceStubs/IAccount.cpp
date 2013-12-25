/*
 * IAccount.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: dbrown
 */

#include "IAccount.h"

IAccount::IAccount() {
	// TODO Auto-generated constructor stub

}

IAccount::~IAccount() {
	// TODO Auto-generated destructor stub
}

double IAccount::currentEquity(){return currentEquity_;}
double IAccount::MMRMultiplier(){return MMRMultiplier_;}

AccountState IAccount::accountState(){return accountState_;}
void IAccount::load(){}
