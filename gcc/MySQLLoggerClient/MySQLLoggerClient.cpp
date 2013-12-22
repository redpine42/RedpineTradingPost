// MySQLLoggerClient.cpp : Defines the entry point for the console application.
//

#include "DataStore.h"
#include "CandleDataConsumer.h"
#include "L1DataConsumer.h"
#include "L2DataConsumer.h"
#include "TimeSalesDataConsumer.h"

#include "TimeSalesDataManipulation.h"
#include "L1DataManipulation.h"
#include "L2DataManipulation.h"
#include "CandleDataManipulation.h"

int main(int argc, char* argv[])
{
	DataStore dataStore;
	DataStore l2DataStore;
	DataStore tsdataStore;
	DataStore candleDataStore;
	CandleDataConsumer candleDataConsumer(&candleDataStore);
	L1DataConsumer l1DataConsumer(&dataStore);
	L2DataConsumer l2DataConsumer(&l2DataStore);
	TimeSalesDataConsumer timeSalesDataConsumer(&tsdataStore);

    Thread candleDataConsumerThread( &candleDataConsumer );
    candleDataConsumerThread.start();

    Thread l1DataConsumerThread( &l1DataConsumer );
    l1DataConsumerThread.start();

    Thread l2DataConsumerThread( &l2DataConsumer );
    l2DataConsumerThread.start();

    Thread timeSalesDataConsumerThread( &timeSalesDataConsumer );
    timeSalesDataConsumerThread.start();
	candleDataConsumer.waitUntilReady();
	l1DataConsumer.waitUntilReady();
	l2DataConsumer.waitUntilReady();
	timeSalesDataConsumer.waitUntilReady();

	candleDataConsumerThread.run();
	l1DataConsumerThread.run();
	l2DataConsumerThread.run();
	timeSalesDataConsumerThread.join();

	return 0;
}
