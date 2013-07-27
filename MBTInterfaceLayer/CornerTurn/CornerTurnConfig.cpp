#include "CornerTurnConfig.h"

CornerTurnConfig * CornerTurnConfig::instance_ = 0;

CornerTurnConfig * CornerTurnConfig::instance()
{
	if(0 == instance_)
	{
		instance_ = new CornerTurnConfig();
	}
	return instance_;
}

CornerTurnConfig::CornerTurnConfig()
{
	brokerURI_ = "failover:(tcp://127.0.0.1:61616)";
	logPath_ = "C:\\TradeLogs";
}
