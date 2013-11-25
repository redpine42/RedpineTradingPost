//
//   Copyright (c) 2008 by Shalom Yariv
//
// ComSink.cpp : implementation file
//

#include "stdafx.h" 
#include "ComSink.h"
#include "MsgProducer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MBT_COM_MGR				0

#define ON_HEALTH_UPDATE		0x1
#define ON_ALERT_ADDED			0x2
#define ON_LOGON_SUCCEED		0x3
#define ON_LOGON_DENY			0x4
#define ON_CRITICAL_SHUTDOWN	0x5
#define ON_HOT_KEYS_MODIFIED	0xc
#define ON_ALERTS_REFRESH		0xd
#define ON_SESSION_TOKEN_UPDATED 0xe

/////////////////////////////////////////////////////////////////////////////
// CComSink

IMPLEMENT_DYNAMIC(CComSink, CCmdTarget)

CComSink::CComSink(IMbtComMgrPtr pComMgr, DWORD pSinksThread)
{
	EnableAutomation();

	m_pComMgr = pComMgr;
	m_pSinksThread = pSinksThread;
	if(!AfxConnectionAdvise (m_pComMgr,	__uuidof(IMbtComMgrEvents), 
		this->GetIDispatch(FALSE), FALSE, &m_dwCookie))
	{
		TRACE("  DEBUG>>>Failed to advise MbtComMgr events\n");
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::COMSINK, "Failed to advise MbtComMgr events!");

	}
	m_permsStatus = csILG; 
	m_quoteStatus = csILG; 
	m_ordersStatus = csILG;
}

CComSink::~CComSink()
{
	if(!AfxConnectionUnadvise(m_pComMgr, __uuidof(IMbtComMgrEvents), 
		this->GetIDispatch(FALSE), FALSE, m_dwCookie))
	{
		TRACE("  DEBUG>>>Failed to UNadvise MbtComMgr events\n");
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::COMSINK, "Failed to UNadvise MbtComMgr events!");
	}
}

BEGIN_DISPATCH_MAP(CComSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CComSink)
	DISP_FUNCTION_ID(CComSink, "OnHealthUpdate", 1, OnHealthUpdate, VT_EMPTY, VTS_I4 VTS_I4)
	DISP_FUNCTION_ID(CComSink, "OnAlertAdded", 2, OnAlertAdded, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(CComSink, "OnLogonSucceed", 3, OnLogonSucceed, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CComSink, "OnLogonDeny", 4, OnLogonDeny, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CComSink, "OnCriticalShutdown", 5, OnCriticalShutdown, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CComSink, "OnHotKeysModified", 12, OnHotKeysModified, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CComSink, "OnAlertsRefresh", 13, OnAlertsRefresh, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CComSink, "OnSessionTokenUpdate", 15, OnAlertsRefresh, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/*
 The DISPIDs entered above can be found in the typedefs for MbtCom.DLL.

dispinterface IMbtComMgrEvents {
    properties:
    methods:
        [id(0x00000001), helpstring("Periodically occurs to report status of various server connections")]
        void OnHealthUpdate([in] enumServerIndex index, enumConnectionState state);
        [id(0x00000002), helpstring("Occurs when a new event has been added to Alert event log")]
        void OnAlertAdded([in] IMbtAlert* pAlert);
        [id(0x00000003), helpstring("Occurs when successful login to server has taken place.")]
        void OnLogonSucceed();
        [id(0x00000004), helpstring("Occurs when login to server has failed.")]
        void OnLogonDeny([in] BSTR bstrReason);
        [id(0x00000005), helpstring("Occurs when a catastrophic event has taken place; and order server communications have been permanently severed.")]
        void OnCriticalShutdown();
        [id(0x0000000c), helpstring("Occurs when user has modified order placement hotkeys via property page")]
        void OnHotKeysModified();
        [id(0x0000000d), helpstring("Periodically occurs after certain reconnection events.")]
        void OnAlertsRefresh();
};
*/

BEGIN_INTERFACE_MAP(CComSink, CCmdTarget)
// the __uuidof should use the dispinterface found in the .tlh file
	INTERFACE_PART(CComSink, __uuidof(IMbtComMgrEvents), Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComSink message handlers

/*
   siQuotes = 0,
    siPerms = 1,
    siOrders = 2,
    siMAX = 3

*/
const char _index[4][20] = {
 "siQuotes", 
  "siPerms", 
  "siOrders",
  "siMAX",
}; 


const char _state[7][20] =
{
"csDisconnected",
"csConnecting",
"csConnected",
"csLoggingIn",
"csLoggedIn",
"csIndeterminate",
"csMAX"
	
	
};// = {};
void CComSink::OnHealthUpdate(enumServerIndex nIndex, enumConnectionState nState) 
{
	char buf[2];
	CString s[2];
	_itoa_s(nIndex+1, buf, 2, 10);
	s[0] = buf;
	_itoa_s(nState+1, buf, 2, 10);
	s[1] = buf;

	switch (nIndex) {
		case siQuotes:
			m_quoteStatus = nState; 
			break;
		case siPerms:
			m_permsStatus = nState;
			break;
		case siOrders: 
			m_ordersStatus = nState;
			break;
		default:
			break;
	}

	std::string result = "Health Update: ";
	result += _index[nIndex];
	result += "...";
	result += _state[nState];
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, result);
}

void CComSink::OnAlertAdded(IMbtAlert* pAlert) 
{
	std::cerr << (char*)pAlert->Message << "\n";
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, (char*)pAlert->Message);
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_ALERT_ADDED, (char*)pAlert->Message);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnLogonSucceed() 
{
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, "Login succeeded");
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_LOGON_SUCCEED);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnLogonDeny(BSTR bstrReason) 
{
	std::string reason = "Login Failed";
	reason += (char*)bstrReason;
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, reason);
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_LOGON_DENY, (char*)bstrReason);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnCriticalShutdown() 
{
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, "Critical Shutdown");
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_CRITICAL_SHUTDOWN);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnHotKeysModified() 
{
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_HOT_KEYS_MODIFIED);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnAlertsRefresh() 
{
//	CMessage* message = new CMessage(MBT_COM_MGR, ON_ALERTS_REFRESH);
//	PostThreadMessage(m_pSinksThread, MBT_Message, NULL, (long)message);
}

void CComSink::OnSessionTokenUpdate(BSTR bstrNewToken, DATE timeNewExpire)
{
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::COMSINK, "Session Token Updated");
}

