// ExitStrategyFactory.cpp: implementation of the ExitStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "ExitStrategyFactory.h"

#include "SymbolData.h"
#include "ExitExit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	
ExitStrategyFactory * ExitStrategyFactory::instance_ = 0;


ExitStrategyFactory::ExitStrategyFactory()
{

}

ExitStrategyFactory::~ExitStrategyFactory()
{

}

ExitStrategyFactory * ExitStrategyFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new ExitStrategyFactory();
	}
	return instance_;
}

ExitStrategy * ExitStrategyFactory::getStrategy(SymbolData * stock)
{
	return new ExitExit(stock->symbol(), 0, 86400);;
}

