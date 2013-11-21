// TPSLMonitorClose.h: interface for the TPSLMonitorClose class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TPSLMonitorClose_h
#define TPSLMonitorClose_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MonitorCloseOrder.h"

class TPSLMonitorClose : public MonitorCloseOrder  
{
public:
	TPSLMonitorClose(StockWatch * stock, long startTradeTime, long endTradeTime, double pipsStopLoss);
	virtual ~TPSLMonitorClose();

	PositionStatus checkCloseClose(long & positionTime);

private:
	double pipsStopLoss_;
};

#endif
