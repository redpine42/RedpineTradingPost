// COTLMonitorCloseOrder.h: interface for the COTLMonitorCloseOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COTLMonitorCloseOrder_h
#define COTLMonitorCloseOrder_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorCloseOrder_h
#include "MonitorCloseOrder.h"
#endif

class COTLMonitorCloseOrder : public MonitorCloseOrder  
{
public:
	COTLMonitorCloseOrder(StockWatch * stock, double trailOnceStopLossTrigger, double trailOnceStopLoss, long startTradeTime, long endTradeTime);
	virtual ~COTLMonitorCloseOrder();

	PositionStatus checkCloseClose(long & positionTime);

	PositionStatus closeOrderWaiting(PositionMonitorManager::OrderData& pOrd);
private:
	double trailOnceStopLossTrigger_;
	double trailOnceStopLoss_;

	bool cancelingOrder_;
	bool MACDExit_;
	bool stopLossWait_;


};

#endif 
