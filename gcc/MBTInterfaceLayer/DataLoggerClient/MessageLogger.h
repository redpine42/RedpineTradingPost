#pragma once

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

#ifndef MsgInterface_h
#include "MsgInterface.h"
#endif

class MessageLogger : public MsgInterface
{
public:
	MessageLogger(void);
	~MessageLogger(void);

	void logMsgCB(const CornerTurnConst::MessageType msgType, const std::string & source, const std::string messageText);

private:
	std::ofstream debugLog_;

	void getLocalTime(std::string & date, std::string & time, std::string & ms);


};
