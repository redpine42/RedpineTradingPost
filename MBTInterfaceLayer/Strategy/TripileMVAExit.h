// TripileMVAExit.h: interface for the TripileMVAExit class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TripileMVAExit_h
#define TripileMVAExit_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif


class TripileMVAExit : public ExitStrategy  
{
public:
	TripileMVAExit(long startTime, long endTime);
	virtual ~TripileMVAExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

private:
	long fast_;
	long medium_;
	long slow_;
};

#endif

