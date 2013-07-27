// MonitorOpenOrderFactory.cpp: implementation of the MonitorOpenOrderFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "MonitorOpenOrderFactory.h"
#include "SymbolData.h"
#include "NullMonitorOpenOrder.h"
#include "OpenOrderChase.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MonitorOpenOrderFactory * MonitorOpenOrderFactory::instance_ = 0;

MonitorOpenOrderFactory::MonitorOpenOrderFactory()
{

}

MonitorOpenOrderFactory::~MonitorOpenOrderFactory()
{

}

MonitorOpenOrderFactory * MonitorOpenOrderFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new MonitorOpenOrderFactory();
	}
	return instance_;
}


MonitorOpenOrder * MonitorOpenOrderFactory::getMonitorOpenOrder(SymbolData * stock)
{
	return new OpenOrderChase(stock);
}
