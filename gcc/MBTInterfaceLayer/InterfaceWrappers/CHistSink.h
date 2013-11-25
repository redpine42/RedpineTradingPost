#ifndef CHistSink_h
#define CHistSink_h

#include "stdafx.h"

class CHistSink : public CCmdTarget
{
	DECLARE_DYNAMIC(CHistSink)

public:
	CHistSink();
	virtual ~CHistSink();


	virtual void OnFinalRelease();
	void  OnDataEvent (
		long lRequestId,
		IDispatch * pHist,
		enum enumHistEventType evt );
	void  OnError ( long lRequestId,
		IDispatch * pHist,
		enum enumHistErrorType err );

	void SetComMgr(IMbtComMgrPtr cm) {m_ComMgr = cm;}

public:


protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	CRITICAL_SECTION m_criticalSection;

	IMbtComMgrPtr m_ComMgr;

	virtual void _OnMinBar(		long lRequestId,		IDispatch * pHist, enumHistEventType evt );
	virtual void _OnDayBar  (		long lRequestId,		IDispatch * pHist, enumHistEventType evt );
	virtual void _OnTick  (		long lRequestId,		IDispatch * pHist, enumHistEventType evt );

private:
	int m_RecsSoFar;

};


#endif
