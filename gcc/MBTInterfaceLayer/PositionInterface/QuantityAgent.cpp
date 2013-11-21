#include "QuantityAgent.h"
#include "PurchaseData.h"
#include "PositionManager.h"

QuantityAgent * QuantityAgent::instance_ = 0;

QuantityAgent * QuantityAgent::instance()
{
	if(0 == instance_)
	{
		instance_ = new QuantityAgent();
	}
	return instance_;
}

QuantityAgent::QuantityAgent(void)
{
}

void QuantityAgent::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

QuantityAgent::~QuantityAgent(void)
{
}

void QuantityAgent::newPurchaseRequest(PurchaseData * data)
{
	if(PositionManager::instance()->positionExists(data->symbol_))
	{
		data->size_ = 0;
	}
	else
	{
		data->size_ = 1000;
	}
}
