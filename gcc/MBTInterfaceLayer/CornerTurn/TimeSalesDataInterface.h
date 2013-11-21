#ifndef TimeSalesDataInterface_h
#define TimeSalesDataInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif
struct TimeSalesData;

class TimeSalesDataInterface
{
public:
	virtual void logTimeSalesDataCB(const TimeSalesData* data)=0;

};

#endif
