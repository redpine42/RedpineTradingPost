#include "StdAfx.h"
#include "MessageLogger.h"
#include "CornerTurnConfig.h"
#include <time.h>
#include <sys/timeb.h>
#include <string>

MessageLogger::MessageLogger(void)
{
    _tzset();

    // Display operating system-style date and time. 
	std::string timeStr;
	std::string dateStr;
	std::string msStr;

	getLocalTime(dateStr,timeStr, msStr);
	size_t pos = timeStr.find(':');
	timeStr.erase(pos,1);
	pos = timeStr.find(':');
	timeStr.erase(pos,1);

	pos = dateStr.find('/');
	dateStr.erase(pos,1);
	pos = dateStr.find('/');
	dateStr.erase(pos,1);

	std::string fileName = CornerTurnConfig::instance()->getLogPath();
	fileName += "\\logs\\";
	fileName += dateStr + timeStr + ".log";
	
	debugLog_.open(fileName.c_str());
}

MessageLogger::~MessageLogger(void)
{
}

void MessageLogger::getLocalTime(std::string & dateStr, std::string & timeStr, std::string & ms)
{
	char tmpbuf[128];
    struct _timeb tstruct;

	_strtime_s( tmpbuf, 128 );
	timeStr = tmpbuf;

    _strdate_s( tmpbuf, 128 );
	dateStr = tmpbuf;

    _ftime_s( &tstruct ); 

	sprintf_s( tmpbuf,"%u", tstruct.millitm );
	ms = tmpbuf;
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
	std::string timeStr;
	std::string dateStr;
	std::string msStr;

	getLocalTime(dateStr,timeStr, msStr);

	debugLog_ << "[" << dateStr << " " << timeStr << "." << msStr << "] ";
	debugLog_ << "Type: " << msgTypeStr << ", Source: " << source << " \"" << messageText << "\"" << std::endl;
}
