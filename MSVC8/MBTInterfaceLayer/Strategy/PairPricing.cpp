// PairPricing.cpp: implementation of the PairPricing class.
//
//////////////////////////////////////////////////////////////////////

#include "PairPricing.h"
#include "MsgProducer.h"

const std::string myClassName = "PairPricing";

PairPricing * PairPricing::instance_ = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PairPricing::PairPricing()
{
	setPairPrice("CHF/JPY", 98.679);
	setPairPrice("EUR/CHF", 1.6544);
	setPairPrice("EUR/GBP", 0.72114);
	setPairPrice("EUR/JPY", 163.27);
	setPairPrice("EUR/SEK", 9.3921);
	setPairPrice("EUR/USD", 1.4639);
	setPairPrice("GBP/CHF", 2.2930);
	setPairPrice("GBP/JPY", 226.29);
	setPairPrice("GBP/USD", 2.0289);
	setPairPrice("USD/CAD", 1.0076);
	setPairPrice("USD/CHF", 1.1301);
	setPairPrice("USD/DKK", 5.0951);
	setPairPrice("USD/JPY", 111.53);
	
	setPairPrice("EUR/AUD", 1.6761);
	setPairPrice("EUR/CAD", 1.4676);
	setPairPrice("EUR/NZD", 1.8862);
	setPairPrice("CAD/JPY", 111.33);
	setPairPrice("CAD/CHF", 1.3333);

	setPairPrice("AUD/CAD", 0.8744);
	setPairPrice("AUD/JPY", 94.7);
	setPairPrice("AUD/NZD", 1.1373);
	setPairPrice("AUD/USD", 0.8721);
	setPairPrice("NZD/USD", 0.7663);
	setPairPrice("NZD/JPY", 83.17);
	setPairPrice("USD/NOK", 5.3424);
	setPairPrice("USD/SEK", 6.3562);

}

PairPricing::~PairPricing()
{

}

PairPricing * PairPricing::instance()
{
	if(0 == instance_)
	{
		instance_ = new PairPricing();
	}
	return instance_;
}

void PairPricing::setPairPrice(const std::string & symbol, double price)
{
	priceMap_[symbol] = price;
}

double PairPricing::getUSDPipVal(const std::string & symbol, double price)
{
	// figure out pips to USD.
	double USDPriceChange = 1.0;

	double precision = .0001;

	// Base pair
	std::string firstSymbol = symbol.substr(0,3);

	// second pair symobl
	std::string secondSymbol = symbol.substr(4,3);

	if(secondSymbol == "JPY")
	{
		precision = .01;
	}

	if(secondSymbol == "USD")
	{
			USDPriceChange = 1.0;
	}
	else if(firstSymbol == "USD")
	{
		USDPriceChange = (10000.0 * precision)/price;
	}
	else
	{
		std::string baseSymbol = "USD";
		baseSymbol += "/";
		baseSymbol += secondSymbol;
			
			
		PriceMapIter iter;
		iter = priceMap_.find(baseSymbol);
		if(iter != priceMap_.end())
		{
			USDPriceChange = (10000.0 * precision)/(*iter).second;
		}
		else
		{
 			// Get Pair
			baseSymbol = firstSymbol;
			baseSymbol += "/";
			baseSymbol += "USD";

			PriceMapIter iter;
			iter = priceMap_.find(baseSymbol);
			if(iter != priceMap_.end())
			{
				USDPriceChange = (10000.0 * precision) * (*iter).second;
			}
			else
			{
				std::string msg = "Couldn't calculate USD pips for pair: ";
				msg += symbol;
				msg += "\nFailed to record trade price";
				MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, myClassName, msg);
				return 0.0;
			}
		}
	}
	return USDPriceChange;
}

double PairPricing::getUSDCost(const std::string & symbol, double price)
{
	double usdPrice = 1.0;

	// Base pair
	std::string firstSymbol = symbol.substr(0,3);

	// second pair symobl
	std::string secondSymbol = symbol.substr(4,3);

	// Need to figure out purchase price using 
	// base pair price.  Only commits 1/12 buying power in US dollars
	if(secondSymbol == "USD")
	{
		usdPrice = price;
	}
	else if (firstSymbol == "USD")
	{
		usdPrice = 1.0;
	}
	// Opps mixed pair.  Need to look up USD related price
	// if EUR/GBP need to find EUR/USD price
	else
	{
		std::string baseSymbol = firstSymbol;
		baseSymbol += "/";
		baseSymbol += "USD";
			
 		// Get Pair
		PriceMapIter iter;
		iter = priceMap_.find(baseSymbol);
		if(iter != priceMap_.end())
		{
			usdPrice = (*iter).second;
		}
		else
		{
			baseSymbol = "USD";
			baseSymbol += "/";
			baseSymbol += firstSymbol;
			
 			// Get Pair
			PriceMapIter iter;
			iter = priceMap_.find(baseSymbol);
			if(iter != priceMap_.end())
			{
				usdPrice = 1.0/(*iter).second;
			}
		}
	}
	return usdPrice;
}


