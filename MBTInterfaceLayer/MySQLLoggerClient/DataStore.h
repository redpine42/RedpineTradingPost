#pragma once
#include <winsock.h>

#ifndef L1DataInterface_h
#include "L1DataInterface.h"
#endif

#ifndef L2DataInterface_h
#include "L2DataInterface.h"
#endif

#ifndef TimeSalesDataInterface_h
#include "TimeSalesDataInterface.h"
#endif

#ifndef CandleDataInterface_h
#include "CandleDataInterface.h"
#endif

struct L1Data;
struct L2Data;
struct TimeSalesData;


class DataStore : public L1DataInterface, public L2DataInterface, public TimeSalesDataInterface, public CandleDataInterface
{
public:
	DataStore(void);
	~DataStore(void);

	void logL1DataCB(const L1Data* data);
	void logTimeSalesDataCB(const TimeSalesData* data);
	void logCandleDataCB(const CandleData* data);
	void logL2DataCB(const L2Data* data);

private:
	static HANDLE l1Mutex; 
	static HANDLE l2Mutex; 
	static HANDLE tsMutex; 
	static HANDLE cdMutex; 
};
