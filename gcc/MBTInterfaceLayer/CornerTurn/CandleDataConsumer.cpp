#include "CandleDataConsumer.h"
#include "CandleDataInterface.h"
#include "CornerTurnConfig.h"
#include "CandleData.h"

CandleDataConsumer::CandleDataConsumer(CandleDataInterface * cb)
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

CandleDataConsumer::~CandleDataConsumer(void)
{
}

void CandleDataConsumer::waitUntilReady() 
{
    latch.await();
}

void CandleDataConsumer::run() 
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
        destination = session->createTopic( "CandleData" );

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
void CandleDataConsumer::onMessage( const Message* message )
{
	return;
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			CandleData*  data = new CandleData(dataMessage->getString(CornerTurnConst::SYMBOL),
							dataMessage->getInt(CornerTurnConst::VOLUME),
							dataMessage->getDouble(CornerTurnConst::OPEN),
							dataMessage->getDouble(CornerTurnConst::HIGH),
							dataMessage->getDouble(CornerTurnConst::LOW),
							dataMessage->getDouble(CornerTurnConst::CLOSE),
							dataMessage->getInt(CornerTurnConst::JDATE),
							dataMessage->getInt(CornerTurnConst::TIME),
							(CandleData::CandleTimeType)dataMessage->getByte(CornerTurnConst::CANDLETIMETYPE),
							(CandleData::CandleUpdateType)dataMessage->getByte(CornerTurnConst::CANDLEUPDATETYPE));
			cb_->logCandleDataCB(data);
       }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void CandleDataConsumer::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
