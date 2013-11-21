// UpBarsProfitExit.h: interface for the UpBarsProfitExit class.
//
//////////////////////////////////////////////////////////////////////


#ifndef UpBarsProfitExit_h
#define UpBarsProfitExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

class UpBarsProfitExit : public ExitStrategy  
{
public:
	UpBarsProfitExit(long startTime, long endTime);
	virtual ~UpBarsProfitExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};
};

#endif 
