#ifndef ExitExit_h
#define ExitExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

#include <string>

class ExitExit : public ExitStrategy  
{
public:
	ExitExit(std::string & symbol,long startTime, long endTime);
	virtual ~ExitExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

private:

};

#endif
