#ifndef DataEnums_h
#define DataEnums_h

namespace DataEnums
{

enum OrderSide
{
	BID = 1,
	ASK = 2
};

enum TickType
{
	TRADE_TICK,
	BID_TICK,
	ASK_TICK
};

enum TickStatus
{
	NORMAL,
	FILTERED,
	OUTOFSEQ,
	DELETED
};

enum PositionStatus
{
    NoPosition,
	OpenOrderWaiting,
	OpenOrderPartialFill,
    OpenFilled,
    CloseOrderWaiting,
	CloseOrderPartialFill,
    CloseFilled,
    Canceled,
	Rejected
};

};
#endif
