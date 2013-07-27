// EMAScalp.h: interface for the EMAScalp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EMAScalp_h
#define EMAScalp_h
#pragma warning(disable:4786) 

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class EMAScalp : public EntryStrategy  
{
public:
	EMAScalp(StockWatch * stock, int EMABars, int ADXBars, int ATRBars, long startTradeTime, long endTradeTime);
	virtual ~EMAScalp();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	int EMABars_;
	int ADXBars_;
	int ATRBars_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

