// NullMonitorCloseOrder.h: interface for the NullMonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NullMonitorCloseOrder_h
#define NullMonitorCloseOrder_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorCloseOrder_h
#include "MonitorCloseOrder.h"
#endif

class NullMonitorCloseOrder : public MonitorCloseOrder  
{
public:
	NullMonitorCloseOrder(StockWatch * stock, long startTradeTime, long endTradeTime);
	virtual ~NullMonitorCloseOrder();

	PositionStatus checkCloseClose(long & positionTime) {return CloseOrderWaiting;}
};

#endif 
