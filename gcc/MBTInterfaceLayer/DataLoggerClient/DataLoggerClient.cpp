// DataLoggerClient.cpp : Defines the entry point for the console application.
//
#include "MessageLogger.h"
#include "MsgConsumer.h"


int main(int argc AMQCPP_UNUSED, char* argv[] AMQCPP_UNUSED)
{
	MessageLogger msgLogger;
	MsgConsumer msgConsumer(&msgLogger);

    // Start the consumer thread.
    Thread msgConsumerThread( &msgConsumer );
    msgConsumerThread.start();


    // Wait for the consumer to indicate that its ready to go.
    msgConsumer.waitUntilReady();
    msgConsumerThread.join();

	return 0;
}

