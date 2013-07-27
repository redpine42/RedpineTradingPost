// EntryStrategyFactory.h: interface for the EntryStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EntryStrategyFactory_h
#define EntryStrategyFactory_h

class EntryStrategy;
class StockWatch;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class EntryStrategyFactory  
{
public:
	static 	EntryStrategyFactory * instance();
	virtual ~EntryStrategyFactory();

	EntryStrategy * getStrategy(StockWatch * stock);

private:
	static 	EntryStrategyFactory * instance_;
	EntryStrategyFactory();


};

#endif 
