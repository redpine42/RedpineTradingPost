// ExitStrategyFactory.h: interface for the ExitStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ExitStrategyFactory_h
#define ExitStrategyFactory_h

class ExitStrategy;
class SymbolData;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ExitStrategyFactory  
{
public:
	virtual ~ExitStrategyFactory();

	static ExitStrategyFactory * instance();

	ExitStrategy * getStrategy(SymbolData * stock);

private:
	static 	ExitStrategyFactory * instance_;
	ExitStrategyFactory();

};

#endif