// ImprovedExit.h: interface for the ImprovedExit class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ImprovedExit_h
#define ImprovedExit_h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef ExitStrategy_h
#include "ExitStrategy.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

class ImprovedExit : public ExitStrategy  
{
public:
	ImprovedExit(std::string symbol, int atrBars, int timeExit, double mmstp, double ptlim, double stpa, double stpb, double ptga, long startTime, long endTime);
	virtual ~ImprovedExit();


	bool buyToCover(const std::string & symbol, const double openPrice, const double price);
	bool sell(const std::string & symbol, const double openPrice, const double price);

	void reset(){};

private:
	  bool firstTest_;
	  double stopLoss_;
	  double takeProfit_;
	  int ATRBars_;
	  int timeExit_;
	  double mmstp_;
	  double ptlim_;
	  double stpa_;
	  double stpb_;
	  double ptga_;

	  long lastTime_;
	  long seconds_;
	  double precision_;
};

#endif