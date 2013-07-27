// QuantityStrategy.h: interface for the QuantityStrategy class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786) 

#ifndef QuantityStrategy_h
#define QuantityStrategy_h

#ifndef string_h
#include <string>
#define string_h
#endif


class QuantityStrategy  
{
public:
	QuantityStrategy();
	virtual ~QuantityStrategy();

	virtual int buy(const std::string & symbol, const double price) = 0;
	virtual int sellShort(const std::string & symbol, const double price) = 0;

};

#endif

