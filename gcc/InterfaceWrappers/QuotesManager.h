#ifndef QuotesManager_h
#define QuotesManager_h

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
class IQuotes;

class QuotesManager
{
public:
    static QuotesManager * instance();
    static QuotesManager * createInstance(IQuotes * pQuotes,
                                          MBQuotes_i * quotesCB);
    static void removeInstance();
	bool addSymbols(std::vector<std::string> quotesList);
    
    // FIX Type data
    bool OnQuoteData(std::string pRec);
    bool OnLevel2Data(std::string pRec);
    bool OnTSData(std::string pRec);
    bool OnOptionsData(std::string pRec);
    
	// TODO static mutex hMutex;
private:
    QuotesManager(IQuotes * pQuotes,
                  MBQuotes_i *quotesCB);
     ~QuotesManager();
   
    IQuotes * pQuotes_;
    MBQuotes_i * quotes_;
    
    static QuotesManager *instance_;

	std::ofstream utcOut_;
};

#endif


