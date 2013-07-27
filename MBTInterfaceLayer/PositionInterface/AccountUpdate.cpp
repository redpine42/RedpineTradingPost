#include "AccountUpdate.h"
#include "CornerTurnConfig.h"
#include "CornerTurnConst.h"
#include "PositionManager.h"
#include "AccountData.h"

AccountUpdate::AccountUpdate(PositionManager * cb)
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

AccountUpdate::~AccountUpdate(void)
{
}
void AccountUpdate::waitUntilReady() 
{
    latch.await();
}

void AccountUpdate::run() 
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
        destination = session->createTopic( "AccountData" );

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
void AccountUpdate::onMessage( const Message* message )
{
    try
    {
        const MapMessage* dataMessage =
            dynamic_cast< const MapMessage* >( message );

        if( dataMessage != NULL ) 
		{
			AccountData * data = new AccountData();
			data->eventType_ = dataMessage->getString("EVENT_TYPE");
			data->account_ = dataMessage->getString("ACCOUNT");
			data->accountType_ = dataMessage->getLong("ACCOUNT_TYPE");
			data->bank_ = dataMessage->getString("BANK");
			data->baseCurrency_ = dataMessage->getString("BASE_CURRENCY");
			data->branch_ = dataMessage->getString("BRANCH");
			data->cancelsToday_ = dataMessage->getLong("CANCELS_TODAY");
			data->credit_ = dataMessage->getDouble("CREDIT");
			data->currentEquity_ = dataMessage->getDouble("CURRENT_EQUITY");
			data->currentExcess_ = dataMessage->getDouble("CURRENT_EXCESS");
			data->customer_ = dataMessage->getString("CUSTOMER");
			data->dailyRealizedPL_ = dataMessage->getDouble("DAILY_REALIZED_PL");
			data->MMRMultiplier_ = dataMessage->getDouble("MMR_MULTIPLIER");
			data->MMRUsed_ = dataMessage->getDouble("MMR_USED");
			data->morningCash_ = dataMessage->getDouble("MORNING_CASH");
			data->morningEquity_ = dataMessage->getDouble("MORNING_EQUITY");
			data->morningExcess_ = dataMessage->getDouble("MORNING_EXCESS");
			data->overnightExcess_ = dataMessage->getDouble("OVERNIGHT_EXCESS");
			data->permedForCADEquities_ = dataMessage->getBoolean("PERMED_FOR_CAD_EQUITIES");
			data->permedForEquities_ = dataMessage->getBoolean("PERMED_FOR_EQUITIES");
			data->permedForForex_ = dataMessage->getBoolean("PERMED_FOR_FOREX");
			data->permedForFutures_ = dataMessage->getBoolean("PERMED_FOR_FUTURES");
			data->permedForOptions_ = dataMessage->getBoolean("PERMED_FOR_OPTIONS");
			data->routingId_ = dataMessage->getString("ROUTING_ID");
			data->semiDelimited_ = dataMessage->getString("SEMI_DELIMITED");
			data->sharesToday_ = dataMessage->getLong("SHARES_TODAY");
			data->state_ = (AccountData::AccountState)dataMessage->getLong("STATE");
			data->tradesToday_ = dataMessage->getLong("TRADES_TODAY");

			cb_->accountUpdate(data);
      }
    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void AccountUpdate::onException( const CMSException& ex AMQCPP_UNUSED) 
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    ex.printStackTrace();
    exit(1);
}
