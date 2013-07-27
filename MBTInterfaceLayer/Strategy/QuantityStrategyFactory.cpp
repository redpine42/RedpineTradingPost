// QuantityStrategyFactory.cpp: implementation of the QuantityStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "QuantityStrategyFactory.h"
#include "QuantityStrategy.h"
#include "ConfigurationData.h"
#include "MaxDDSizing.h"
#include "MyMaxDDSizing.h"
#include "EqualPriceQuantity.h"
#include "ErrorLog.h"

QuantityStrategyFactory * QuantityStrategyFactory::instance_ = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

QuantityStrategyFactory::QuantityStrategyFactory()
{

}

QuantityStrategyFactory::~QuantityStrategyFactory()
{
	QSMapIter iter;
	for(iter = strategyMap_.begin(); iter != strategyMap_.end(); ++iter)
	{
		delete (*iter).second;
	}
}

QuantityStrategyFactory * QuantityStrategyFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new QuantityStrategyFactory();
	}
	return instance_;
}

QuantityStrategy * QuantityStrategyFactory::getStrategy(const std::string & symbol)
{
	QuantityStrategy * strategy = 0;
	QSMapIter iter = strategyMap_.find(symbol);
	if(iter == strategyMap_.end())
	{
		MaxDDMSAData * data = ConfigurationData::instance()->msaData(symbol);
		MaxDDData * maxData = ConfigurationData::instance()->maxDDData(symbol);
		if(0 == data && 0 == maxData)
		{
			strategy = new EqualPriceQuantity();
		}
		else if(data != 0)
		{
			strategy = new MaxDDSizing(data);
		}
		else if(maxData != 0)
		{
			strategy = new MyMaxDDSizing(maxData);
		}
		strategyMap_[symbol] = strategy;
	}
	else
	{
		strategy = (*iter).second;
	}
	return strategy;
}


