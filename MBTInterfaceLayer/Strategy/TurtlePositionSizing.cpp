// TurtlePositionSizing.cpp: implementation of the TurtlePositionSizing class.
//
//////////////////////////////////////////////////////////////////////

#include "TurtlePositionSizing.h"
#include "AccountManager.h"
#include "ATRMetric.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TurtlePositionSizing::TurtlePositionSizing()
{
}

TurtlePositionSizing::~TurtlePositionSizing()
{

}

int TurtlePositionSizing::buy(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}


int TurtlePositionSizing::sellShort(const std::string & symbol, const double price)
{
	return calculateSize(symbol, price);
}

int TurtlePositionSizing::calculateSize(const std::string & symbol, const double price)
{
	long quantity = 0;
    double startBP = AccountManager::instance()->getStartBuyingPower();
    double BP = AccountManager::instance()->getBP();
    
	double ATR = getATR(symbol, 20);
	if(ATR > 0.0)
	{
		quantity = (long)((0.01 * startBP)/(ATR * price));
		if(quantity * price > BP)
		{
			quantity = 0;
		}
	}
    return quantity;
}


