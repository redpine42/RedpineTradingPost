#ifndef QuotesManager_h
#define QuotesManager_h

#ifndef stdafx_h
#include "stdafx.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

class MBQuotes_i;
class StockWatch;

class QuotesManager
{
public:
    static QuotesManager * instance();
    static QuotesManager * createInstance(IMbtQuotesPtr pQuotes, 
                                          MBQuotes_i * quotesCB);
    static void removeInstance();
	bool addSymbols(std::vector<std::string> quotesList);
    
    // IMbtQuotesNotify callbacks required by CMbtQuotesNotify sink
    HRESULT OnQuoteData(QUOTERECORD* pRec);
    HRESULT OnLevel2Data(LEVEL2RECORD* pRec);
    HRESULT OnTSData(TSRECORD* pRec);
    HRESULT OnOptionsData(OPTIONSRECORD* pRec);
    
	static HANDLE hMutex; 
private:
    QuotesManager(IMbtQuotesPtr pQuotes, 
                  MBQuotes_i *quotesCB);
     ~QuotesManager();
   
    IMbtQuotesPtr pQuotes_;	
    MBQuotes_i * quotes_;
    
    static QuotesManager *instance_;

	std::ofstream utcOut_;
};

#endif


