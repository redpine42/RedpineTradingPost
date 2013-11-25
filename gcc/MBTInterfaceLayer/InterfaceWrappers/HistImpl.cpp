#include "HistImpl.h"
#include "CandleStickManager.h"

#define IMPLEMENT_MBTQUOTESNOTIFY_ALL_SINK(class_name)\
	IMPLEMENT_MBTQUOTESNOTIFY_IUNKNOWNS(class_name)\
	IMPLEMENT_MBTQUOTESNOTIFY(class_name, OnDataEvent, long, IDispatch*, enumHistEventType)\
	IMPLEMENT_MBTQUOTESNOTIFY(class_name, OnError, long, IDispatch*, enumHistEventType)

#define IMPLEMENT_MBTQUOTESNOTIFY_IUNKNOWNS(class_name)\
	STDMETHODIMP_(ULONG) class_name::XMbtHistNotify::AddRef()\
	{\
		METHOD_PROLOGUE(class_name, MbtHistNotify)\
		return pThis->AddRef();\
	}\
	STDMETHODIMP_(ULONG) class_name::XMbtHistNotify::Release()\
	{\
		METHOD_PROLOGUE(class_name, MbtHistNotify)\
		return pThis->Release();\
	}\
	STDMETHODIMP class_name::XMbtHistNotify::QueryInterface(REFIID iid, LPVOID* ppvObj)\
	{\
		METHOD_PROLOGUE(class_name, MbtHistNotify)\
		return pThis->QueryInterface(&iid, ppvObj);\
	}

#define IMPLEMENT_MBTQUOTESNOTIFY_NOTIMPL(class_name, function_name, param_type1,param_type2, param_type3)\
	STDMETHODIMP class_name::XMbtHistNotify::raw_##function_name(param_type1 pRec1, param_type2 pRec2, param_type3 pRec3)	{ return E_NOTIMPL; }
#define IMPLEMENT_MBTQUOTESNOTIFY(class_name, function_name, param_type1,param_type2, param_type3)\
	STDMETHODIMP class_name::XMbtQuotesNotify::raw_##function_name(param_type1 pRec1, param_type2 pRec2, param_type3 pRec3)\
	{\
		METHOD_PROLOGUE(class_name, MbtQuotesNotify)\
		/*Thunk this back to the containing parent class (which is a virtual\
		  function that can be overridden in derived classes to handle)*/\
		return pThis->function_name(pRec1, pRec2, pRec3);\
	}


IMPLEMENT_MBTQUOTESNOTIFY_ALL_SINK(HistImpl)
IMPLEMENT_MBTQUOTESNOTIFY(HistImpl)
BEGIN_MESSAGE_MAP(HistImpl, CCmdTarget)
	//{{AFX_MSG_MAP(CDlgLevel2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BEGIN_INTERFACE_MAP(HistImpl, CCmdTarget)
		INTERFACE_PART(HistImpl, __uuidof(IMbtHistNotify), MbtHistNotify)
END_INTERFACE_MAP()

HRESULT HistImpl::OnDataEvent (
        long requestId,
        IDispatch * pHist,
        enum enumHistEventType evt )
{
	switch(evt)
	{
	case hetInitial:
		CandleStickManager::instance()->historyInitial(requestId);
		break;
	case hetNew:
		CandleStickManager::instance()->historyNew(requestId);
		break;
	case hetUpdate:
		CandleStickManager::instance()->historyUpdate(requestId);
		break;
	}
	return true;
}
 
HRESULT HistImpl::OnError (
        long requestId,
        IDispatch * pHist,
        enum enumHistErrorType err )
{
	std::string msg;
	switch(err) 
	{
		case errNoError:							msg = "errNoError";							break;
		case errClientSideConnect:					msg = "errClientSideConnect";				break;
		case errClientSideTimeout:					msg = "errClientSideTimeout";				break; 
		case errClientSideSend:						msg = "errClientSideSend";					break;
		case errClientSideRecv:						msg = "errClientSideRecv";					break;
		case errClientSideMemoryAlloc:				msg = "errClientSideMemoryAlloc";			break;
		case errClientSideDecompress:				msg = "errClientSideDecompress";			break; 
		case errClientSideParsing:					msg = "errClientSideParsing";				break; 
		case errServerSideMaintInProgress:			msg = "errServerSideMaintInProgress";		break;
		case errServerSideInvalidRequest:			msg = "errServerSideInvalidRequest";		break;
		case errServerSideDataLoad:					msg = "errServerSideDataLoad";				break; 
		case errServerSideMemoryAlloc:				msg = "errServerSideMemoryAlloc";			break; 
		case errServerSideNoRequestData:			msg = "errServerSideNoRequestData";			break; 
		case errServerSideCompress:					msg = "errServerSideCompress";				break;
		case errServerSideFormatting:				msg = "errServerSideFormatting";			break;
		case errServerSideInvalidUserOrPwd:			msg = "errServerSideInvalidUserOrPwd";		break;
		case errServerSideLockedOut:				msg = "errServerSideLockedOut";				break;
		case errServerSideInternalDatabaseError:	msg = "errServerSideInternalDatabaseError";	break;
		case errServerSideNotEntitled :				msg = "errServerSideNotEntitled";			break;
		default:									msg = "Unkown Error";						break;
	};
	CandleStickManager::instance()->historyError(requestId, msg);
	return true;
}

