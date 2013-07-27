#pragma once

struct L1Data;
struct TimeSalesData;

#ifndef queue_h
#include <queue>
#define queue_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef PurchaseData_
#include "PurchaseData.h"
#endif

class Trigger
{
public:
	Trigger(std::string & symbol);
	~Trigger(void);

	virtual void evalData(L1Data * data);
	virtual void evalData(TimeSalesData * data){};

private:
	virtual bool buy(L1Data * data);
	virtual bool sell(L1Data * data);

	void sendTrigger(PurchaseData::TradeType tradeEnum, L1Data * data);

	std::string symbol_;
	std::queue<L1Data*> l1Data_;
};
