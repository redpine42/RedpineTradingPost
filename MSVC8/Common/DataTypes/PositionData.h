#ifndef PositionData_h
#define PositionData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef strstream_h
#include <strstream>
#define strstream_h
#endif

struct PositionData
{
	long aggregatePosition_;
	long closableShares_;
	double commission_;
	long intradayPosition_;
	double intradayPrice_;
	double MMRPct_;
	double MMRUsed_;
	long overnightPosition_;
	double overnightPrice_;
	long pendingBuyShares_;
	long pendingSellShares_;
	double realizedPNL_;
	std::string symbol_;	
	std::string eventType_;
	std::string account_;
	std::string customer_;

	std::string getLogString()
	{
		std::strstream ss;
		ss << "!!!!Position Data!!!!" << "\n\tSymbol: " << symbol_ << "\n\tEvent: " << eventType_ << "\n\tAccount: " << account_ << "\n\tCustomer: " << customer_ 
			<< "\n\tCloseable Shares: " << closableShares_ << "\n\tPending Buy Shares: " << pendingBuyShares_ << "\n\tPending Sell Shares: " << pendingSellShares_
			<< "\n\tRealized PnL: " << realizedPNL_ << "\n" << std::ends;
		std::string msg = ss.str();
		ss.clear();
		ss.rdbuf()->freeze(0);
		return msg;
	}

};

#endif
