#pragma warning(disable:4786) 
#ifndef OrderBook_h
#define OrderBook_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

struct L2Data;

#ifndef vector_h
#include <vector>
#define vector_h
#endif

class OrderBook
{
public:
    
	OrderBook(std::string & symbol, DataEnums::OrderSide orderType);
    ~OrderBook();
    void addData(const L2Data * data);
    
protected:
    
	typedef std::vector<const L2Data *> L2DataVec;
	typedef std::vector<const L2Data *>::iterator L2DataVecIter;
    typedef std::map<const std::string, L2DataVec, std::less<const std::string> > BookDataMap;
    typedef BookDataMap::iterator BookDataMapIter;
    typedef BookDataMap::const_iterator BookDataMapCIter;
  
    BookDataMap bookData_;

	std::string symbol_;
	DataEnums::OrderSide side_;
};

#endif

