#ifndef OrderManager_h
#define OrderManager_h


#ifndef stdafx_h
#include "stdafx.h"
#define stdafx_h
#endif

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

class OrderManager
{
public:
    static OrderManager * createInstance(IMbtOrderClientPtr m_pOrders);
	static OrderManager * instance();
    static void removeInstance();

    void makeOrder(const PurchaseData * data);
    void closeOut();

	void cancelOrder(const std::string & symbol, const std::string & orderNumber);
	bool checkOrderServer();

	IMbtOrderClientPtr orderClient(){return orders_;}

private:

	static OrderManager * instance_;
    ~OrderManager();
    OrderManager(IMbtOrderClientPtr m_pOrders);
    IMbtOrderClientPtr orders_;

    typedef std::map<std::string, IMbtOpenOrderPtr, std::less<std::string> > OrderMap;
    typedef OrderMap::iterator OrderMapIter;

    OrderMap openOrders_;
};

#endif

