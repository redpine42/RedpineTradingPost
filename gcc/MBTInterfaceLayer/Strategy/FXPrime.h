#pragma warning(disable:4786)
// FXPrime.h: interface for the VolatilityBreakout class.
//
//////////////////////////////////////////////////////////////////////

#ifndef FXPrime_h
#define FXPrime_h

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class FXPrime : public EntryStrategy  
{
public:
	FXPrime(StockWatch * stock, int ATRBars, int RSIBars, int CCISlowBars, int CCIFastBars, long startTradeTime, long endTradeTime);
	virtual ~FXPrime();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	int ATRBars_;
	int RSIBars_;
	int CCISlowBars_;
	int CCIFastBars_;
	double cciFastPrev_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

