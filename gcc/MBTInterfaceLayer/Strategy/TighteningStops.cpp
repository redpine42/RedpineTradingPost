// TighteningStops.cpp: implementation of the TighteningStops class.
//
//////////////////////////////////////////////////////////////////////

#include "TighteningStops.h"
#include "ATRMetric.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TighteningStops::TighteningStops(long startTime, long endTime)
:ExitStrategy("Tightening Stops Exit", startTime, endTime),
 highVal_(0.0),
 lowVal_(999999.0)
{

}

TighteningStops::~TighteningStops()
{

}

// Trade conditions
//  1. 2 ATR Stop
//  2. 10 cent gain passed, close when drops to 5 cent gain
//  3. 1.5% gain, close postion when <= 1%
//  4. 2% gain close when change of 1% from best postion
bool TighteningStops::buyToCover(const std::string & symbol, const double openPrice, const double currentPrice)
{
	if(currentPrice < lowVal_)
    {
        lowVal_ = currentPrice;
    }
    
	double priceChange = 0.0;
//    double percentFromBest = 0.0;
	double changeFromOpen = 0.0;
	double changeFromBest = 0.0;
	double bestPrice = 0.0;
	double percentBest = 0.0;


//    priceChange = openPrice/currentPrice;
//  percentFromBest = lowVal_/currentPrice;
	changeFromOpen = openPrice - lowVal_;

	changeFromBest = currentPrice - lowVal_;
	bestPrice = openPrice - lowVal_;
	percentBest = openPrice/lowVal_;

	return stop(symbol, changeFromOpen, changeFromBest, bestPrice, percentBest);
}

bool TighteningStops::sell(const std::string & symbol, const double openPrice, const double currentPrice)
{
    if(currentPrice > highVal_)
    {
        highVal_ = currentPrice;
    }
    
//	double priceChange = 0.0;
//    double percentFromBest = 0.0;
	double changeFromOpen = 0.0;
	double changeFromBest = 0.0;
	double bestPrice = 0.0;
	double percentBest = 0.0;


 //   priceChange = currentPrice/openPrice;
//  percentFromBest = currentPrice/highVal_;
	changeFromOpen = highVal_ - openPrice;

	changeFromBest = highVal_ - currentPrice;
    bestPrice = highVal_ - openPrice;
	percentBest = highVal_/openPrice;

	return stop(symbol, changeFromOpen, changeFromBest, bestPrice, percentBest);
}


bool TighteningStops::stop(const std::string & symbol, double changeFromOpen, double changeFromBest, double bestPrice, double percentBest)
{
	double atr = getATR(symbol, 20);
	if(atr < .04)
	{
		atr = .04;
	}

	if((changeFromOpen > (4.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .9) ||
		(changeFromOpen > (3.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .7) || 
		(changeFromOpen > (2.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .4))
	{
		if((changeFromOpen > (4.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .9))
		{
			reason_ = "4 ATR rule!";
		}
		else if((changeFromOpen > (3.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .7))
		{
			reason_ = "3 ATR rule!";
		}
		else if((changeFromOpen > (2.0 * atr) && (bestPrice - changeFromBest)/bestPrice < .4))
		{
			reason_ = "2 ATR rule!";
		}
		return true;
	}
	return false;
}

