#ifndef PositionMonitor_h
#define PositionMonitor_h

#ifndef PositionMonitorManager_h
#include "PositionMonitorManager.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

class SymbolData;
struct PurchaseData;
class ExitStrategy;
class MonitorOpenOrder;
class MonitorCloseOrder;

class PositionMonitor
{
public:

    PositionMonitor(SymbolData * stock, PurchaseData * data);
	~PositionMonitor();

    void closePosition(SymbolData * stock, PurchaseData * data);

    void checkPosition();
	void updateOrder(PositionMonitorManager::OrderData& pOrd);

	void createClose(PurchaseData * data, double currentPrice);

	void status(DataEnums::PositionStatus posStatus){posStatus_ = posStatus;}
	DataEnums::PositionStatus status(){return posStatus_;}

	void refreshPosition(long quantity, double price);

private:
	void checkOpenFilledOrder();

    SymbolData * stock_;
	DataEnums::PositionStatus posStatus_;

    long positionTime_;
	double startPrice_;

    PurchaseData * openData_;
    PurchaseData * closeData_;
	std::string reason_;

	ExitStrategy * exitStrategy_;

	MonitorOpenOrder * monitorOpen_;
	MonitorCloseOrder * monitorClose_;

};

#endif

