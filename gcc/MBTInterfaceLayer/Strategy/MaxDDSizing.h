// MaxDDSizing.h: interface for the MaxDDSizing class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MaxDDSizing_h
#define MaxDDSizing_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef QuantityStrategy_h
#include "QuantityStrategy.h"
#endif

#ifndef MyDataTypes_h
#include "MyDataTypes.h"
#endif

class MaxDDSizing : public QuantityStrategy  
{
public:
	MaxDDSizing(MaxDDMSAData * data);
	virtual ~MaxDDSizing();

	int buy(const std::string & symbol, const double price);
	int sellShort(const std::string & symbol, const double price);

private:
	int calculateSize(const std::string & symbol, const double price);

	double margPer_;
	double maxDDPer_;
	double maxDD_;

};

#endif 
