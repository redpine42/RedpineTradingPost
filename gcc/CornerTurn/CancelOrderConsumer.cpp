#include "CancelOrderConsumer.h"
#include "CancelOrderInterface.h"
#include "CornerTurnConfig.h"
#include "PurchaseData.h"
#include <iostream>

CancelOrderConsumer::CancelOrderConsumer(CancelOrderInterface * cb)
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

CancelOrderConsumer::~CancelOrderConsumer(void)
{
}

void CancelOrderConsumer::waitUntilReady() 
{
    latch.await();
}

void CancelOrderConsumer::run() 
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
        destination = session->createTopic( "CancelOrder" );

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
void CancelOrderConsumer::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			std::string symbol = dataMessage->getString(CornerTurnConst::SYMBOL);
			std::string orderNumber = dataMessage->getString(CornerTurnConst::ORDERNUMBER);
	    
			cb_->cancelOrder(symbol, orderNumber);
       }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void CancelOrderConsumer::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    std::cerr << "CMS Exception occurred.  Shutting down client." << std::endl;
    ex.printStackTrace();
    exit(1);
}
