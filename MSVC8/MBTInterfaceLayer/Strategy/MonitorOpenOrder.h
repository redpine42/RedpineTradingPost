// MonitorOpenOrder.h: interface for the MonitorOpenOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MonitorOpenOrder_h
#define MonitorOpenOrder_h

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

class MonitorOpenOrder  
{
public:
	MonitorOpenOrder(SymbolData * stock);
	virtual ~MonitorOpenOrder();

	virtual DataEnums::PositionStatus checkOpenOrder(long & positionTime) = 0;

	virtual DataEnums::PositionStatus openOrderWaiting(PositionMonitorManager::OrderData& pOrd);
	virtual DataEnums::PositionStatus openFilled(PositionMonitorManager::OrderData& pOrd);

protected:
	SymbolData * stock_;
};

#endif
