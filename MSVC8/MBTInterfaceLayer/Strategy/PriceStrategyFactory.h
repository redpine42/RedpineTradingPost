#pragma warning(disable:4786)
// PriceStrategyFactory.h: interface for the PriceStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef PriceStrategyFactory_h
#define PriceStrategyFactory_h

class PriceStrategy;
class StockWatch;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

class PriceStrategyFactory  
{
public:
	virtual ~PriceStrategyFactory();
	static PriceStrategyFactory * instance();

	PriceStrategy * getStrategy(StockWatch * stock);

private:
	static 	PriceStrategyFactory * instance_;
	PriceStrategyFactory();

	typedef std::map<std::string, PriceStrategy*, std::less<std::string> > StrategyMap;
	typedef StrategyMap::iterator StrategyMapIter;

	StrategyMap priceStrategies_;
};

#endif
