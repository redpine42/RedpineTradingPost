#ifndef L1DataInterface_h
#define L1DataInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif
struct L1Data;

class L1DataInterface
{
public:
	virtual void logL1DataCB(const L1Data* data)=0;

};

#endif

