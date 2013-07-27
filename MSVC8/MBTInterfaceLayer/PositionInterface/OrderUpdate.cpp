#include "OrderUpdate.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "PositionManager.h"
#include "OpenOrderData.h"

OrderUpdate::OrderUpdate(PositionManager * cb)
	: cb_(cb),
	  latch(1),
      doneLatch(999999999)
{
	connection = 0;
	session = 0;
	destination = 0;
	consumer = 0;
	waitMillis = 999999999;
	brokerURI = CornerTurnConfig::instance()->getURI();
    activemq::library::ActiveMQCPP::initializeLibrary();
}

OrderUpdate::~OrderUpdate(void)
{
}
void OrderUpdate::waitUntilReady() 
{
    latch.await();
}

void OrderUpdate::run() 
{
	try 
	{
        // Create a ConnectionFactory
		std::auto_ptr<ConnectionFactory> connectionFactory(
            ConnectionFactory::createCMSConnectionFactory( brokerURI ) );

        // Create a Connection
        connection = connectionFactory->createConnection();
        connection->start();
        connection->setExceptionListener(this);

        // Create a Session
        session = connection->createSession( Session::AUTO_ACKNOWLEDGE );

        // Create the destination (Topic or Queue)
        destination = session->createTopic( "OpenOrderData" );

        // Create a MessageConsumer from the Session to the Topic or Queue
        consumer = session->createConsumer( destination );

        consumer->setMessageListener( this );

        std::cout.flush();
        std::cerr.flush();

        // Indicate we are ready for messages.
        latch.countDown();

        // Wait while asynchronous messages come in.
		while(true)
        doneLatch.await( waitMillis );

    } 
	catch( CMSException& e ) 
	{
        // Indicate we are ready for messages.
        latch.countDown();

        e.printStackTrace();
    }
}

// Called from the consumer since this class is a registered MessageListener.
void OrderUpdate::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			OpenOrderData * data = new OpenOrderData();
			data->eventType_ = dataMessage->getString("EVENT_TYPE");
			data->account_ = dataMessage->getString("ACCOUNT");
			data->customer_ = dataMessage->getString("CUSTOMER");
			data->acknowledged_ = dataMessage->getBoolean("ACKNOWLEDGED");
			data->buySell_ = dataMessage->getString("BUY_SELL");
			data->currentEvent_ = dataMessage->getString("CURRENT_EVENT");
			data->date_ = dataMessage->getString("DATE");
			data->orderNumber_ = dataMessage->getString("ORDER_NUMBER");
			data->orderType_ = dataMessage->getLong("ORDER_TYPE");
			data->prefMMID_ = dataMessage->getString("PREF_MMID");
			data->price_ = dataMessage->getDouble("PRICE");
			data->quantity_ = dataMessage->getLong("QUANTITY");
			data->replaceable_ = dataMessage->getBoolean("REPLACEABLE");
			data->route_ = dataMessage->getString("ROUTE");
			data->sharesFilled_ = dataMessage->getLong("SHARES_FILLED");
			data->stopLimit_ = dataMessage->getDouble("STOP_LIMIT");
			data->symbol_ = dataMessage->getString(CornerTurnConst::SYMBOL);
			data->time_ = dataMessage->getString("TIME");
			data->timeInForce_ = dataMessage->getLong("TIME_IN_FORCE");
			data->token_ = dataMessage->getString("TOKEN");
			data->traderId_ = dataMessage->getString("TRADER_ID");
			data->trailingOffset_ = dataMessage->getDouble("TRAILING_OFFSET");
			data->volumeType_ = dataMessage->getLong("VOLUME_TYPE");

			cb_->orderUpdate(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void OrderUpdate::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
