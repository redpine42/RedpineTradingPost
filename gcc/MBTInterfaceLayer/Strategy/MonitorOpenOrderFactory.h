// MonitorOpenOrderFactory.h: interface for the MonitorOpenOrderFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MonitorOpenOrderFactory_h
#define MonitorOpenOrderFactory_h

class MonitorOpenOrder;
class SymbolData;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MonitorOpenOrderFactory  
{
public:
	static MonitorOpenOrderFactory * instance();

	virtual ~MonitorOpenOrderFactory();
	
	MonitorOpenOrder * getMonitorOpenOrder(SymbolData * stock);

private:
	static MonitorOpenOrderFactory * instance_;
	MonitorOpenOrderFactory();
};

#endif
