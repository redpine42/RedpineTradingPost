// PairPricing.h: interface for the PairPricing class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)

#ifndef PairPricing_h
#define PairPricing_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

class PairPricing  
{
public:
	static PairPricing * instance();
	virtual ~PairPricing();

	void setPairPrice(const std::string & symbol, double price);

	double getUSDCost(const std::string & symbol, double price);
	double getUSDPipVal(const std::string & symbol, double price);

private:
	PairPricing();
	static PairPricing * instance_;

	typedef std::map<std::string, double, std::less<std::string> > PriceMap;
	typedef PriceMap::iterator PriceMapIter;

	PriceMap priceMap_;

};

#endif 