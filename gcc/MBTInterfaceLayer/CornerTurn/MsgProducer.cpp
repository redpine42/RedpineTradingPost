#include "MsgProducer.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"

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
#include <stdlib.h>
#include <iostream>
#include <memory>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;

MsgProducer * MsgProducer::instance_ = 0;

MsgProducer * MsgProducer::instance()
{
	if(0 == instance_)
	{
		instance_ = new MsgProducer();
	}
	return instance_;
}


MsgProducer::MsgProducer()
{
    activemq::library::ActiveMQCPP::initializeLibrary();

	brokerURI = CornerTurnConfig::instance()->getURI();
 
	try 
	{
		// Create a ConnectionFactory
		std::auto_ptr<ConnectionFactory> connectionFactory(
            ConnectionFactory::createCMSConnectionFactory( brokerURI ) );

        // Create a Connection
        connection = connectionFactory->createConnection();
        connection->start();

        // Create a Session
        session = connection->createSession( Session::AUTO_ACKNOWLEDGE );

        // Create the destination (Topic or Queue)
        msgDest = session->createTopic( "MessageData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        msgProd = session->createProducer( msgDest );
        msgProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        eventDest = session->createTopic( "EventData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        eventProd = session->createProducer( eventDest );
        eventProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        CandleDataDest = session->createTopic( "CandleData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        CandleDataProd = session->createProducer( CandleDataDest );
        CandleDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        L1DataDest = session->createTopic( "L1Data" );

        // Create a MessageProducer from the Session to the Topic or Queue
        L1DataProd = session->createProducer( L1DataDest );
        L1DataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        L2DataDest = session->createTopic( "L2Data" );

        // Create a MessageProducer from the Session to the Topic or Queue
        L2DataProd = session->createProducer( L2DataDest );
        L2DataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        TimeSalesDataDest = session->createTopic( "TimeSalesData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        TimeSalesDataProd = session->createProducer( TimeSalesDataDest );
        TimeSalesDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        AccountDataDest = session->createTopic( "AccountData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        AccountDataProd = session->createProducer( AccountDataDest );
        AccountDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        PositionDataDest = session->createTopic( "PositionData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        PositionDataProd = session->createProducer( PositionDataDest );
        PositionDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        OpenOrderDataDest = session->createTopic( "OpenOrderData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        OpenOrderDataProd = session->createProducer( OpenOrderDataDest );
        OpenOrderDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

        // Create the destination (Topic or Queue)
        OrderHistoryDataDest = session->createTopic( "OpenOrderHistoryData" );

        // Create a MessageProducer from the Session to the Topic or Queue
        OrderHistoryDataProd = session->createProducer( OrderHistoryDataDest );
        OrderHistoryDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

		TradeTriggerDataDest = session->createTopic( "TradeTriggerData" );
		TradeTriggerDataProd = session->createProducer( TradeTriggerDataDest );
        TradeTriggerDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

		CreateOrderDataDest = session->createTopic( "CreateOrder" );
		CreateOrderDataProd = session->createProducer( CreateOrderDataDest );
        CreateOrderDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

		CancelOrderDataDest = session->createTopic( "CancelOrder" );
		CancelOrderDataProd = session->createProducer( CancelOrderDataDest );
        CancelOrderDataProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );

		OrderStatusDest = session->createTopic( "OrderStatus" );
		OrderStatusProd = session->createProducer( OrderStatusDest );
        OrderStatusProd->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
	}
	catch ( CMSException& e ) 
	{
        e.printStackTrace();
    }
}


void MsgProducer::sendTextMessage(const CornerTurnConst::MessageType msgType, const std::string source, const std::string messageText)
{
	MapMessage* message = session->createMapMessage();
    message->setInt(CornerTurnConst::MESSAGETYPE, msgType);
	message->setString(CornerTurnConst::SOURCE, fillStr(source));
	message->setString(CornerTurnConst::MESSAGETEXT, fillStr(messageText));

	// Tell the producer to send the message
    msgProd->send( message );

	std::cout << "Message Type: " << msgType << std::endl;
	std::cout << "Source: " << source << std::endl;
	std::cout << "Text: " << messageText << std::endl;

	delete message;
}
	
void MsgProducer::sendCandleData(CandleData & data)
{
	MapMessage* message = session->createMapMessage();
	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	message->setInt(CornerTurnConst::JDATE, data.jdate_);
	message->setInt(CornerTurnConst::TIME, data.startTime_);
	    
    message->setInt(CornerTurnConst::VOLUME, data.volume_);
    message->setDouble(CornerTurnConst::OPEN, data.open_);
    message->setDouble(CornerTurnConst::HIGH, data.high_);
    message->setDouble(CornerTurnConst::LOW, data.low_);
    message->setDouble(CornerTurnConst::CLOSE, data.close_);

	message->setByte(CornerTurnConst::CANDLETIMETYPE, (char)data.candleTimeType_);
	message->setByte(CornerTurnConst::CANDLEUPDATETYPE, (char)data.candleUpdateType_);

	// Tell the producer to send the message
    CandleDataProd->send( message );

	delete message;
}

void MsgProducer::sendL1Data(L1Data& data)
{
	MapMessage* message = session->createMapMessage();
	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	message->setInt(CornerTurnConst::JDATE, data.jdate_);
	message->setInt(CornerTurnConst::TIME, data.time_);
	message->setDouble(CornerTurnConst::TIMESTAMP, data.timeStamp_);
	    
    message->setBoolean(CornerTurnConst::SHORTABLE, data.shortable_);
    message->setBoolean(CornerTurnConst::UPTICK, data.upTick_);
    message->setDouble(CornerTurnConst::LASTPRICE, data.price_);
    message->setInt(CornerTurnConst::LASTSIZE, data.size_);
    message->setDouble(CornerTurnConst::BID, data.bid_);
    message->setDouble(CornerTurnConst::ASK, data.ask_);
    message->setInt(CornerTurnConst::BIDSIZE, data.bidSize_);
    message->setInt(CornerTurnConst::ASKSIZE, data.askSize_);
    message->setInt(CornerTurnConst::VOLUME, data.volume_);

	// Tell the producer to send the message
    L1DataProd->send( message );

	delete message;
}

void MsgProducer::sendL2Data(L2Data& data)
{
	MapMessage* message = session->createMapMessage();
	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	message->setString(CornerTurnConst::MMID, fillStr(data.MMID_));
	message->setString(CornerTurnConst::SOURCE, fillStr(data.source_));
	message->setInt(CornerTurnConst::JDATE, data.jdate_);
	message->setInt(CornerTurnConst::TIME, data.time_);
	message->setDouble(CornerTurnConst::TIMESTAMP, data.timeStamp_);
	    
    message->setBoolean(CornerTurnConst::CLOSED, data.closed_);
    message->setDouble(CornerTurnConst::LASTPRICE, data.price_);
    message->setInt(CornerTurnConst::LASTSIZE, data.size_);
    message->setByte(CornerTurnConst::MARKETSIDE, data.marketSide_);

	// Tell the producer to send the message
    L2DataProd->send( message );

	delete message;
}

void MsgProducer::sendAccountUpdateMessage(AccountData & data)
{
	MapMessage* message = session->createMapMessage();
	message->setString("EVENT_TYPE",fillStr(data.eventType_));
	message->setString("ACCOUNT",fillStr(data.account_));
	message->setLong("ACCOUNT_TYPE",data.accountType_);
	message->setString("BANK",fillStr(data.bank_));
	message->setString("BASE_CURRENCY",fillStr(data.baseCurrency_));
	message->setString("BRANCH",fillStr(data.branch_));
	message->setLong("CANCELS_TODAY",data.cancelsToday_);
	message->setDouble("CREDIT",data.credit_);
	message->setDouble("CURRENT_EQUITY",data.currentEquity_);
	message->setDouble("CURRENT_EXCESS",data.currentExcess_);
	message->setString("CUSTOMER",fillStr(data.customer_));
	message->setDouble("DAILY_REALIZED_PL",data.dailyRealizedPL_);
	message->setDouble("MMR_MULTIPLIER",data.MMRMultiplier_);
	message->setDouble("MMR_USED",data.MMRUsed_);
	message->setDouble("MORNING_CASH",data.morningCash_);
	message->setDouble("MORNING_EQUITY",data.morningEquity_);
	message->setDouble("MORNING_EXCESS",data.morningExcess_);
	message->setDouble("OVERNIGHT_EXCESS",data.overnightExcess_);
	message->setBoolean("PERMED_FOR_CAD_EQUITIES",data.permedForCADEquities_);
	message->setBoolean("PERMED_FOR_EQUITIES",data.permedForEquities_);
	message->setBoolean("PERMED_FOR_FOREX",data.permedForForex_);
	message->setBoolean("PERMED_FOR_FUTURES",data.permedForFutures_);
	message->setBoolean("PERMED_FOR_OPTIONS",data.permedForOptions_);
	message->setString("ROUTING_ID",fillStr(data.routingId_));
	message->setString("SEMI_DELIMITED",fillStr(data.semiDelimited_));
	message->setLong("SHARES_TODAY",data.sharesToday_);
	message->setLong("STATE",(long)data.state_);
	message->setLong("TRADES_TODAY",data.tradesToday_);

	AccountDataProd->send(message);

	delete message;
}

void MsgProducer::sendPositionUpdateMessage(PositionData & data)
{
	MapMessage* message = session->createMapMessage();
	message->setLong("AGGREGATE_POSITION",data.aggregatePosition_);
	message->setLong("CLOSABLE_SHARES",data.closableShares_);
	message->setDouble("COMMISSION",data.commission_);
	message->setLong("INTRADAY_POSITION",data.intradayPosition_);
	message->setDouble("INTRADAY_PRICE",data.intradayPrice_);
	message->setDouble("MMR_PCT",data.MMRPct_);
	message->setDouble("MMR_USED",data.MMRUsed_);
	message->setLong("OVERNIGHT_POSITION",data.overnightPosition_);
	message->setDouble("OVERNIGHT_PRICE",data.overnightPrice_);
	message->setLong("PENDING_BUY_SHARES",data.pendingBuyShares_);
	message->setLong("PENDING_SELL_SHARES",data.pendingSellShares_);
	message->setDouble("REALIZED_PNL",data.realizedPNL_);
	message->setString(CornerTurnConst::SYMBOL,data.symbol_);	
	message->setString("EVENT_TYPE",fillStr(data.eventType_));
	message->setString("ACCOUNT",fillStr(data.account_));
	message->setString("CUSTOMER",fillStr(data.customer_));

	PositionDataProd->send(message);

	delete message;
}

void MsgProducer::sendOpenOrderUpdateMessage(OpenOrderData & data)
{
	MapMessage* message = session->createMapMessage();
	message->setString("EVENT_TYPE",fillStr(data.eventType_));
	message->setString("ACCOUNT",fillStr(data.account_));
	message->setString("CUSTOMER",fillStr(data.customer_));
	message->setBoolean("ACKNOWLEDGED",data.acknowledged_);
	message->setString("BUY_SELL",fillStr(data.buySell_));
	message->setString("CURRENT_EVENT",fillStr(data.currentEvent_));
	message->setString("DATE",fillStr(data.date_));
	message->setString("ORDER_NUMBER",fillStr(data.orderNumber_));
	message->setLong("ORDER_TYPE",data.orderType_);
	message->setString("PREF_MMID",fillStr(data.prefMMID_));
	message->setDouble("PRICE",data.price_);
	message->setLong("QUANTITY",data.quantity_);
	message->setBoolean("REPLACEABLE",data.replaceable_);
	message->setString("ROUTE",fillStr(data.route_));
	message->setLong("SHARES_FILLED",data.sharesFilled_);
	message->setDouble("STOP_LIMIT",data.stopLimit_);
	message->setString(CornerTurnConst::SYMBOL,fillStr(data.symbol_));
	message->setString("TIME",fillStr(data.time_));
	message->setLong("TIME_IN_FORCE",data.timeInForce_);
	message->setString("TOKEN",fillStr(data.token_));
	message->setString("TRADER_ID",fillStr(data.traderId_));
	message->setDouble("TRAILING_OFFSET",data.trailingOffset_);
	message->setLong("VOLUME_TYPE",data.volumeType_);

	OpenOrderDataProd->send(message);
	delete message;
}

void MsgProducer::sendOrderHistoryUpdateMessage(OrderHistoryData & data)
{
	MapMessage* message = session->createMapMessage();
	message->setString("EVENT_TYPE", fillStr(data.eventType_));
	message->setString("ACCOUNT", fillStr(data.account_));
	message->setString("CUSTOMER", fillStr(data.customer_));
	message->setString("BUY_SELL", fillStr(data.buySell_));
	message->setLong("CAPACITY", data.capacity_);
	message->setLong("CONTRACTS_AHEAD", data.contractsAhead_);
	message->setString("DATE", fillStr(data.date_));
	message->setDouble("DISC_PRICE", data.discPrice_);
	message->setLong("DISPLAY_QUANTITY", data.displayQuantity_);
	message->setString("EVENT", fillStr(data.event_));
	message->setLong("EXEC_ID", data.execId_);
	message->setString("MESSAGE", fillStr(data.message_));
	message->setString("ORDER_NUMBER", fillStr(data.orderNumber_));
	message->setLong("ORDER_TYPE", data.orderType_);
	message->setString("ORIG_TRADER_ID", fillStr(data.origTraderId_));
	message->setString("PREF_MMID", fillStr(data.prefMMID_));
	message->setDouble("PRICE", data.price_);
	message->setLong("QUANTITY", data.quantity_);
	message->setString("REMOTE_ID", fillStr(data.remoteId_));
	message->setString("ROUTE", fillStr(data.route_));
	message->setLong("SHARES_FILLED", data.sharesFilled_);
	message->setDouble("STOP_LIMIT", data.stopLimit_);
	message->setString("SYMBOL", fillStr(data.symbol_));
	message->setString("TIME", fillStr(data.time_));
	message->setLong("TIME_IN_FORCE", data.timeInForce_);
	message->setString("TOKEN", fillStr(data.token_));
	message->setString("TRADER_ID", fillStr(data.traderId_));
	message->setLong("VOLUME_TYPE", data.volumeType_);
	message->setLong(CornerTurnConst::EXECUTIONTYPE, data.execType_);

	OrderHistoryDataProd->send(message);
	delete message;
}


void MsgProducer::sendTimeSalesData(TimeSalesData& data)
{
	MapMessage* message = session->createMapMessage();
	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	message->setInt(CornerTurnConst::JDATE, data.jdate_);
	message->setInt(CornerTurnConst::TIME, data.time_);
	message->setDouble(CornerTurnConst::TIMESTAMP, data.timeStamp_);
	    
    message->setDouble(CornerTurnConst::LASTPRICE, data.price_);
    message->setInt(CornerTurnConst::LASTSIZE, data.size_);
	message->setByte(CornerTurnConst::TSSTATUS, data.TSStatus_);
	message->setByte(CornerTurnConst::TSTYPE, data.TSType_);

	// Tell the producer to send the message
    TimeSalesDataProd->send( message );

	delete message;
}

void MsgProducer::sendTradeTrigger(PurchaseData & data)
{
	MapMessage * message = createPurchaseMsg(data);
	TradeTriggerDataProd->send( message );

	delete message;
}

void MsgProducer::sendOrder(PurchaseData & data)
{
	MapMessage * message = createPurchaseMsg(data);
	CreateOrderDataProd->send( message );

	delete message;
}

MapMessage * MsgProducer::createPurchaseMsg(PurchaseData & data)
{
	MapMessage* message = session->createMapMessage();

	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	    
	message->setDouble(CornerTurnConst::PRICE, data.price_);
	message->setDouble(CornerTurnConst::STOPPRICE, data.stopPrice_);
	message->setLong(CornerTurnConst::SIZE, data.size_);

	message->setLong(CornerTurnConst::EXECUTIONTYPE, data.executionType_);
	message->setLong(CornerTurnConst::TRADETYPE, data.typeTrade_);
	message->setDouble(CornerTurnConst::STOPLOWERPRICE, data.stopLowerPrice_);
	message->setDouble(CornerTurnConst::STOPUPPERPRICE, data.stopUpperPrice_);
	message->setString("REASON", "TestTrigger");

	return message;
}
void MsgProducer::cancelOrder(PurchaseData & data)
{
	MapMessage * message = session->createMapMessage();

	message->setString(CornerTurnConst::SYMBOL, fillStr(data.symbol_));
	message->setString(CornerTurnConst::ORDERNUMBER, fillStr(data.orderNumber_));

	CreateOrderDataProd->send( message );

	delete message;
}

void MsgProducer::sendOrderStatus(std::string symbol, bool success, std::string msg)
{
	MapMessage * message = session->createMapMessage();

	message->setString(CornerTurnConst::SYMBOL, fillStr(symbol));
	message->setBoolean(CornerTurnConst::SUCCESS, success);
	message->setString(CornerTurnConst::STATUS, fillStr(msg)),

	OrderStatusProd->send( message );

	delete message;
}

void MsgProducer::removeInstance()
{
	if(0 != instance_)
	{
		delete instance_;
		instance_ = 0;
	}
}

MsgProducer::~MsgProducer()
{        
	// Destroy resources.
    try
	{
        if(0 != msgDest)
		{
			delete msgDest;
		}
    }
	catch (CMSException& e) 
	{
		e.printStackTrace(); 
	}
    msgDest = 0;

    try
	{
        if(0 != eventDest)
		{
			delete eventDest;
		}
    }
	catch (CMSException& e) 
	{
		e.printStackTrace(); 
	}
    eventDest = 0;

    // Close open resources.
    try
	{
        if( session != 0 ) 
		{
			session->close();
		}
        if( connection != 0 ) 
		{
			connection->close();
		}
    }
	catch (CMSException& e) 
	{ 
		e.printStackTrace(); 
	}

    // Now Destroy them
    try
	{
        if( session != 0 ) 
		{
			delete session;
		}
    }
	catch (CMSException& e) 
	{ 
		e.printStackTrace(); 
	}
    session = 0;

    try
	{
        if( connection != 0 ) 
		{
			delete connection;
		}
    }
	catch (CMSException& e) 
	{ 
		e.printStackTrace(); 
	}
    connection = 0;
}


std::string MsgProducer::fillStr(const std::string & str)
{
	if(str.empty())
	{
		return "N/A";
	}
	return str;
}
