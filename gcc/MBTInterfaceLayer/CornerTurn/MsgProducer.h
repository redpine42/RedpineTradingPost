#ifndef MsgProducer_h
#define MsgProducer_h

#include <activemq/library/ActiveMQCPP.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <decaf/lang/Integer.h>
#include <decaf/util/Date.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

#ifndef L1Data_h
#include "L1Data.h"
#endif

#ifndef L2Data_h
#include "L2Data.h"
#endif

#ifndef TimeSalesData_h
#include "TimeSalesData.h"
#endif

#ifndef AccountData_h
#include "AccountData.h"
#endif

#ifndef PositionData_h
#include "PositionData.h"
#endif

#ifndef OpenOrderData_h
#include "OpenOrderData.h"
#endif

#ifndef OrderHistoryData_h
#include "OrderHistoryData.h"
#endif

#ifndef CandleData_h
#include "CandleData.h"
#endif

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;

class MsgProducer
{
public:
	static MsgProducer * instance();
	static void removeInstance();

	void sendTextMessage(const CornerTurnConst::MessageType msgType, const std::string source, const std::string message);
	void sendL1Data(L1Data& data);
	void sendL2Data(L2Data& data);
	void sendTimeSalesData(TimeSalesData& data);
	void sendAccountUpdateMessage(AccountData & data);
	void sendPositionUpdateMessage(PositionData & data);
	void sendOpenOrderUpdateMessage(OpenOrderData & data);
	void sendOrderHistoryUpdateMessage(OrderHistoryData & data);
	void sendCandleData(CandleData & data);

	void sendTradeTrigger(PurchaseData & data);
	void sendOrder(PurchaseData & data);
	void cancelOrder(PurchaseData & data);
	void sendOrderStatus(std::string symbol, bool success, std::string msg);
	std::string fillStr(const std::string & str);

private:
	static MsgProducer * instance_;
	MsgProducer();
	~MsgProducer();

	MapMessage * createPurchaseMsg(PurchaseData & data);

	Connection* connection;
    Session* session;
    Destination* msgDest;
    MessageProducer* msgProd;
    Destination* eventDest;
    MessageProducer* eventProd;
    Destination* CandleDataDest;
    MessageProducer* CandleDataProd;
    Destination* L1DataDest;
    MessageProducer* L1DataProd;
    Destination* L2DataDest;
    MessageProducer* L2DataProd;
    Destination* TimeSalesDataDest;
    MessageProducer* TimeSalesDataProd;
    Destination* AccountDataDest;
    MessageProducer* AccountDataProd;
    Destination* PositionDataDest;
    MessageProducer* PositionDataProd;
    Destination* OpenOrderDataDest;
    MessageProducer* OpenOrderDataProd;
    Destination* OrderHistoryDataDest;
    MessageProducer* OrderHistoryDataProd;
    Destination* TradeTriggerDataDest;
    MessageProducer* TradeTriggerDataProd;
    Destination* CreateOrderDataDest;
    MessageProducer* CreateOrderDataProd;
    Destination* CancelOrderDataDest;
    MessageProducer* CancelOrderDataProd;
    Destination* OrderStatusDest;
    MessageProducer* OrderStatusProd;
    std::string brokerURI;
};

#endif
