#include "DataStore.h"
#include <iostream>
#include <strstream>
#include "L1Data.h"
#include "L2Data.h"
#include "TimeSalesData.h"
#include "CandleData.h"
#include "L1DataManipulation.h"
#include "L2DataManipulation.h"
#include "CandleDataManipulation.h"
#include "TimeSalesDataManipulation.h"

HANDLE DataStore::l1Mutex= CreateMutex (NULL,    // no security attributes 
										   FALSE,   // initially not owned 
										   "MutexToProtectCriticalSection");    // name of mutex 

HANDLE DataStore::l2Mutex= CreateMutex (NULL,    // no security attributes 
										   FALSE,   // initially not owned 
										   "MutexToProtectCriticalSection");    // name of mutex 

HANDLE DataStore::tsMutex= CreateMutex (NULL,    // no security attributes 
										   FALSE,   // initially not owned 
										   "MutexToProtectCriticalSection");    // name of mutex 

HANDLE DataStore::cdMutex= CreateMutex (NULL,    // no security attributes 
										   FALSE,   // initially not owned 
										   "MutexToProtectCriticalSection");    // name of mutex 


DataStore::DataStore(void)
{
}

DataStore::~DataStore(void)
{
}

void DataStore::logL1DataCB(const L1Data* data)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(l1Mutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
	if(data->bid_ == 0.0)
	{
    	ReleaseMutex(l1Mutex);
		return;
	}
	L1DataManipulation::instance()->bulkSave(data);
	ReleaseMutex(l1Mutex);
}

void DataStore::logL2DataCB(const L2Data* data)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(l2Mutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
	L2DataManipulation::instance()->bulkSave(data);
	ReleaseMutex(l2Mutex);
}

void DataStore::logCandleDataCB(const CandleData* data)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(cdMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
	CandleDataManipulation::instance()->saveCandleData(data);
	ReleaseMutex(cdMutex);
}

void DataStore::logTimeSalesDataCB(const TimeSalesData* data)
{
    DWORD dwWaitResult; 
    dwWaitResult = WaitForSingleObject(tsMutex,                 // handle of mutex
                                       5000L);                 // five-second time-out interval
	TimeSalesDataManipulation::instance()->bulkSave(data);
	ReleaseMutex(tsMutex);
}


