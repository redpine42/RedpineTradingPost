// TighteningStops.h: interface for the TighteningStops class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TighteningStops_h
#define TighteningStops_h

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

class TighteningStops : public ExitStrategy  
{
public:
	TighteningStops(long startTime, long endTime);
	~TighteningStops();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){highVal_ = 0.0; lowVal_ = 999999.0;};
private:
	bool stop(const std::string & symbol, double changeFromOpen, double changeFromBest, double bestPrice, double percentBest);

	double highVal_;
	double lowVal_;
};


#endif 
