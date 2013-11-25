#include "stdafx.h"

#include <iostream>
#include "TradeManager.h"
#include "MBQuotes_i.h"
#include "QuotesManager.h"
#include "OrderManager.h"
#include "AccountManager.h"
#include "CandleManager.h"
#include "ComSink.h"
#include "COrderSink.h"
#include "CHistSink.h"
#include "TimeZone.h"
#include "MsgProducer.h"

#include <time.h>
#include "Time.h"

TradeManager * TradeManager::instance_ = 0;

TradeManager * TradeManager::instance()
{
    if(0 == instance_)
    {
        instance_ = new TradeManager();
    }
    return instance_;
}

void TradeManager::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

TradeManager::TradeManager()
{
    // COM stuff setup
    IMbtQuotesPtr m_pQuotes;

	HRESULT hResult;
	bOLEinited_ = false;

	// The following hack simply allows the use of the string table:
	HINSTANCE hInstance = (HINSTANCE)0x400000;
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	pModuleState->m_hCurrentInstanceHandle = hInstance;
	pModuleState->m_hCurrentResourceHandle = hInstance;
	if( FAILED(hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)) )
	{
		AfxMessageBox( "Could not CoInitializeEx !", MB_ICONINFORMATION );
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::TRADEMANAGER, "Could not CoInitializeEx !");

		exit(1);
	} 
	else 
	{
		bOLEinited_ = true;
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::TRADEMANAGER, "CoInitializeEx succeeded!");
	}

	if( !AfxOleInit() )
	{
//		AfxMessageBox( IDP_OLE_INIT_FAILED );
		exit(1);
	}

//	CLSID clsid = __uuidof(MbtComMgr);
//	std::cout << &clsid << std::endl ;

	// Standard initialization
	if( FAILED(m_pComMgr.CreateInstance (__uuidof(MbtComMgr)) ))
	{
		AfxMessageBox( "Could not instantiate MbtComMgr !", MB_ICONINFORMATION );
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::TRADEMANAGER, "Could not instantiate MbtComMgr !");
		exit(1);
	}
	else
	{
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::TRADEMANAGER, "MbtComMgr instantiation successful!");
	}


	m_pComSink = new CComSink(m_pComMgr, 0);

	// Do our login
	long lHostId = 1356;
	_bstr_t bstrHostVersion = "0";
	_bstr_t bstrUserName = "";
	_bstr_t bstrPassword = "";
	if( !m_pComMgr->DoLogin( lHostId, bstrUserName, bstrPassword, bstrHostVersion ) )
	{
		AfxMessageBox( "DoLogin() was interrupted !", MB_ICONINFORMATION );
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::TRADEMANAGER, "DoLogin() was interrupted !");
		exit(1);

	}
	else
	{
		// Just for fun...
		CString sMsg;
		CString sUserName =( LPCTSTR )m_pComMgr->UserName;
		long lHostId = m_pComMgr->HostId;
		long lCustomerType = m_pComMgr->CustomerType;
		sMsg.Format( "#### UID: %s HostID: %d, CustomerType: %d",
			sUserName, lHostId, lCustomerType );
		TRACE( sMsg );
		std::string msg = sMsg;
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::TRADEMANAGER, msg);
	}

	// Hide the splash so we can see while debugging
	HWND hWndSplash = ::FindWindow( NULL, "MbtNavSplash" );
	if( hWndSplash )
		::ShowWindow( hWndSplash, SW_HIDE );


	// Instantiate the sink object
	m_pSink = new COrderSink();
	ASSERT( NULL != m_pSink );

	// Get IUnknown interface for [out] event sink object
	LPUNKNOWN pUnk = m_pSink->GetIDispatch(FALSE);
	ASSERT( NULL != pUnk );

    // Fetch our pointer to the Order Client
    m_pOrders = m_pComMgr->OrderClient;


    // Spin a message loop so the OrderClient object can complete its login
	MSG msg;
	int iMaxWait = 200000000;  // Timeout for login
	DWORD dwStart = GetTickCount();

	bool needToLogToOrderClient = true;
	enumConnectionState cs0 = this->m_pComMgr->GetCurrentHealth(siQuotes);
	enumConnectionState cs1 = this->m_pComMgr->GetCurrentHealth(siPerms);
	enumConnectionState cs2 = this->m_pComMgr->GetCurrentHealth(siOrders);

    m_pQuotes = m_pComMgr->Quotes;

	// only 12 quotes.  Watch list has to contain trade list
    quotes_ = new MBQuotes_i(m_pQuotes);

	if (needToLogToOrderClient) 
	{
		printf("Waiting %dms for OrderClient to finish loading accounts ", iMaxWait);
	
		if (!m_pOrders->GotInitialLogonSucceed() ) 
		{
			while( GetMessage( &msg, NULL, 0, 0 ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );

				if( GetTickCount() > dwStart + iMaxWait )
				{
					AfxMessageBox( "Could not Connect to Order Client !", MB_ICONINFORMATION );
				    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::TRADEMANAGER, "Could not Connect to Order Client !");
//					exit(1);
				}
				if (m_pComSink->isLoggedIn()) 
				{
					DWORD dwEnd = GetTickCount();
					printf("\nAccounts loaded in %.4f seconds\n", (double(dwEnd) - double(dwStart)) / 1000);
					break;
				}
				printf(".");
			}
		}
	}

    accountManager_ = AccountManager::createInstance(m_pOrders);
    orderManager_ = OrderManager::createInstance(m_pOrders);
    
	// Wire our sink into ComMgr - this is to receive OrderClient events to stick
	// into the first (large) RichEdit
	ASSERT( NULL != m_pComMgr );
	if( NULL == m_pComMgr || !AfxConnectionAdvise(
		m_pOrders,
		__uuidof(_IMbtOrderClientEvents), pUnk, FALSE, &m_dwCookie)
		)
	{
		AfxMessageBox("WARNING: Failed to advise MbtComMgr events");
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::TRADEMANAGER, "Failed to advise MbtComMgr events!");
	}

