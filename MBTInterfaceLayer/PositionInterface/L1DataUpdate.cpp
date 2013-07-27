#include "L1DataUpdate.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "PositionManager.h"
#include "L1Data.h"

L1DataUpdate::L1DataUpdate(PositionManager * cb)
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

L1DataUpdate::~L1DataUpdate(void)
{
}
void L1DataUpdate::waitUntilReady() 
{
    latch.await();
}

void L1DataUpdate::run() 
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
        destination = session->createTopic( "L1Data" );

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
void L1DataUpdate::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			L1Data * data= new L1Data(dataMessage->getString(CornerTurnConst::SYMBOL),
						dataMessage->getInt(CornerTurnConst::LASTSIZE),
						dataMessage->getDouble(CornerTurnConst::LASTPRICE),
						dataMessage->getInt(CornerTurnConst::TIME),
						dataMessage->getInt(CornerTurnConst::JDATE),
						0,
						dataMessage->getDouble(CornerTurnConst::TIMESTAMP),
						dataMessage->getDouble(CornerTurnConst::BID),
						dataMessage->getDouble(CornerTurnConst::ASK),
						dataMessage->getInt(CornerTurnConst::BIDSIZE),
						dataMessage->getInt(CornerTurnConst::ASKSIZE),
						dataMessage->getBoolean(CornerTurnConst::UPTICK),
						dataMessage->getInt(CornerTurnConst::VOLUME),
						dataMessage->getBoolean(CornerTurnConst::SHORTABLE));

			cb_->l1DataUpdate(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void L1DataUpdate::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
