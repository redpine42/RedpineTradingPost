#include "PositionManager.h"
#include "TradeTrigger.h"
#include "AccountUpdate.h"
#include "PositionUpdate.h"
#include "OrderUpdate.h"
#include "OrderHistoryUpdate.h"
#include "L1DataUpdate.h"
#include "OrderStatusMessage.h"

#include "SymbolDataList.h"
#include "SymbolData.h"

int main(int argc, char* argv[])
{
	SymbolDataList::instance()->addSymbolData(new SymbolData("AUD/CAD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("AUD/JPY"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("AUD/NZD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("AUD/USD"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("CAD/CHF"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("CAD/JPY"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("CHF/JPY"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/AUD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/CAD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/CHF"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/GBP"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/JPY"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("EUR/USD"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("GBP/AUD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("GBP/CAD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("GBP/CHF"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("GBP/JPY"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("GBP/USD"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("NZD/JPY"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("NZD/USD"));

	SymbolDataList::instance()->addSymbolData(new SymbolData("USD/CAD"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("USD/CHF"));
	SymbolDataList::instance()->addSymbolData(new SymbolData("USD/JPY"));

	PositionManager * manager = PositionManager::instance();
	TradeTrigger tradeTrigger(manager);
	AccountUpdate accountUpdate(manager);
	PositionUpdate positionUpdate(manager);
	OrderUpdate orderUpdate(manager);
	OrderHistoryUpdate orderHistoryUpdate(manager);
	L1DataUpdate l1DataUpdate(manager);
	OrderStatusMessage orderStatusMessage(manager);

    Thread orderHistoryUpdateThread( &orderHistoryUpdate );
    orderHistoryUpdateThread.start();

    Thread orderUpdateThread( &orderUpdate );
    orderUpdateThread.start();

    Thread positionUpdateThread( &positionUpdate );
    positionUpdateThread.start();

    Thread accountUpdateThread( &accountUpdate );
    accountUpdateThread.start();

    Thread l1DataThread( &l1DataUpdate );
    l1DataThread.start();

    Thread tradeTriggerThread( &tradeTrigger );
    tradeTriggerThread.start();

    Thread orderStatusThread( &orderStatusMessage );
    orderStatusThread.start();

	orderHistoryUpdate.waitUntilReady();
	orderUpdate.waitUntilReady();
	tradeTrigger.waitUntilReady();
	accountUpdate.waitUntilReady();
	positionUpdate.waitUntilReady();
	l1DataUpdate.waitUntilReady();
	orderStatusMessage.waitUntilReady();

	orderHistoryUpdateThread.run();
	orderUpdateThread.run();
	positionUpdateThread.run();
	accountUpdateThread.run();
	l1DataThread.run();
	orderStatusThread.run();
	tradeTriggerThread.join();

	return 0;
};

