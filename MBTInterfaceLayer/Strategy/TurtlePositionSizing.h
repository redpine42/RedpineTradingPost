// TurtlePositionSizing.h: interface for the TurtlePositionSizing class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TurtlePositionSizing_h
#define TurtlePositionSizing_h

#ifndef QuantityStrategy_h
#include "QuantityStrategy.h"
#endif

class TurtlePositionSizing : public QuantityStrategy  
{
public:
	TurtlePositionSizing();
	~TurtlePositionSizing();

	int buy(const std::string & symbol, const double price);
	int sellShort(const std::string & symbol, const double price);

private:
	int calculateSize(const std::string & symbol, const double price);
};

#endif 

