#ifndef CancelOrderInterface_h
#define CancelOrderInterface_h

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

struct PurchaseData;

class CancelOrderInterface
{
public:
	virtual void cancelOrder(const std::string & symbol, const std::string & orderNumber) = 0;

};

#endif
