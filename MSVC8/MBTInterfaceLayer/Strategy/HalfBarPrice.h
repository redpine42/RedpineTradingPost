// HalfBarPrice.h: interface for the HalfBarPrice class.
//
//////////////////////////////////////////////////////////////////////

#ifndef HalfBarPrice_h
#define HalfBarPrice_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif


class HalfBarPrice : public PriceStrategy  
{
public:
	HalfBarPrice();
	virtual ~HalfBarPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

	PurchaseData::ExecutionType priceType(){return PurchaseData::ExecutionType::LIMIT;}

};

#endif 