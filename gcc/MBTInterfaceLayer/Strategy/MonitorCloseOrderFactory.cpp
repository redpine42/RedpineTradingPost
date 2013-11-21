// MonitorCloseOrderFactory.cpp: implementation of the MonitorCloseOrderFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "MonitorCloseOrderFactory.h"
#include "SymbolData.h"
#include "NormalCloseMonitor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MonitorCloseOrderFactory * MonitorCloseOrderFactory::instance_ = 0;

MonitorCloseOrderFactory::MonitorCloseOrderFactory()
{

}

MonitorCloseOrderFactory::~MonitorCloseOrderFactory()
{

}

MonitorCloseOrderFactory * MonitorCloseOrderFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new MonitorCloseOrderFactory();
	}
	return instance_;
}


MonitorCloseOrder * MonitorCloseOrderFactory::getMonitorCloseOrder(SymbolData * stock)
{
	return new NormalCloseMonitor(stock, 0, 0);
}

