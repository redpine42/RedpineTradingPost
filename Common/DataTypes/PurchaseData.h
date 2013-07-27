#pragma warning(disable:4786) 
#ifndef PurchaseData_h
#define PurchaseData_h

#ifndef string_h
#include <string>
#define string_h
#endif

struct PurchaseData
{
    enum TradeStatus
    {
        None,
        SimulatedTrade,
        Sent,
        Executed,
        Filled,
        PartialFill,
        Failed,
		Canceled
    };

    enum TradeType
    {
        NoTrade,
        Buy,
        Sell,
        SellShort,
        BuyToCover
    };

    enum ExecutionType
    {
        NotExecuted = 0,
		DISCRETIONARY = 10043,
		LIMIT = 10030,
		LIMIT_CLOSE = 10057,
		LIMIT_OPEN = 10056,
		LIMIT_STOPMKT = 10064,
		LIMIT_TRAIL = 10054,
		LIMIT_TTO = 10050,
		MARKET = 10031,
		MARKET_CLOSE = 10039,
		MARKET_OPEN = 10038,
		MARKET_STOP = 10069,
		MARKET_TRAIL = 10055,
		MARKET_TTO = 10051,
		PART = 10046,
		PEGGED = 10062,
		RESERVE = 10040,
		RSV_DISC = 10044,
		RSV_PEGGED = 10066,
		RSV_TTO = 10052,
		STOPLMT_STOP = 10072,
		STOPLMT_TRAIL = 10068,
		STOPLMT_TTO = 10067,
		STOP_LIMIT = 10033,
		STOP_MARKET = 10032,
		STOP_STOP = 10073,
		STOP_TRAIL = 10065,
		STOP_TTO = 10053,
		TRAILING_STOP = 10034,
		TTO_ORDER = 10037,
		VWAP = 10063
    };


    std::string symbol_;
    long long size_;
	long long sharesFilled_;
    double price_;
	double stopPrice_;
	double stopLowerPrice_;
	double stopUpperPrice_;

	double strikePrice_;
    long long timePlaced_;
	long long timeFilled_;
	std::string date_;

	long long jdate_;
	double gap_;
    
    TradeType typeTrade_;
    ExecutionType executionType_;
	TradeStatus status_;

    std::string orderNumber_;
    std::string errorMessage_;
	std::string reason_;

	PurchaseData()
		: symbol_("UNK"),
		  size_(0),
		  sharesFilled_(0),
		  price_(0.0),
		  stopPrice_(0.0),
		  stopLowerPrice_(0.0),
		  stopUpperPrice_(0.0),
		  strikePrice_(0.0),
		  timePlaced_(0),
		  timeFilled_(0),
		  jdate_(0),
		  gap_(0.0),
		  typeTrade_(NoTrade),
		  executionType_(NotExecuted),
		  orderNumber_("None"),
		  errorMessage_("None"),
		  reason_("None")
	{
	}
private:
	friend std::ostream & operator<<(std::ostream& ostrm, const PurchaseData& data);

};

#endif

