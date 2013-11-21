// COTLMonitorOpenOrder.h: interface for the COTLMonitorOpenOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COTLMonitorOpenOrder_h
#define COTLMonitorOpenOrder_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorOpenOrder_h
#include "MonitorOpenOrder.h"
#endif

class COTLMonitorOpenOrder : public MonitorOpenOrder  
{
public:
	COTLMonitorOpenOrder(StockWatch * stock,double pipsStopLoss);
	virtual ~COTLMonitorOpenOrder();
	
	PositionStatus checkOpenOrder(long & positionTime);

	PositionStatus openOrderWaiting(PositionMonitorManager::OrderData& pOrd);
	PositionStatus openFilled(PositionMonitorManager::OrderData& pOrd);

private:
	double pipsStopLoss_;

};

#endif 
