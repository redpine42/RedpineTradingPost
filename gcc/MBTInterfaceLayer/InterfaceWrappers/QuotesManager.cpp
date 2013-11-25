#include "stdafx.h"

#include <iostream>
#include <strstream>

#include "QuotesManager.h"
#include <fstream>
#include <bitset>
#include "MBQuotes_i.h"

#include "TimeZone.h"
#include "MsgProducer.h"
#include "TimeSalesData.h"
#include "L2Data.h"

QuotesManager *QuotesManager::instance_ = 0;
HANDLE QuotesManager::hMutex= CreateMutex (NULL,    // no security attributes 
										   FALSE,   // initially not owned 
										   "MutexToProtectCriticalSection");    // name of mutex 

QuotesManager * QuotesManager::createInstance(IMbtQuotesPtr pQuotes, 
                                              MBQuotes_i * quotesCB)
{
	if(0 == instance_)
	{
		instance_ = new QuotesManager(pQuotes, quotesCB);
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::QUOTESMANAGER, "Quotes Manager Created");
	}
    
    return instance_;
}

QuotesManager * QuotesManager::instance()
{
    if(0 == instance_)
    {
        // This would be an error;
		MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::QUOTESMANAGER, "Quotes Manager instance called before construction!");
        return 0;
    }
    return instance_;
}

void QuotesManager::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

QuotesManager::~QuotesManager()
{
    pQuotes_->UnadviseAll(quotes_);
    pQuotes_->Disconnect();
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::QUOTESMANAGER, "Quotes Manager Destroyed");
   
	CloseHandle(hMutex); //do as late as possible
    hMutex = NULL; //good habit to be in
}

HRESULT QuotesManager::OnQuoteData(QUOTERECORD* pRec)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(hMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval

    _bstr_t symbol(pRec->bstrSymbol);
    std::string symbolStr = (const char *)symbol;
    
	bool upTick = false;
	bool shortable = (pRec->lFlags == 1 || pRec->lFlags == 3);
        
   if(pRec->tick == 0)
   {
        upTick = true;
   }


    L1Data data(symbolStr,
			    pRec->lLastSize,
				pRec->dLast,
				TimeZone::instance()->getSecondsGMT(pRec->UTCDateTime),
				TimeZone::instance()->getJDate(pRec->UTCDateTime),
				0,
				TimeZone::instance()->getUSecondsLocal(),
				pRec->dBid,
				pRec->dAsk,
				pRec->lBidSize,
				pRec->lAskSize,
				upTick,
				pRec->lVolume,
				shortable);

	MsgProducer::instance()->sendL1Data(data);
    ReleaseMutex(hMutex);
    return 0;
}

HRESULT QuotesManager::OnLevel2Data(LEVEL2RECORD* pRec)
{
    if(pRec->bClosed)
    {
 //       return 0;
    }
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(hMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
    
    _bstr_t symbol(pRec->bstrSymbol);
	std::string symbolStr = (const char *)symbol;

    _bstr_t MMID(pRec->bstrMMID);
	std::string mmidStr = (const char *)MMID;

    _bstr_t source(pRec->bstrSource);
	std::string sourceStr = (const char *)source;

	bool closed = (pRec->bClosed > 0);

	L2Data data(symbolStr,
				mmidStr,
				sourceStr,
				(DataEnums::OrderSide)pRec->side,
				pRec->dPrice,
				pRec->lSize,
				TimeZone::instance()->getSecondsGMT(pRec->UTCTime),
				TimeZone::instance()->getCurrentJDate(),
				TimeZone::instance()->getUSecondsLocal(),
				closed,
				0);

	MsgProducer::instance()->sendL2Data(data);
    ReleaseMutex(hMutex);
    return 0;
}

HRESULT QuotesManager::OnTSData(TSRECORD* pRec)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(hMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval

    _bstr_t symbol(pRec->bstrSymbol);
    std::string symbolStr = (const char *)symbol;

	TimeSalesData data(symbolStr,
		               pRec->lSize,
					   pRec->dPrice,
					   TimeZone::instance()->getSecondsGMT(pRec->UTCDateTime),
					   TimeZone::instance()->getJDate(pRec->UTCDateTime),
					   0,
					   TimeZone::instance()->getUSecondsLocal(),
					   (DataEnums::TickStatus)pRec->status,
					   (DataEnums::TickType)pRec->type);

	MsgProducer::instance()->sendTimeSalesData(data);

	ReleaseMutex(hMutex);
    return 0;
}

HRESULT QuotesManager::OnOptionsData(OPTIONSRECORD* pRec)
{
    return 0;
}

QuotesManager::QuotesManager(IMbtQuotesPtr pQuotes, 
                             MBQuotes_i * quotesCB)
    : pQuotes_(pQuotes),
      quotes_(quotesCB)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(hMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
    pQuotes_->Connect();
    ReleaseMutex(hMutex);
}

bool QuotesManager::addSymbols(std::vector<std::string> quotesList)
{
	bool ret = false;
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(hMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
	enumConnectionState quoteState = pQuotes_->ConnectionState; 
	if(quoteState == csLoggedIn)
	{
		std::vector<std::string>::iterator iter;
	    for(iter = quotesList.begin(); iter != quotesList.end(); ++iter)
		{
			std::string symbol = (*iter);
	        pQuotes_->AdviseSymbol(quotes_, (*iter).c_str(), qsfLevelTwo);
			pQuotes_->AdviseSymbol(quotes_, symbol.c_str(), qsfLevelOne);
			pQuotes_->AdviseSymbol(quotes_, symbol.c_str(), qsfTimeAndSales);
			Sleep(200);
			std::string msg = "Symbol Data Subscribed too(" + symbol + ")";
		    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::QUOTESMANAGER, msg);
		}
		ret = true;
	}
    ReleaseMutex(hMutex);
	return ret;
}


