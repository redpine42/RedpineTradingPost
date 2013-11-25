// MBTInterfaceLayer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TradeManager.h"
#include "QuotesManager.h"
#include "CandleManager.h"
#include "CandleHistMaker.h"
#include "MsgProducer.h"
#include "OrderMessageHandler.h"
#include "CreateOrderConsumer.h"
#include "CancelOrderConsumer.h"

#include <string>
#include <vector>

int _tmain(int argc, _TCHAR* argv[])
{
//	ShowWindow( GetConsoleWindow(), SW_HIDE );
	TradeManager::instance();
	std::vector<std::string> symbols;
	symbols.push_back("AUD/CAD");
	symbols.push_back("AUD/JPY");
	symbols.push_back("AUD/NZD");
	symbols.push_back("AUD/USD");

	symbols.push_back("CAD/CHF");
	symbols.push_back("CAD/JPY");

	symbols.push_back("CHF/JPY");

	symbols.push_back("EUR/AUD");
	symbols.push_back("EUR/CAD");
	symbols.push_back("EUR/CHF");
	symbols.push_back("EUR/GBP");
	symbols.push_back("EUR/JPY");
	symbols.push_back("EUR/USD");

	symbols.push_back("GBP/AUD");
	symbols.push_back("GBP/CAD");
	symbols.push_back("GBP/CHF");
	symbols.push_back("GBP/JPY");
	symbols.push_back("GBP/USD");

	symbols.push_back("NZD/JPY");
	symbols.push_back("NZD/USD");

	symbols.push_back("USD/CAD");
	symbols.push_back("USD/CHF");
	symbols.push_back("USD/JPY");

	while(!QuotesManager::instance()->addSymbols(symbols))
	{
		std::cerr << "Can't set up quotes!!!" << std::endl;
		Sleep(10000);
	}
	CandleManager::instance()->getCandleData(symbols);
//	CandleHistMaker::instance()->getCandleHistory(symbols);

	OrderMessageHandler createOrder;
	OrderMessageHandler cancelOrder;
	CreateOrderConsumer createOrderConsumer(&createOrder);
	CancelOrderConsumer cancelOrderConsumer(&cancelOrder);

    // Start the consumer thread.
    Thread createOrderConsumerThread( &createOrderConsumer );
    createOrderConsumerThread.start();
	createOrderConsumer.waitUntilReady();

    Thread cancelOrderConsumerThread( &cancelOrderConsumer );
    cancelOrderConsumerThread.start();
	cancelOrderConsumer.waitUntilReady();
	cancelOrderConsumerThread.run();
	createOrderConsumerThread.run();


	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	MsgProducer::removeInstance();
	return 0;
}

