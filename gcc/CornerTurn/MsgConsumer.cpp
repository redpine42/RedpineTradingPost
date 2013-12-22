#include "MsgConsumer.h"
#include "MsgInterface.h"
#include "CornerTurnConfig.h"
#include <stdio.h>

MsgConsumer::MsgConsumer(MsgInterface * cb)
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

MsgConsumer::~MsgConsumer(void)
{
}

void MsgConsumer::waitUntilReady() 
{
    latch.await();
}

void MsgConsumer::run() 
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
        destination = session->createTopic( "MessageData" );

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
void MsgConsumer::onMessage( const Message* message )
{
    try
    {
        const MapMessage* textMessage =
            dynamic_cast< const MapMessage* >( message );

        if( textMessage != NULL ) 
		{
			int msgType = textMessage->getInt(CornerTurnConst::MESSAGETYPE);
			std::string source = textMessage->getString(CornerTurnConst::SOURCE);
			std::string text = textMessage->getString(CornerTurnConst::MESSAGETEXT);
			cb_->logMsgCB((CornerTurnConst::MessageType)msgType,source,text);
       }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void MsgConsumer::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
