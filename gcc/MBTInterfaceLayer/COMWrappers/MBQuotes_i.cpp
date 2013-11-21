#include "MBQuotes_i.h"

MBQuotes_i::MBQuotes_i(IMbtQuotesPtr pQuotes)
{
    qManager_ = QuotesManager::createInstance(pQuotes, this);
}
    
MBQuotes_i::~MBQuotes_i()
{
    QuotesManager::removeInstance();
}


