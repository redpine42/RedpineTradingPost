#include "TradeTrigger.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "PositionManager.h"
#include "PurchaseData.h"

TradeTrigger::TradeTrigger(PositionManager * cb)
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

TradeTrigger::~TradeTrigger(void)
{
}
void TradeTrigger::waitUntilReady() 
{
    latch.await();
}

void TradeTrigger::run() 
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
        destination = session->createTopic( "TradeTriggerData" );

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
void TradeTrigger::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			PurchaseData * data = new PurchaseData();
			data->symbol_ = dataMessage->getString(CornerTurnConst::SYMBOL);
	    
			data->price_ = dataMessage->getDouble(CornerTurnConst::PRICE);
			data->stopPrice_ = dataMessage->getDouble(CornerTurnConst::STOPPRICE);
			data->size_ = dataMessage->getLong(CornerTurnConst::SIZE);

			data->executionType_ = (PurchaseData::ExecutionType)dataMessage->getLong(CornerTurnConst::EXECUTIONTYPE);
			data->typeTrade_ = (PurchaseData::TradeType)dataMessage->getLong(CornerTurnConst::TRADETYPE);
			data->stopLowerPrice_ = dataMessage->getDouble(CornerTurnConst::STOPLOWERPRICE);
			data->stopUpperPrice_ = dataMessage->getDouble(CornerTurnConst::STOPUPPERPRICE);
			data->reason_ = dataMessage->getString("REASON");

			cb_->purchaseUpdate(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void TradeTrigger::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
