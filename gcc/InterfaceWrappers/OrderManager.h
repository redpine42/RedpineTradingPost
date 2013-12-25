#ifndef OrderManager_h
#define OrderManager_h

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

#ifndef IOpenOrder_h
#include "IOpenOrder.h"
#endif

class OrderManager
{
public:
    static OrderManager * createInstance(IOrderClient* orderClient);
	static OrderManager * instance();
    static void removeInstance();

    void makeOrder(const PurchaseData * data);
    void closeOut();

	void cancelOrder(const std::string & symbol, const std::string & orderNumber);
	bool checkOrderServer();

	IOrderClient * orderClient(){return orderClient_;}

private:

	static OrderManager * instance_;
    ~OrderManager();
    OrderManager(IOrderClient * orderClient);
    IOrderClient * orderClient_;

    typedef std::map<std::string, IOpenOrder *, std::less<std::string> > OrderMap;
    typedef OrderMap::iterator OrderMapIter;

    OrderMap openOrders_;
};

#endif

