// TLScalp.h: interface for the TLScalp class.
//
//////////////////////////////////////////////////////////////////////


#ifndef TLScalp_h
#define TLScalp_h
#pragma warning(disable:4786) 

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class TLScalp : public EntryStrategy  
{
public:
	TLScalp(StockWatch * stock, int SlopeBars, int ADXBars, int ATRBars, int TLTradeTime, long startTradeTime, long endTradeTime);
	virtual ~TLScalp();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	int ADXBars_;
	int TLTradeTime_;
	int ATRBars_;
	int SlopeBars_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

