// TurtleExit.h: interface for the TurtleExit class.
//
//////////////////////////////////////////////////////////////////////
#ifndef TurtleExit_h
#define TurtleExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

class TurtleExit : public ExitStrategy  
{
public:
	TurtleExit(long startTime, long endTime);
	~TurtleExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);
	void reset(){};

};

#endif

