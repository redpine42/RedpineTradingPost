#include "Trigger.h"
#include "L1Data.h"
#include "MsgProducer.h"
#include "PurchaseData.h"

Trigger::Trigger(std::string & symbol)
: symbol_(symbol)
{
}

Trigger::~Trigger(void)
{
}

void Trigger::evalData(L1Data * data)
{
	if(symbol_ == data->symbol_)
	{
		l1Data_.push(data);

		if(buy(data))
		{
			sendTrigger(PurchaseData::Buy, data);
		}
		else if(sell(data))
		{
			sendTrigger(PurchaseData::Sell, data);
		}

		if(l1Data_.size() > 10)
		{
			L1Data * front = l1Data_.front();
			l1Data_.pop();
			delete front;
		}
	}
}

bool Trigger::buy(L1Data * data)
{
	bool ret = false;
	if(l1Data_.size() > 10)
	{
		L1Data * front = l1Data_.front();
		L1Data * back = l1Data_.back();

		if(back->time_ - front->time_ < 5.0 && 
			back->price_ - front->price_ > .0003)
		{
			ret = true;
		}
	}

	return ret;
}

bool Trigger::sell(L1Data * data)
{
	bool ret = false;
	if(l1Data_.size() > 10)
	{
		L1Data * front = l1Data_.front();
		L1Data * back = l1Data_.back();

		if(back->time_ - front->time_ < 5.0 && 
			front->price_ - back->price_ > .0003)
		{
			ret = true;
		}
	}

	return ret;
}

void Trigger::sendTrigger(PurchaseData::TradeType tradeEnum, L1Data * l1Data)
{
	PurchaseData data;
	data.symbol_ = symbol_;
	    
	data.price_ = l1Data->price_;
	data.stopPrice_ = 0.0;
	data.size_ = 0;

	data.executionType_ = PurchaseData::NotExecuted;
	data.typeTrade_ = tradeEnum;
	data.stopLowerPrice_ = 0.0;
	data.stopUpperPrice_ = 0.0;

	data.reason_ = "Test Trigger";

	MsgProducer::instance()->sendTradeTrigger(data);

	std::string triggerType = "BUY";
	if(tradeEnum == PurchaseData::Sell)
	{
		triggerType = "SELL";
	}
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, "Test Trigger Event: ", triggerType);
}
