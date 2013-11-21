// NormalCloseMonitor.h: interface for the NormalCloseMonitor class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NormalCloseMonitor_h
#define NormalCloseMonitor_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorCloseOrder_h
#include "MonitorCloseOrder.h"
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

class NormalCloseMonitor : public MonitorCloseOrder  
{
public:
	NormalCloseMonitor(SymbolData * stock, long startTradeTime, long endTradeTime);
	virtual ~NormalCloseMonitor();
	DataEnums::PositionStatus checkCloseClose(long & positionTime);

private:

	bool cancelingOrder_;

};

#endif 