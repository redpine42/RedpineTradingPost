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

pthread_mutex_t DataStore::l1Mutex;    // name of mutex
pthread_mutex_t DataStore::l2Mutex;    // name of mutex
pthread_mutex_t DataStore::tsMutex;    // name of mutex
pthread_mutex_t DataStore::cdMutex;    // name of mutex


DataStore::DataStore(void)
{
}

DataStore::~DataStore(void)
{
}

void DataStore::logL1DataCB(const L1Data* data)
{
	pthread_mutex_lock(&l1Mutex);
	if(data->bid_ == 0.0)
	{
		pthread_mutex_lock(&l1Mutex);
		return;
	}
	L1DataManipulation::instance()->bulkSave(data);
	pthread_mutex_lock(&l1Mutex);
}

void DataStore::logL2DataCB(const L2Data* data)
{
	pthread_mutex_lock(&l2Mutex);                 // five-second time-out interval
	L2DataManipulation::instance()->bulkSave(data);
	pthread_mutex_lock(&l2Mutex);
}

void DataStore::logCandleDataCB(const CandleData* data)
{
	pthread_mutex_lock(&cdMutex);                 // five-second time-out interval
	CandleDataManipulation::instance()->saveCandleData(data);
	pthread_mutex_lock(&cdMutex);
}

void DataStore::logTimeSalesDataCB(const TimeSalesData* data)
{
	pthread_mutex_lock(&tsMutex);                 // five-second time-out interval
	TimeSalesDataManipulation::instance()->bulkSave(data);
	pthread_mutex_lock(&tsMutex);
}


