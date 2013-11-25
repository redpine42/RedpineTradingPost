#include "stdafx.h"
#include "Trigger.h"
#include "L1DataEval.h"

int main(int argc, char* argv[])
{
	std::string symbol("EUR/USD");

	Trigger testT(symbol);
	L1DataEval l1DataEval(&testT);

    Thread l1DataEvalThread( &l1DataEval );
    l1DataEvalThread.start();

	l1DataEval.waitUntilReady();
	l1DataEvalThread.join();

	return 0;
};

