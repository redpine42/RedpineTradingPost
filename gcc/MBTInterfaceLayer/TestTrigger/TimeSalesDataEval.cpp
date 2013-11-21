#include "TimeSalesDataEval.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "TimeSalesData.h"

#include "Trigger.h"

TimeSalesDataEval::TimeSalesDataEval(Trigger * cb)
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

TimeSalesDataEval::~TimeSalesDataEval(void)
{
}

void TimeSalesDataEval::waitUntilReady() 
{
    latch.await();
}

void TimeSalesDataEval::run() 
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
        destination = session->createTopic( "TimeSalesData" );

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
void TimeSalesDataEval::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			TimeSalesData *data= new TimeSalesData(dataMessage->getString(CornerTurnConst::SYMBOL),
								dataMessage->getInt(CornerTurnConst::LASTSIZE),
								dataMessage->getDouble(CornerTurnConst::LASTPRICE),
								dataMessage->getInt(CornerTurnConst::TIME),
								dataMessage->getInt(CornerTurnConst::JDATE),
								0,
								dataMessage->getDouble(CornerTurnConst::TIMESTAMP),
								(DataEnums::TickStatus)dataMessage->getByte(CornerTurnConst::TSSTATUS),
								(DataEnums::TickType)dataMessage->getByte(CornerTurnConst::TSTYPE));
			cb_->evalData(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void TimeSalesDataEval::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
