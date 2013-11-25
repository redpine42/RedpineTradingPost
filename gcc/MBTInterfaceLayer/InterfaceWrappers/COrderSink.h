/***********************************************************
 By using this material you agree to comply with the terms
 governing the MBTI systems and with the MBTI Site Terms and
 Conditions available for view at http://www.mbtrading.com/
 Copyright 2003 MB Trading, Inc. ALL RIGHTS RESERVED.
************************************************************/

#if !defined(AFX_COrderSink_H__FD34B862_C2F2_479F_B1A0_1D59AEC4F293__INCLUDED_)
#define AFX_COrderSink_H__FD34B862_C2F2_479F_B1A0_1D59AEC4F293__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// COrderSink command target


class COrderSink : public CCmdTarget
{
	DECLARE_DYNAMIC(COrderSink)
	COrderSink(); // protected constructor used by dynamic creation
	virtual ~COrderSink(); // moved to here from protected - Phil

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderSink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bLogonSucceeded;

	// Generated message map functions
	//{{AFX_MSG(COrderSink)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COrderSink)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	// These event handlers:...
	void OnConnect(long lErrorCode) { Log_ErrorCode("OnConnect", lErrorCode); }
	void OnClose (long lErrorCode) { Log_ErrorCode("OnClose", lErrorCode); }
//	void OnLogonSucceed () { Log_ErrorCode("OnLogonSucceed", 0); }
	void OnSubmit (IMbtOpenOrder* pOrd) { Log_pOrd("OnSubmit", pOrd); }
	void OnAcknowledge(IMbtOpenOrder* pOrd) { Log_pOrd("OnAcknowledge", pOrd); }
	void OnExecute (IMbtOpenOrder* pOrd) { Log_pOrd("OnExecute", pOrd); }
	void OnRemove (IMbtOpenOrder* pOrd) { Log_pOrd("OnRemove", pOrd); }
	void OnHistoryAdded(IMbtOrderHistory* pHist) { Log_pHist("OnHistoryAdded", pHist); }
	void OnPositionAdded (IMbtPosition* pPos) { Log_pPos("OnPositionAdded", pPos); }
	void OnPositionUpdated(IMbtPosition* pPos) { Log_pPos("OnPositionUpdated", pPos); }
	void OnBalanceUpdate (IMbtAccount* pAcct) { Log_pAcct("OnBalanceUpdate", pAcct); }
	void OnDefaultAccountChanged(IMbtAccount* pAcct) { Log_pAcct("OnDefaultAccountChanged", pAcct); }
	void OnAccountLoading (IMbtAccount* pAcct) { Log_pAcct("OnAccountLoading", pAcct); }
	void OnAccountLoaded (IMbtAccount* pAcct) { Log_pAcct("OnAccountLoaded", pAcct); }
	void OnCancelPlaced (IMbtOpenOrder* pOrd) { Log_pOrd("OnCancelPlaced", pOrd); }
	void OnReplacePlaced (IMbtOpenOrder* pOrd) { Log_pOrd("OnReplacePlaced", pOrd); }
	void OnReplaceRejected (IMbtOpenOrder* pOrd) { Log_pOrd("OnReplaceRejected", pOrd); }
	void OnCancelRejected (IMbtOpenOrder* pOrd) { Log_pOrd("OnCancelRejected", pOrd); }
	void OnAccountUnavailable (IMbtAccount* pAcct) { Log_pAcct("OnAccountUnavailable", pAcct); }

	// ...call THESE:
	void Log_pOrd(LPCTSTR sEventName, IMbtOpenOrder* pOrd);
	void Log_pPos(LPCTSTR sEventName, IMbtPosition* pPos);
	void Log_pAcct(LPCTSTR sEventName, IMbtAccount* pAcct);
	void Log_pHist(LPCTSTR sEventName, IMbtOrderHistory* pHist);
	void Log_ErrorCode(LPCTSTR sEventname, long lErrorCode);


	/*
	OnLogonSucceed occurs when user has been authenticated and has successfully
	logged in. I'm capturing this only to insert 'NEW' vs 'old' in the TRACEs and
	in the RichEdit (distinguishes between existing and new events).
	****************************************************************************/
	void COrderSink::OnLogonSucceed()
	{
		m_bLogonSucceeded = TRUE;
		TraceItOut("----  OnLogonSucceed ------------------------------------------\n");
	}
	inline CString NewOrOld(BOOL m_bLogonSucceeded)
	{
		return (m_bLogonSucceeded) ? "NEW" : "old";
	}
	inline void TraceItOut(CString sOut)
	{
		/* If we haven't yet gotten our OnLogonSucceed event, then cache all
		messages until we do. This smooths out the RichEdit display -- chunks
		all old messages into it in one fell swoop.
		***********************************************************************/
		std::string data = sOut;
//		DataLogger::instance()->recordDebug(data);
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COrderSink_H__FD34B862_C2F2_479F_B1A0_1D59AEC4F293__INCLUDED_)
