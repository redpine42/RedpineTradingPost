#ifndef CreateOrderInterface_h
#define CreateOrderInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

struct PurchaseData;

class CreateOrderInterface
{
public:
	virtual void createOrder(const PurchaseData * data) = 0;

};

#endif
