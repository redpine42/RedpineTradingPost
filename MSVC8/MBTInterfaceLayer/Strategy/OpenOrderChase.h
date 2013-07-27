// OpenOrderChase.h: interface for the OpenOrderChase class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OpenOrderChase_h
#define OpenOrderChase_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MonitorOpenOrder_h
#include "MonitorOpenOrder.h"
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

class OpenOrderChase : public MonitorOpenOrder  
{
public:
	OpenOrderChase(SymbolData * stock);
	virtual ~OpenOrderChase();

	DataEnums::PositionStatus checkOpenOrder(long & positionTime);

};

#endif
