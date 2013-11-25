#include "OrderMessageHandler.h"
#include "OrderManager.h"
#include "PurchaseData.h"

OrderMessageHandler::OrderMessageHandler(void)
{
}

OrderMessageHandler::~OrderMessageHandler(void)
{
}

void OrderMessageHandler::createOrder(const PurchaseData * data)
{
	OrderManager::instance()->makeOrder(data);
}

void OrderMessageHandler::cancelOrder(const std::string & symbol, const std::string & orderNumber)
{
	OrderManager::instance()->cancelOrder(symbol, orderNumber);
}

