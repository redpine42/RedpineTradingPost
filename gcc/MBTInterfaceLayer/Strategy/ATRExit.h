// ATRExit.h: interface for the ATRExit class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ATRExit_h
#define ATRExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

class ATRExit : public ExitStrategy  
{
public:
	ATRExit(long startTime, long endTime);
	virtual ~ATRExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

};

#endif
