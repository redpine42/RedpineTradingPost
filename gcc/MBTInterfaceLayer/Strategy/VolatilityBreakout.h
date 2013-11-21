#pragma warning(disable:4786)
// VolatilityBreakout.h: interface for the VolatilityBreakout class.
//
//////////////////////////////////////////////////////////////////////

#ifndef VolatilityBreakout_h
#define VolatilityBreakout_h

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class VolatilityBreakout : public EntryStrategy  
{
public:
	VolatilityBreakout(StockWatch * stock, int ATRBars, int EMABars, double ATRMult, long startTradeTime, long endTradeTime);
	virtual ~VolatilityBreakout();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	double ATRMultiple_;
	int ATRBars_;
	int EMABars_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

