
#pragma once

#ifndef _Included_ComSink
#define _Included_ComSink

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComSink.h : header file
//
//#include "Message.h"
//#include "Other.h"

/////////////////////////////////////////////////////////////////////////////
// CComSink command target

class CComSink : public CCmdTarget
{
	DECLARE_DYNAMIC(CComSink)

	CComSink(IMbtComMgrPtr pComMgr, DWORD pSinksThread);  
	virtual ~CComSink();

	BOOL isAlive() { return ((m_pComMgr != NULL) && (m_pComMgr->GetIsConnected())); }

	BOOL isLoggedIn() { return ((m_pComMgr != NULL) && (m_ordersStatus >= csLoggedIn)); }

protected:
	IMbtComMgrPtr m_pComMgr;
	DWORD m_pSinksThread;
	DWORD m_dwCookie;
	  enumConnectionState m_permsStatus; 
	  enumConnectionState m_quoteStatus; 
	  enumConnectionState m_ordersStatus; 

/*
    Copyright (c) 2008 by Shalom Yariv
*/




	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	// Event handlers:
	void OnHealthUpdate(enumServerIndex index, enumConnectionState state);
	void OnAlertAdded(IMbtAlert* pAlert);
	void OnLogonSucceed();
	void OnLogonDeny(BSTR bstrReason);
	void OnCriticalShutdown();
	void OnHotKeysModified();
	void OnAlertsRefresh();
	void OnSessionTokenUpdate(BSTR bstrNewToken, DATE timeNewExpire );
};


#endif 

