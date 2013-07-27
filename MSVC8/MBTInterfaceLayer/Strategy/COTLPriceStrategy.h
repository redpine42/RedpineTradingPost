// COTLPriceStrategy.h: interface for the COTLPriceStrategy class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COTLPriceStrategy_h
#define COTLPriceStrategy_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif

class COTLPriceStrategy : public PriceStrategy  
{
public:
	COTLPriceStrategy(double pipsStopLoss);
	virtual ~COTLPriceStrategy();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);
private:
	double pipsStopLoss_;
};

#endif
