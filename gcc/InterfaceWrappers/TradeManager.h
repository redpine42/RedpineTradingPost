#ifndef TradeManager_h
#define TradeManager_h

class MBQuotes_i;
class OrderManager;
class AccountManager;
class CComSink;
class COrderSink;
class CHistSink;

class IHistMgr;
class IPositions;
class MBQuotes_i;
class IComMgr;
class IOrderClient;

#include <map>


class TradeManager
{
public:
    static TradeManager * instance();
    static void removeInstance();

	void reconnect();

private:
    TradeManager();
    ~TradeManager();
    static TradeManager * instance_;
	IOrderClient* m_pOrders;
	IHistMgr * m_pHistMgr;
	IPositions * m_pPositions;
    MBQuotes_i * quotes_;
    IComMgr * m_pComMgr;

    OrderManager * orderManager_;
    AccountManager * accountManager_;

	// TODO LPUNKNOWN pUnk;

	CComSink*  m_pComSink;
	COrderSink* m_pSink;
	CHistSink * m_pHistSink;
	double m_dwCookie;
	double m_dwhCookie;

	bool bOLEinited_;
};

#endif

