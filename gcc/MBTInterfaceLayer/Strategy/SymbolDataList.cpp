#include "SymbolDataList.h"
#include "SymbolData.h"

SymbolDataList * SymbolDataList::instance_ = 0;

SymbolDataList * SymbolDataList::instance()
{
    if(0 == instance_)
    {
        instance_ = new SymbolDataList();
    }
    return instance_;
}

void SymbolDataList::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

void SymbolDataList::addSymbolData(SymbolData * stock)
{
    symbolData_[stock->symbol()] = stock;
}

SymbolData * SymbolDataList::getSymbolData(const std::string & symbol)
{
    SymbolDataMapIter iter = symbolData_.find(symbol);
    if(iter != symbolData_.end())
    {
        return (*iter).second;
    }
    return 0;
}

SymbolDataList::SymbolDataList()
{
}

SymbolDataList::~SymbolDataList()
{
    SymbolDataMapIter iter;
    for(iter = symbolData_.begin(); iter != symbolData_.end(); ++iter)
    {
        delete (*iter).second;
    }
}


