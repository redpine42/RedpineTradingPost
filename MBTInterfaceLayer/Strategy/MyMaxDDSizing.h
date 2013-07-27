// MaxDDSizing.h: interface for the MaxDDSizing class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MyMaxDDSizing_h
#define MyMaxDDSizing_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef QuantityStrategy_h
#include "QuantityStrategy.h"
#endif

#ifndef MyDataTypes_h
#include "MyDataTypes.h"
#endif

class MyMaxDDSizing : public QuantityStrategy  
{
public:
	MyMaxDDSizing(MaxDDData * data);
	virtual ~MyMaxDDSizing();

	int buy(const std::string & symbol, const double price);
	int sellShort(const std::string & symbol, const double price);

private:
	int calculateSize(const std::string & symbol, const double price);

	MaxDDData * maxDDData_;
};

#endif 
