// NullMonitorCloseOrder.cpp: implementation of the NullMonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#include "NullMonitorCloseOrder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NullMonitorCloseOrder::NullMonitorCloseOrder(StockWatch * stock, long startTradeTime, long endTradeTime)
	: MonitorCloseOrder(stock, startTradeTime, endTradeTime)
{

}

NullMonitorCloseOrder::~NullMonitorCloseOrder()
{

}
