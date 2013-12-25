// MbtQuotesNotify.h: Definition of the CMbtQuotesNotify class
//
//////////////////////////////////////////////////////////////////////
#ifndef MBQuotes_ih
#define MBQuotes_ih

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#ifndef QuotesManager_h
#include "QuotesManager.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// MBQuotes_i -- private sink object which implements MBT's direct quote callback interface

class MBQuotes_i: 
	public IMbtQuotesNotify
{
public:
    MBQuotes_i(IMbtQuotesPtr pQuotes);
    
    ~MBQuotes_i();

    HRESULT __stdcall raw_OnQuoteData(QUOTERECORD* pRec) { return qManager_->OnQuoteData(pRec) ; }
    HRESULT __stdcall raw_OnLevel2Data(LEVEL2RECORD* pRec) { return qManager_->OnLevel2Data(pRec); }
    HRESULT __stdcall raw_OnTSData(TSRECORD* pRec) { return qManager_->OnTSData(pRec);}
    HRESULT __stdcall raw_OnOptionsData(OPTIONSRECORD* pRec) { return qManager_->OnOptionsData(pRec) ; }
    unsigned long __stdcall AddRef() {return 0; }
    unsigned long __stdcall Release() {return 0; }
    long __stdcall QueryInterface(const struct _GUID&, void **) {return 0;}

    QuotesManager * qManager_;
};

#endif
