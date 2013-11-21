#ifndef MsgInterface_h
#define MsgInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

class MsgInterface
{
public:
	virtual void logMsgCB(const CornerTurnConst::MessageType msgType, const std::string & source, const std::string messageText)=0;

};

#endif

