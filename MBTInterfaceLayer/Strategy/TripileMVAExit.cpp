// TripileMVAExit.cpp: implementation of the TripileMVAExit class.
//
//////////////////////////////////////////////////////////////////////

#include "TripileMVAExit.h"
#include "EMAMetric.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TripileMVAExit::TripileMVAExit(long startTime, long endTime)
	: ExitStrategy("Tripile Moving Average", startTime, endTime),
	  fast_(3),
	  medium_(9),
	  slow_(13)
{

}

TripileMVAExit::~TripileMVAExit()
{

}

bool TripileMVAExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	double fastMVA = getEMA(symbol, fast_);
//	double mediumMVA = getEMA(symbol, medium_);
	double slowMVA = getEMA(symbol, slow_);

	if(fastMVA > slowMVA)
	{
		return true;
	}
	return false;
}

bool TripileMVAExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	double fastMVA = getEMA(symbol, fast_);
//	double mediumMVA = getEMA(symbol, medium_);
	double slowMVA = getEMA(symbol, slow_);

	if(fastMVA < slowMVA)
	{
		return true;
	}
	return false;
}


