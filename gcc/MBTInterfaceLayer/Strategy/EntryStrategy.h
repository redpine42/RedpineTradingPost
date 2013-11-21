// EntryStrategy.h: interface for the EntryStrategy class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786) 

#ifndef EntryStrategy_h
#define EntryStrategy_h

class CandleStick;

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef SymbolData_h
#include "SymbolData.h"
#endif

class EntryStrategy  
{
public:
	EntryStrategy(SymbolData * stock, std::string reason, long startTradeTime, long endTradeTime);
	virtual ~EntryStrategy();

	virtual bool buy() = 0;
	virtual bool sellShort() = 0;

	virtual bool buy(CandleStick * stick){return false;}
	virtual bool sellShort(CandleStick * stick){return false;}

	std::string reason(){return reason_;}
	virtual void reset() = 0;

	virtual void newTradeDay() = 0;
	

protected:
	SymbolData * stock_;

	void reason(std::string reason) {reason_ = reason;}
	bool isTradingTime(double time);
	bool newDay_;

private:
	std::string reason_;
	long startTradeTime_;
	long endTradeTime_;

};

#endif 
