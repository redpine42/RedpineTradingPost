#ifndef CandleDataInterface_h
#define CandleDataInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif
struct CandleData;

class CandleDataInterface
{
public:
	virtual void logCandleDataCB(const CandleData* data)=0;

};

#endif

