#pragma warning(disable:4786)
// QuantityStrategyFactory.h: interface for the QuantityStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef QuantityStrategyFactory_h
#define QuantityStrategyFactory_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class QuantityStrategy;

#ifndef string_h
#include <string>
#endif

#ifndef map_h
#include <map>
#endif

class QuantityStrategyFactory  
{
public:
	static QuantityStrategyFactory * instance();
	virtual ~QuantityStrategyFactory();

	QuantityStrategy * getStrategy(const std::string & symbol);

private:
	static QuantityStrategyFactory * instance_;
	QuantityStrategyFactory();

	typedef std::map<std::string, QuantityStrategy*, std::less<std::string> > QSMap;
	typedef QSMap::iterator QSMapIter;

	QSMap strategyMap_;
};

#endif 
