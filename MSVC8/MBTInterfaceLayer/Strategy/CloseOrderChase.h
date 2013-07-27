// CloseOrderChase.h: interface for the CloseOrderChase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CloseOrderChase_h
#define CloseOrderChase_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MonitorCloseOrder.h"

class CloseOrderChase : public MonitorCloseOrder  
{
public:
	CloseOrderChase(StockWatch * stock, long startTradeTime, long endTradeTime);
	virtual ~CloseOrderChase();

	PositionStatus checkCloseClose(long & positionTime);

};

#endif
