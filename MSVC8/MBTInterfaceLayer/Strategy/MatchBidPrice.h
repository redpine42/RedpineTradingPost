// MatchBidPrice.h: interface for the MatchBidPrice class.
//
//////////////////////////////////////////////////////////////////////
#ifndef MatchBidPrice_h
#define MatchBidPrice_h

#ifndef PriceStrategy_h
#include "PriceStrategy.h"
#endif

class MatchBidPrice : public PriceStrategy  
{
public:
	MatchBidPrice(int pipsTrail);
	~MatchBidPrice();

	PricingData buy(const std::string & symbol);
	PricingData sellShort(const std::string & symbol);

	PricingData buyToCover(const std::string & symbol);
	PricingData sell(const std::string & symbol);

private:
	double pipsTrail_;

};

#endif 

