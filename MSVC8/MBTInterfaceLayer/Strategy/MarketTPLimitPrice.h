// MarketTPLimitPrice.h: interface for the MarketPrice class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MarketTPLimitPrice_h
#define MarketTPLimitPrice_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif


class MarketTPLimitPrice : public PriceStrategy  
{
public:
	MarketTPLimitPrice(double takeProfitPips);
	virtual ~MarketTPLimitPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

	PurchaseData::ExecutionType priceType(){return PurchaseData::ExecutionType::MARKET;}

private:
	double takeProfitPips_;
};

#endif
