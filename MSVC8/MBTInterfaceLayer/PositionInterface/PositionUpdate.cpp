#include "PositionUpdate.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "PositionManager.h"
#include "PositionData.h"

PositionUpdate::PositionUpdate(PositionManager * cb)
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
PositionUpdate::~PositionUpdate(void)
{
}
void PositionUpdate::waitUntilReady() 
{
    latch.await();
}

void PositionUpdate::run() 
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
        destination = session->createTopic( "PositionData" );

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
void PositionUpdate::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			PositionData * data = new PositionData();
			data->aggregatePosition_ = dataMessage->getLong("AGGREGATE_POSITION");
			data->closableShares_ = dataMessage->getLong("CLOSABLE_SHARES");
			data->commission_ = dataMessage->getDouble("COMMISSION");
			data->intradayPosition_ = dataMessage->getLong("INTRADAY_POSITION");
			data->intradayPrice_ = dataMessage->getDouble("INTRADAY_PRICE");
			data->MMRPct_ = dataMessage->getDouble("MMR_PCT");
			data->MMRUsed_ = dataMessage->getDouble("MMR_USED");
			data->overnightPosition_ = dataMessage->getLong("OVERNIGHT_POSITION");
			data->overnightPrice_ = dataMessage->getDouble("OVERNIGHT_PRICE");
			data->pendingBuyShares_ = dataMessage->getLong("PENDING_BUY_SHARES");
			data->pendingSellShares_ = dataMessage->getLong("PENDING_SELL_SHARES");
			data->realizedPNL_ = dataMessage->getDouble("REALIZED_PNL");
			data->symbol_ = dataMessage->getString(CornerTurnConst::SYMBOL);	
			data->eventType_ = dataMessage->getString("EVENT_TYPE");
			data->account_ = dataMessage->getString("ACCOUNT");
			data->customer_ = dataMessage->getString("CUSTOMER");

			cb_->positionUpdate(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void PositionUpdate::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
