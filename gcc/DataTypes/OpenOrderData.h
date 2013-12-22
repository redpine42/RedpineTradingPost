#ifndef OpenOrderData_h
#define OpenOrderData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef strstream_h
#include <strstream>
#define strstream_h
#endif

struct OpenOrderData
{
	std::string eventType_;
	std::string account_;
	std::string customer_;
	bool acknowledged_;
	std::string buySell_;
	std::string currentEvent_;
	std::string date_;
	std::string orderNumber_;
	long orderType_;
	std::string prefMMID_;
	double price_;
	long quantity_;
	bool replaceable_;
	std::string route_;
	long sharesFilled_;
	double stopLimit_;
	std::string symbol_;
	std::string time_;
	long timeInForce_;
	std::string token_;
	std::string traderId_;
	double trailingOffset_;
	long volumeType_;

	std::string getLogString()
	{
		std::strstream ss;
		ss << "!!!!Open Order Data!!!!" << "\n\tAccount: " << account_ << "\n\tEvent: " << eventType_ << "\n\tCustomer: " << customer_ << "\n\tCurrent Event: " << currentEvent_ 
			<< "\n\tBuySell: " << buySell_ << "\n\tStop Limit: " << stopLimit_ << "\n\tShares Filled: " << sharesFilled_
			<< "\n\tQuantity: " << quantity_ << "\n\tSymbol: " << symbol_ << "\n\tPrice: " << price_  << "\n\tRoute: " << route_
			 << "\n\tTime: " << time_ << "\n\tDate: " << date_ << "\n\tOrder Number: " << orderNumber_ << "\n\tToken: " << token_ << "\n" << std::ends;
		std::string msg = ss.str();
		ss.clear();
		ss.rdbuf()->freeze(0);
		return msg;
	}
};

#endif
