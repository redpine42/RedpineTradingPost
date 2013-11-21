// MonitorCloseOrder.h: interface for the MonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MonitorCloseOrder_h
#define MonitorCloseOrder_h

class SymbolData;
struct PurchaseData;

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

#ifndef PositionMonitorManager_h
#include "PositionMonitorManager.h"
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MonitorCloseOrder  
{
public:
	MonitorCloseOrder(SymbolData * stock, long startTradeTime, long endTradeTime);
	virtual ~MonitorCloseOrder();

	virtual DataEnums::PositionStatus checkCloseClose(long & positionTime) = 0;

	virtual DataEnums::PositionStatus closeOrderWaiting(PositionMonitorManager::OrderData& pOrd);

	bool tradeTime(SymbolData * stock);

protected:
	SymbolData * stock_;
	long startTradeTime_;
	long endTradeTime_;
	bool cancelOrder_;
};

#endif

