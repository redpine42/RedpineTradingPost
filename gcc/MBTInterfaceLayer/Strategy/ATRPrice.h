// ATRPrice.h: interface for the ATRPrice class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ATRPrice_h
#define ATRPrice_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif

class ATRPrice : public PriceStrategy  
{
public:
	ATRPrice();
	virtual ~ATRPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);
};

#endif
