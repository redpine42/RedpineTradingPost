#ifndef PositionMonitorManager_h
#define PositionMonitorManager_h

class PositionMonitor;
class SymbolData;

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

class PositionMonitorManager
{
public:
	struct OrderData
	{
		std::string symbol_;
		long quantity_;
		long quantityFilled_;
		double price_;
		std::string status_;
		std::string orderNumber_;
		std::string eventName_;
		long time_;
		PurchaseData::TradeType buySell_;
		PurchaseData::ExecutionType execType_;
	};

    static PositionMonitorManager * instance();
    static void removeInstance();

    ~PositionMonitorManager();

    void openPosition(SymbolData * stock, PurchaseData * data);
	void openPosition(SymbolData * stock, PurchaseData * data, DataEnums::PositionStatus posStatus);
    void closePosition(SymbolData * stock, PurchaseData * data);
	void removePosition(const std::string & symbol);
    
    void checkPosition(const std::string & symbol);
	void updateOrder(OrderData& pOrd);
	void recreatePosition(std::string & symbol, long quantity, double price, std::string & orderNumber, double closePrice, std::string & date, long time, std::string reason);
	
private:

    typedef std::map<std::string, PositionMonitor*, std::less<std::string> > PositionsMap;
    typedef PositionsMap::iterator PositionsMapIter;

    PositionMonitorManager();
    static PositionMonitorManager * instance_;

    PositionsMap positions_;
};

#endif


