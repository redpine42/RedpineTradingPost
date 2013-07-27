#pragma warning(disable:4786) 

// TurtleBreakout.h: interface for the TurtleBreakout class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TurtleBreakout_h
#define TurtleBreakout_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef EntryStrategy_h
#include "EntryStrategy.h"
#endif

class TurtleBreakout : public EntryStrategy  
{
public:
	TurtleBreakout(StockWatch * stock, int numBars, long startTradeTime, long endTradeTime);
	~TurtleBreakout();

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	int numBars_;
};

#endif
