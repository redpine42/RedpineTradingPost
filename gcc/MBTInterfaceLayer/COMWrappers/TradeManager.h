#ifndef TradeManager_h
#define TradeManager_h

class MBQuotes_i;
class OrderManager;
class AccountManager;
class CComSink;
class COrderSink;
class CHistSink;

#ifndef map_h
#include <map>
#define map_h
#endif


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
	IMbtOrderClientPtr m_pOrders;
	IMbtHistMgrPtr m_pHistMgr;
	IMbtPositionsPtr m_pPositions;
    MBQuotes_i * quotes_;
    IMbtComMgrPtr m_pComMgr;

    OrderManager * orderManager_;
    AccountManager * accountManager_;

	LPUNKNOWN pUnk;

	CComSink*  m_pComSink;
	COrderSink* m_pSink;
	CHistSink * m_pHistSink;
	DWORD m_dwCookie;
	DWORD m_dwhCookie;

	bool bOLEinited_;
};

#endif

