#ifndef FixedExit_h
#define FixedExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

#include <string>

class FixedExit : public ExitStrategy  
{
public:
	FixedExit(std::string & symbol,long startTime, long endTime, double stopLoss, double takeProfit);
	virtual ~FixedExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

private:
	double pipsStopLoss_;
	double pipsTakeProfit_;

};

#endif
