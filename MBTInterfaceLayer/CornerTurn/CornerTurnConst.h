#ifndef CornerTurnConst_h
#define CornerTurnConst_h

#ifndef string_h
#include <string>
#define string_h
#endif

namespace CornerTurnConst
{
	enum MessageType
	{
		Info,
		Alert,
		Debug,
		Error,
		Fatal_Error
	};


	static const std::string MESSAGETYPE = "MessageType";
	static const std::string SOURCE = "Source";
	static const std::string MESSAGETEXT = "MessageText";
	static const std::string COMSINK = "ComSink";
	static const std::string ACCOUNTMANAGER = "AccountManager";
	static const std::string ORDERSINK = "OrderSink";
	static const std::string ORDERMANAGER = "OrderManager";
	static const std::string QUOTESMANAGER = "QuotesManager";
	static const std::string TRADEMANAGER = "TradeManager";
	static const std::string CANDLEMANAGER = "CandleManager";
	static const std::string SYMBOLDATA = "SymbolData";
	static const std::string POSITIONMONITORMANAGER = "PositionMonitorManager";
	static const std::string POSITIONMONITOR = "PositionMonitor";
	

	static const std::string SYMBOL = "Symbol";
	static const std::string JDATE = "JDate";
	static const std::string TIME = "Time";
	static const std::string TIMESTAMP = "TimeStamp";
	static const std::string DATE = "Date";
	static const std::string SHORTABLE = "Shortable";
	static const std::string UPTICK = "Uptick";
	static const std::string LASTPRICE = "LastPrice";
	static const std::string LASTSIZE = "LastSize";
	static const std::string BID = "Bid";
	static const std::string ASK = "Ask";
	static const std::string BIDSIZE = "BidSize";
	static const std::string ASKSIZE = "AskSize";
	static const std::string VOLUME = "Volume";
	static const std::string TSSTATUS = "TSStatus";
	static const std::string TSTYPE = "TSType";
	static const std::string PRICE = "Price";
	static const std::string STOPPRICE = "StopPrice";
	static const std::string SIZE = "Size";
	static const std::string EXECUTIONTYPE = "ExecutionType";
	static const std::string TRADETYPE = "TradeType";
	static const std::string STOPLOWERPRICE = "StopLowerPrice";
	static const std::string STOPUPPERPRICE = "StopUpperPrice";
	static const std::string ORDERNUMBER = "OrderNumber";
	static const std::string MMID = "MMID";
	static const std::string CLOSED = "Closed";
	static const std::string MARKETSIDE = "MarketSide";
	static const std::string OPEN = "Open";
	static const std::string HIGH = "High";
	static const std::string LOW = "Low";
	static const std::string CLOSE = "Close";
	static const std::string CANDLEUPDATETYPE = "CandleUpdateType";
	static const std::string CANDLETIMETYPE = "CandleTimeType";
	static const std::string SUCCESS = "Success";
	static const std::string STATUS = "Status";

};

#endif
