// ExitStrategy.h: interface for the ExitStrategy class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ExitStrategy_h
#define ExitStrategy_h

#ifndef string_h
#include <string>
#define string_h
#endif


class ExitStrategy  
{
public:
	ExitStrategy(std::string reason, long startTime, long endTime);
	virtual ~ExitStrategy();

	virtual bool buyToCover(const std::string & symbol, const double openPrice, const double price) = 0;
	virtual bool sell(const std::string & symbol, const double openPrice, const double price) = 0;
	std::string reason(){return reason_;}
	virtual void reset() = 0;

	bool tradeTime();

protected:
	std::string reason_;
	long startTradeTime_;
	long endTradeTime_;

};

#endif 

