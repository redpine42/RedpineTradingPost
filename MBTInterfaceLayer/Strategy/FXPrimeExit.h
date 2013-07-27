#ifndef FXPrimeExit_h
#define FXPrimeExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

#include <string>

class FXPrimeExit : public ExitStrategy  
{
public:
	FXPrimeExit(std::string & symbol,long startTime, long endTime);
	virtual ~FXPrimeExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

private:

	double precision_;
	double takeProfitPrice_;
	int maxPipsChange_;
};

#endif
