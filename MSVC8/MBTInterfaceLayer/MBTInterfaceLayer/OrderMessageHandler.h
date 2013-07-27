#pragma once

struct PurchaseData;

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

#ifndef CornerTurnConst_h
#include "CornerTurnConst.h"
#endif

#ifndef CreateOrderInterface_h
#include "CreateOrderInterface.h"
#endif

#ifndef CancelOrderInterface_h
#include "CancelOrderInterface.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

class OrderMessageHandler : public CreateOrderInterface, public CancelOrderInterface
{
public:
	OrderMessageHandler(void);
	~OrderMessageHandler(void);

	void createOrder(const PurchaseData * data);
	void cancelOrder(const std::string & symbol, const std::string & orderNumber);

private:
};
