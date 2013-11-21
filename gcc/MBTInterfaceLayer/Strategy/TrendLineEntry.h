#pragma warning(disable:4786) 
// TrendLineEntry.h: interface for the VolatilityBreakout class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TrendLineEntry_h
#define TrendLineEntry_h

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class TrendLineEntry : public EntryStrategy  
{
public:
	TrendLineEntry(StockWatch * stock, int TL1Bars, int TL2Bars, int RSIBars, int StochBars, long startTradeTime, long endTradeTime);
	virtual ~TrendLineEntry();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	int TL1Bars_;
	int TL2Bars_;
	int RSIBars_;
	int StochBars_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

