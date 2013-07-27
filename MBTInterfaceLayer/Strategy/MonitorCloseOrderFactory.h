// MonitorCloseOrderFactory.h: interface for the MonitorCloseOrderFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MonitorCloseOrderFactory_h
#define MonitorCloseOrderFactory_h

class SymbolData;
class MonitorCloseOrder;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MonitorCloseOrderFactory  
{
public:
	static MonitorCloseOrderFactory * instance();

	virtual ~MonitorCloseOrderFactory();
	
	MonitorCloseOrder * getMonitorCloseOrder(SymbolData * stock);

private:
	static MonitorCloseOrderFactory * instance_;
	MonitorCloseOrderFactory();
};

#endif 
