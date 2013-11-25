#ifndef HistImpl_h
#define HistImpl_h

#include "stdafx.h"

class HistImpl: public CCmdTarget, IMbtHistNotify
{
public:

    HRESULT OnDataEvent (
        long lRequestId,
        IDispatch * pHist,
        enum enumHistEventType evt );
    HRESULT OnError (        long lRequestId,
        IDispatch * pHist,
        enum enumHistErrorType err );

	long __stdcall QueryInterface(const struct _GUID &,void ** ){return 0;}
	unsigned long __stdcall AddRef() {return ++refCnt_;}
	unsigned long __stdcall Release() { return --refCnt_;}
private:
	unsigned long refCnt_;

};

#endif

