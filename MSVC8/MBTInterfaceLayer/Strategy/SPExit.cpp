// SPExit.cpp: implementation of the SPExit class.
//
//////////////////////////////////////////////////////////////////////

#include "SPExit.h"
#include "Hilbert.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SPExit::SPExit()
: ExitStrategy("Signal Exit")
{

}

SPExit::~SPExit()
{

}

bool SPExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	Phase phaseVal = getPhase(symbol);
	if(phaseVal == PhaseOne ||
	   phaseVal == PhaseTwo)
	{
		return true;
	}
	return false;
}

bool SPExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	Phase phaseVal = getPhase(symbol);
	if(phaseVal == PhaseThree  ||
	   phaseVal == PhaseFour)
	{
		return true;
	}
	return false;
}


