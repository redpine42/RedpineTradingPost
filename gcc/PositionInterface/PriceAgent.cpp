#include "PriceAgent.h"
#include "PurchaseData.h"

PriceAgent * PriceAgent::instance_ = 0;

PriceAgent * PriceAgent::instance()
{
	if(0 == instance_)
	{
		instance_ = new PriceAgent();
	}
	return instance_;
}

PriceAgent::PriceAgent(void)
{
}

void PriceAgent::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

PriceAgent::~PriceAgent(void)
{
}


void PriceAgent::newPurchaseRequest(PurchaseData * data)
{
	data->stopLowerPrice_ = data->price_ - .0010;
	data->stopUpperPrice_ = data->price_ + .0010;

	if(data->typeTrade_ == PurchaseData::Sell)
	{
		data->stopPrice_ = data->price_ +.0010;

	}
	else
	{
		data->stopPrice_ = data->price_ -.0010;
	}

}
void PriceAgent::closePurchaseRequest(PurchaseData * data)
{
	if(data->typeTrade_ == PurchaseData::BuyToCover)
	{
		double price = data->price_;
		data->price_ = price -.0010;
		data->stopPrice_ = 0.0;
		data->stopLowerPrice_ = price + .0010;
		data->stopUpperPrice_ = 0.0;
	}
	else
	{
		double price = data->price_;
		data->price_ = price +.0010;
		data->stopPrice_ = 0.0;
		data->stopLowerPrice_ = price - .0010;
		data->stopUpperPrice_ = 0.0;
	}

}
