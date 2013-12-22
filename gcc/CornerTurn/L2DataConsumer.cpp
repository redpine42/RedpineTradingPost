#include "L2DataConsumer.h"
#include "L2DataInterface.h"
#include "CornerTurnConfig.h"
#include "L2Data.h"
#include <stdio.h>

L2DataConsumer::L2DataConsumer(L2DataInterface * cb)
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

L2DataConsumer::~L2DataConsumer(void)
{
}

void L2DataConsumer::waitUntilReady() 
{
    latch.await();
}

void L2DataConsumer::run() 
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
        destination = session->createTopic( "L2Data" );

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
void L2DataConsumer::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			L2Data * data= new L2Data(dataMessage->getString(CornerTurnConst::SYMBOL),
						dataMessage->getString(CornerTurnConst::MMID),
						dataMessage->getString(CornerTurnConst::SOURCE),
						(DataEnums::OrderSide)dataMessage->getByte(CornerTurnConst::MARKETSIDE),
						dataMessage->getDouble(CornerTurnConst::LASTPRICE),
						dataMessage->getInt(CornerTurnConst::LASTSIZE),
						dataMessage->getInt(CornerTurnConst::TIME),
						dataMessage->getInt(CornerTurnConst::JDATE),
						dataMessage->getDouble(CornerTurnConst::TIMESTAMP),
						dataMessage->getBoolean(CornerTurnConst::CLOSED),
						0);
			cb_->logL2DataCB(data);
       }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void L2DataConsumer::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
