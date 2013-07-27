// NullExit.h: interface for the NullExit class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NullExit_h
#define NullExit_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExitStrategy.h"

class NullExit : public ExitStrategy  
{
public:
	NullExit(long startTime, long endTime);
	virtual ~NullExit();

	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset();


};

#endif

