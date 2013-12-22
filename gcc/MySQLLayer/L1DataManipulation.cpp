#include "L1DataManipulation.h"
#include "MySQLLayer.h"
#include "CursorData.h"
#include "Conversions.h"
#include "L1Data.h"
 
#include <stdlib.h>

L1DataManipulation * L1DataManipulation::instance_ = 0;

L1DataManipulation * L1DataManipulation::instance()
{
	if(0 == instance_)
	{
		instance_ = new L1DataManipulation();
	}
	return instance_;
}

L1DataManipulation::L1DataManipulation()
{
}

L1DataManipulation::~L1DataManipulation()
{
	bulkDataFlush();
}


void L1DataManipulation::getL1Data(std::string & symbol, std::vector<L1Data*> & l1Data)
{
}

void L1DataManipulation::bulkDataFlush()
{
	std::string sqlQuery = "INSERT INTO backtest.l1data (Symbol,sizeVal,price,timeval,jdate,timeStamp,bid,ask,bidsize,asksize,volume) values ";
	L1DataVecIter iter;
	for(iter = l1DataVec_.begin(); iter != l1DataVec_.end();)
	{
		const L1Data * data = (*iter);
	    sqlQuery += "(\"";
	    sqlQuery += data->symbol_;
		sqlQuery += "\",";
		sqlQuery += Conversions::getStrFromULong(data->size_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->price_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->time_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->timeStamp_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->bid_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->ask_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->bidSize_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->askSize_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->volume_);
		sqlQuery += ")";
		if(++iter != l1DataVec_.end())
		{
			sqlQuery += ",";
		}
	}
	sqlQuery += ";";
	bool result = MySQLLayer::instance()->insertData(sqlQuery);
	if(!result)
	{
		for(iter = l1DataVec_.begin(); iter != l1DataVec_.end(); ++iter)
		{
			const L1Data * data = (*iter);
			saveL1Data(data);
		}
		l1DataVec_.erase(l1DataVec_.begin(), l1DataVec_.end());
	}
	for(iter = l1DataVec_.begin(); iter != l1DataVec_.end(); ++iter)
	{
		const L1Data * data = (*iter);
		delete data;
	}
	l1DataVec_.erase(l1DataVec_.begin(), l1DataVec_.end());
	MySQLLayer::instance()->commit();
}

void L1DataManipulation::getL1Data(std::string & symbol, std::vector<L1Data*> & l1Data, DateTimeRange & dateData)
{
	std::string sqlQuery = "Select Symbol,seq,sizeVal,price,timeval,jdate,timeStamp,bid,ask,bidsize,asksize,volume From backtest.l1data where Symbol=\"";
	sqlQuery += symbol;
	sqlQuery += "\" and jdate between ";
	sqlQuery += Conversions::getStrFromULong(dateData.startJDate_);
	sqlQuery += " AND ";
	sqlQuery += Conversions::getStrFromULong(dateData.endJDate_);
	sqlQuery += " and time between ";
	sqlQuery += Conversions::getStrFromULong(dateData.startTime_);
	sqlQuery += " AND ";
	sqlQuery += Conversions::getStrFromULong(dateData.endTime_);
	sqlQuery += " order by seq;";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
//		l1Data.resize(cData->size_);
		while ( cData->next())
		{
			unsigned long long seq = atol(cData->rowFile_[1]);
			double price = atof(cData->rowFile_[3]);
			unsigned long volume = atol(cData->rowFile_[2]);
			unsigned long timeVal = atol(cData->rowFile_[4]);
			unsigned long jdate = atol(cData->rowFile_[5]);
			double timeStamp = atof(cData->rowFile_[6]);
			double bid = atof(cData->rowFile_[7]);
			double ask = atof(cData->rowFile_[8]);
			unsigned long bidSize = atol(cData->rowFile_[9]);
  			unsigned long askSize = atol(cData->rowFile_[10]);
			unsigned long totalvol = atol(cData->rowFile_[11]);

			L1Data * data = new L1Data(symbol, 
									   volume,
									   price,
									   timeVal,
									   jdate,
									   seq,
									   timeStamp,
									   bid,
									   ask,
									   bidSize,
									   askSize,
									   true,
									   totalvol,
									   true);

			l1Data.push_back(data);
		}
	}
	delete cData;
}

void L1DataManipulation::saveL1Data(const L1Data* data)
{
	std::string sqlQuery = "INSERT INTO backtest.l1data (Symbol,sizeVal,price,timeval,jdate,timeStamp,bid,ask,bidsize,asksize,volume) values (\"";
	    sqlQuery += data->symbol_;
		sqlQuery += "\",";
		sqlQuery += Conversions::getStrFromULong(data->size_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->price_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->time_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->timeStamp_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->bid_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->ask_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->bidSize_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->askSize_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->volume_);
		sqlQuery += ")";

	MySQLLayer::instance()->insertData(sqlQuery);
	delete data;
}

void L1DataManipulation::bulkSave(const L1Data* data)
{
	l1DataVec_.push_back(data);
	if(l1DataVec_.size() >= 1000)
	{
		bulkDataFlush();
	}
}

L1DataManipulation::L1Iter::L1Iter(std::string & symbol, unsigned int startSeq)
	: lastSeq_(startSeq),
	  cacheSize_(1000),
	  symbol_(symbol)
{
}

L1Data * L1DataManipulation::L1Iter::getNext()
{
	if(cachedData_.size() == 0)
	{
		lastSeq_ = L1DataManipulation::instance()->getL1Data(symbol_, cachedData_, lastSeq_, cacheSize_);
		if(cachedData_.size() == 0)
		{
			return 0;
		}
	}
	L1Data * ret = cachedData_.front();
	cachedData_.pop();

	return ret;
}

void L1DataManipulation::L1Iter::getNextData(unsigned int size, std::vector<L1Data*>& data)
{
}

unsigned long long L1DataManipulation::getL1Data(const std::string & symbol, std::queue<L1Data*> & cacheData, unsigned long long seq, unsigned int size)
{
	unsigned long long ret = 0;
	std::string sqlQuery = "Select Symbol,seq,sizeVal,price,timeval,jdate,timeStamp,bid,ask,bidsize,asksize,volume From backtest.l1data where Symbol=\"";
	sqlQuery += symbol;
	sqlQuery += "\" and seq > ";
	sqlQuery += Conversions::getStrFromULongLong(seq);
	sqlQuery += " order by seq";
	sqlQuery += " LIMIT 0, ";
	sqlQuery += Conversions::getStrFromUInt(size);
	sqlQuery += ";";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
		while ( cData->next())
		{
			seq = atol(cData->rowFile_[1]);
			double price = atof(cData->rowFile_[3]);
			unsigned long volume = atol(cData->rowFile_[2]);
			unsigned long timeVal = atol(cData->rowFile_[4]);
			unsigned long jdate = atol(cData->rowFile_[5]);
			double timeStamp = atof(cData->rowFile_[6]);
			double bid = atof(cData->rowFile_[7]);
			double ask = atof(cData->rowFile_[8]);
			unsigned long bidSize = atol(cData->rowFile_[9]);
  			unsigned long askSize = atol(cData->rowFile_[10]);
			unsigned long totalvol = atol(cData->rowFile_[11]);
			L1Data * data = new L1Data(symbol, 
									   volume,
									   price,
									   timeVal,
									   jdate,
									   seq,
									   timeStamp,
									   bid,
									   ask,
									   bidSize,
									   askSize,
									   true,
									   totalvol,
									   true);
			ret = seq;
			cacheData.push(data);
		}
	}
	delete cData;

	return ret;
}