/*	// Get the positions data
	m_pPositions = m_pOrders->Positions;

    long val = m_pPositions->Count;
	for(int i = 0; i < val; ++i)
	{
		IMbtPosition * position = m_pPositions->Item[i];
		long quantity = 0;
		double price = 0.0;
		CString sSymbol = (LPCTSTR)position->Symbol;
		std::string symbol = sSymbol;
		
		quantity = position->AggregatePosition;
		if(quantity != 0)
		{
			std::string orderNum;
			double closePrice = 0.0;
			long time = 0;
			std::string date;

			IMbtOpenOrder * order = m_pOrders->OpenOrders->FindMostRecentByAcctSymbol(m_pDefaultAccount, symbol.c_str());
			if(0 != order)
			{
				orderNum = order->OrderNumber;
				closePrice = order->Price;
				time = TimeZone::instance()->getSecondsGMT(order->UTCDateTime);
				date = TimeZone::instance()->getDateStr(TimeZone::instance()->getJDate(order->UTCDateTime));
			}

			price = position->IntradayPrice;
			if(price == 0.0)
			{
				price = position->OvernightPrice;
			}
			PositionMonitorManager::instance()->recreatePosition(symbol, quantity, price, orderNum, closePrice,date, time, "Restart - Reload Postition");
		}
	}
*/
	CandleManager::createInstance(m_pComMgr);
}

TradeManager::~TradeManager()
{
	// UNwire our ComMgr sink
	ASSERT( NULL != m_pSink );
	LPUNKNOWN m_pUnk = m_pSink->GetIDispatch(FALSE);
//	LPUNKNOWN m_phUnk = m_pHistSink->GetIDispatch(FALSE);
	AfxConnectionUnadvise(m_pOrders, __uuidof(_IMbtOrderClientEvents), m_pUnk, FALSE, m_dwCookie);
	if( NULL != m_pSink )
	{
		delete m_pSink; // *** THE SINK DTOR MUST BE PUBLIC OR COMPILER WILL COMPLAIN ***
		m_pSink = NULL;
	}

    delete quotes_;
    OrderManager::removeInstance();
    AccountManager::removeInstance();
}

void TradeManager::reconnect()
{
	m_pComMgr->ReconnectPerms();
}

