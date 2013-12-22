#include "MessageLogger.h"
#include "CornerTurnConfig.h"
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include "TimeWrapper.h"

MessageLogger::MessageLogger(void)
{
    // Display operating system-style date and time. 
	std::string dateTimeStr = TimeWrapper::instance()->getLocalISODateTime();

	dateTimeStr.replace(dateTimeStr.begin(),dateTimeStr.end(),',', '.');
	std::string fileName = CornerTurnConfig::instance()->getLogPath();
	fileName += "\\logs\\";
	fileName += dateTimeStr + ".log";
	
	debugLog_.open(fileName.c_str());
}

MessageLogger::~MessageLogger(void)
{
}

void MessageLogger::logMsgCB(const CornerTurnConst::MessageType msgType, const std::string & source, const std::string messageText)
{
	std::string msgTypeStr("None");
	switch (msgType)
	{
	case CornerTurnConst::Info:
		msgTypeStr = "INFO";
		break;
	case CornerTurnConst::Alert:
		msgTypeStr = "ALERT";
		break;
	case CornerTurnConst::Debug:
		msgTypeStr = "DEBUG";
		break;
	case CornerTurnConst::Error:
		msgTypeStr = "ERROR";
		break;
	case CornerTurnConst::Fatal_Error:
		msgTypeStr = "FATAL ERROR";
		break;
	};

	std::string dateTimeStr;

	dateTimeStr = TimeWrapper::instance()->getLocalDateTime();

	debugLog_ << "[" << dateTimeStr << "] ";
	debugLog_ << "Type: " << msgTypeStr << ", Source: " << source << " \"" << messageText << "\"" << std::endl;
}
