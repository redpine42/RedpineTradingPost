// SpreadPrice.h: interface for the SpreadPrice class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SpreadPrice_h
#define SpreadPrice_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif

class SpreadPrice : public PriceStrategy  
{
public:
	SpreadPrice(double stopLoss, double takeProfit);
	virtual ~SpreadPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

private:
	double stopLoss_;
	double takeProfit_;


};

#endif
