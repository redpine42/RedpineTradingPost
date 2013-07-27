#pragma warning(disable:4786)
#ifndef SymbolDataList_h
#define SymbolDataList_h

class SymbolData;

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

class SymbolDataList
{
public:
    static SymbolDataList * instance();
	static void removeInstance();
    
    void addSymbolData(SymbolData * stock);
    SymbolData * getSymbolData(const std::string & symbol);
    
private:
    ~SymbolDataList();
    static SymbolDataList * instance_;
    SymbolDataList();
    
    typedef std::map<std::string, SymbolData*, std::less<std::string> > SymbolDataMap;
    typedef SymbolDataMap::iterator SymbolDataMapIter;
    
    SymbolDataMap symbolData_;
};

#endif

