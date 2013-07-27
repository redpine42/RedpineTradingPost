#pragma warning(disable:4786) 

// COTLEntry.h: interface for the COTLEntry class.
//
//////////////////////////////////////////////////////////////////////

#ifndef COTLEntry_h
#define COTLEntry_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef EntryStrateg_h
#include "EntryStrategy.h"
#endif

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

class COTLEntry : public EntryStrategy  
{
public:
	COTLEntry(StockWatch * stock,
		      long firstEntrySignalTime,
			  long TLStartTime,
			  long TLEndTime, 
			  long startTradeTime, 
			  long endTradeTime);

	~COTLEntry();

	bool buy();
	bool sellShort();

	void reset();
	
	void newTradeDay();

private:
	long priceTime_;

    int transactions_;
	long baseTLTime_;
	double rateOfChange_;
	double baseTLPrice_;
	bool belowTL_;
	bool lastTickInPosition_;
	bool TLCrossTrading_;
	bool ReverseTrading_;

	double tlrSlope_;

	int numSticks_;
	int numTradesPerStick_;
	int numReversals_;

	PurchaseData::TradeType tradeType_;

	bool setTrendLine();

	long TLStartTime_;
	long TLEndTime_;

};

#endif 

