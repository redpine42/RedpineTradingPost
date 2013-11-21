// MarketLimitPricing.h: interface for the MarketLimitPricing class.
//
//////////////////////////////////////////////////////////////////////

//
//////////////////////////////////////////////////////////////////////

#ifndef MarketLimitPricing_h
#define MarketLimitPricing_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif


class MarketLimitPricing : public PriceStrategy  
{
public:
	MarketLimitPricing();
	virtual ~MarketLimitPricing();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

	PurchaseData::ExecutionType priceType(){return PurchaseData::ExecutionType::MARKET;}

};

#endif
