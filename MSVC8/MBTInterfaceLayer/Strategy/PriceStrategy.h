// PriceStrategy.h: interface for the PriceStrategy class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786) 

#ifndef PriceStrategy_h
#define PriceStrategy_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

class PriceStrategy  
{
public:
	enum OrderType
	{
		Limit,
		Market,
	};

	struct PricingData
	{
		PurchaseData::ExecutionType tradeType;
		double price;
		double stopPrice;
		double stopLowerPrice;
		double stopUpperPrice;
	};

	PriceStrategy();
	virtual ~PriceStrategy();

	virtual PricingData buy(const std::string & symbol) = 0;
	virtual PricingData sellShort(const std::string & symbol) = 0;

	virtual PricingData buyToCover(const std::string & symbol) = 0;
	virtual PricingData sell(const std::string & symbol) = 0;

	virtual PurchaseData::ExecutionType priceType(){return PurchaseData::ExecutionType::LIMIT;}

};

#endif
