#ifndef AccountData_h
#define AccountData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef strstream_h
#include <strstream>
#define strstream_h
#endif

struct AccountData
{
	enum AccountState
	{
		Unloaded = 0,
		Loading = 1,
		Reloading = 2,
		Loaded = 3,
		Unavailable = 4
	};
	std::string eventType_;
	std::string account_;
	long accountType_;
	std::string bank_;
	std::string baseCurrency_;
	std::string branch_;
	long cancelsToday_;
	double credit_;
	double currentEquity_;
	double currentExcess_;
	std::string customer_;
	double dailyRealizedPL_;
	double MMRMultiplier_;
	double MMRUsed_;
	double morningCash_;
	double morningEquity_;
	double morningExcess_;
	double overnightExcess_;
	bool permedForCADEquities_;
	bool permedForEquities_;
	bool permedForForex_;
	bool permedForFutures_;
	bool permedForOptions_;
	std::string routingId_;
	std::string semiDelimited_;
	long sharesToday_;
	AccountState state_;
	long tradesToday_;

	std::string getLogString()
	{
		std::strstream ss;
		ss << "\n\tAccount: " << account_ << "\n\tEvent: " << eventType_ << "\n\tCustomer: " << customer_ << "\n\tTrades Today: " << tradesToday_ 
			<< "\n\tCancels Today: " << cancelsToday_ << "\n\tShares Today: " << sharesToday_ << "\n\tCurrent Equity: " << currentEquity_
			<< "\n\tCurrent Excess: " << currentExcess_ << "\n\tDaily PnL: " << dailyRealizedPL_ << std::ends;
		std::string msg = ss.str();
		ss.clear();
		ss.rdbuf()->freeze(0);
		return msg;
	}

};

#endif
