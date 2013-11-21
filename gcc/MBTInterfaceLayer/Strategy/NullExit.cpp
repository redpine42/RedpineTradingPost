// NullExit.cpp: implementation of the NullExit class.
//
//////////////////////////////////////////////////////////////////////

#include "NullExit.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NullExit::NullExit(long startTime, long endTime)
	: ExitStrategy("No Exit", startTime, endTime)
{

}

NullExit::~NullExit()
{

}

bool NullExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	return false;
}

bool NullExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	return false;
}

void NullExit::reset()
{
}

