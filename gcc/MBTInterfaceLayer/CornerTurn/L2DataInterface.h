#ifndef L2DataInterface_h
#define L2DataInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif
struct L2Data;

class L2DataInterface
{
public:
	virtual void logL2DataCB(const L2Data* data)=0;

};

#endif