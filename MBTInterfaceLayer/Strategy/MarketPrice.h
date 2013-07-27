// MarketPrice.h: interface for the MarketPrice class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MarketPrice_h
#define MarketPrice_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif


class MarketPrice : public PriceStrategy  
{
public:
	MarketPrice();
	virtual ~MarketPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

	PurchaseData::ExecutionType priceType(){return PurchaseData::ExecutionType::MARKET;}

};

#endif
