// TLScalp.h: interface for the TLScalp class.
//
//////////////////////////////////////////////////////////////////////


#ifndef TLScalp2_h
#define TLScalp2_h
#pragma warning(disable:4786) 

class StockWatch;
class CandleStick;
#include <fstream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntryStrategy.h"

class TLScalp2 : public EntryStrategy  
{
public:
	TLScalp2(StockWatch * stock, int SlopeBars, int ADXBars, int ATRBars, long startTradeTime, long endTradeTime);
	virtual ~TLScalp2();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	enum TradeState
	{
		Waiting,
		InLong,
		CloseLong,
		InShort,
		CloseShort
	};

	
	TradeState tradeState_;
	
	int ADXBars_;
	int ATRBars_;
	int SlopeBars_;

	double precision_;
	std::ofstream debugLog_;
};

#endif

