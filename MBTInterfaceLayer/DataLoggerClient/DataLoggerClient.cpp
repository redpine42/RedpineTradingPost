// DataLoggerClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MessageLogger.h"
#include "MsgConsumer.h"


BOOL WINAPI ConsoleHandler(DWORD CEvent);

int _tmain(int argc, _TCHAR* argv[])
{
if (SetConsoleCtrlHandler(
    (PHANDLER_ROUTINE)ConsoleHandler,TRUE)==FALSE)
{
    // unable to install handler... 

    // display message to the user

    printf("Unable to install handler!\n");
    return -1;
}
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

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	return TRUE;
}