#ifndef OrderHistoryData_h
#define OrderHistoryData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef strstream_h
#include <strstream>
#define strstream_h
#endif

struct OrderHistoryData
{
	std::string eventType_;
	std::string account_;
	std::string customer_;
	std::string buySell_;
	long capacity_;
	long contractsAhead_;
	std::string date_;
	double discPrice_;
	long displayQuantity_;
	std::string event_;
	long execId_;
	std::string message_;
	std::string orderNumber_;
	long orderType_;
	std::string origTraderId_;
	std::string prefMMID_;
	double price_;
	long quantity_;
	std::string remoteId_;
	std::string route_;
	long sharesFilled_;
	double stopLimit_;
	std::string symbol_;
	std::string time_;
	long timeInForce_;
	std::string token_;
	std::string traderId_;
	long volumeType_;
	long execType_;

	std::string getLogString()
	{
		std::strstream ss;
		ss << "!!!!Order History Data!!!!" << "\n\tAccount: " << account_ << "\n\tEvent: " << eventType_ << "\n\tCustomer: " << customer_ << "\n\tCurrent Event: " << event_ 
			<< "\n\tBuySell: " << buySell_ << "\n\tStop Limit: " << stopLimit_ << "\n\tShares Filled: " << sharesFilled_
			<< "\n\tQuantity: " << quantity_ << "\n\tSymbol: " << symbol_ << "\n\tPrice: " << price_  << "\n\tRoute: " << route_ << "\n\tExecution Type: " << execType_
			 << "\n\tTime: " << time_ << "\n\tDate: " << date_ << "\n\tOrder Number: " << orderNumber_ << "\n\tToken: " << token_ 
			 << "\nMessage: " << message_ << std::ends;
		std::string msg = ss.str();
		ss.clear();
		ss.rdbuf()->freeze(0);
		return msg;
	}

};

#endif
