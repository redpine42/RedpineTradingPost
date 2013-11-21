// NullMonitorOpenOrder.h: interface for the NullMonitorOpenOrder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NullMonitorOpenOrder_h
#define NullMonitorOpenOrder_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorOpenOrder_h
#include "MonitorOpenOrder.h"
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

class NullMonitorOpenOrder : public MonitorOpenOrder  
{
public:
	NullMonitorOpenOrder(SymbolData * stock);
	virtual ~NullMonitorOpenOrder();

	DataEnums::PositionStatus checkOpenOrder(long & positionTime) {return DataEnums::OpenOrderWaiting;}
};

#endif 
