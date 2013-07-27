// TripileMVAEntry.h: interface for the TripileMVAEntry class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TripileMVAEntry_h
#define TripileMVAEntry_h

#ifndef EntryStrategy_h
#include "EntryStrategy.h"
#endif

class TripileMVAEntry : public EntryStrategy  
{
public:
	TripileMVAEntry(StockWatch * stock, long fast, long medum, long slow, long startTradeTime, long endTradeTime);
	virtual ~TripileMVAEntry();

	bool buy();
	bool sellShort();


	void reset(){};
	void newTradeDay(){};

private:
	long fast_;
	long medium_;
	long slow_;
};

#endif

