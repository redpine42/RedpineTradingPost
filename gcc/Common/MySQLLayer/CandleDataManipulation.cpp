#include "CandleDataManipulation.h"
#include "MySQLLayer.h"
#include "CursorData.h"
#include "Conversions.h"
#include "L1Data.h"
#include "SymbolHelper.h"
#include "CandleDataHelper.h"
#include "TimeZone.h"

#include <iostream>
#include <strstream>
#include <fstream>
#include <stdlib.h>

CandleDataManipulation * CandleDataManipulation::instance_ = 0;

CandleDataManipulation * CandleDataManipulation::instance()
{
	if(0 == instance_)
	{
		instance_ = new CandleDataManipulation();
	}
	return instance_;
}

CandleDataManipulation::CandleDataManipulation()
{
}

CandleDataManipulation::~CandleDataManipulation()
{
	bulkDataFlush();
}


void CandleDataManipulation::getCandleData(std::string & symbol, CandleData::CandleTimeType timeType, std::vector<CandleData*> & candleData)
{
	std::string sqlQuery = "Select Symbol,jdate,startTime,vol,open,high,low,close From backtest.candledata where Symbol=\"";
	sqlQuery += symbol;
	sqlQuery += "\" and timetype=";
	sqlQuery += Conversions::getStrFromInt((int)timeType);
	sqlQuery += " order by jDate,startTime;";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
//		candleData.resize(cData->size_);

		while ( cData->next())
		{
			unsigned long jdate = atol(cData->rowFile_[1]);
			unsigned long startTime = atol(cData->rowFile_[2]);
			unsigned long vol = atol(cData->rowFile_[3]);
			double open = atof(cData->rowFile_[4]);
			double high = atof(cData->rowFile_[5]);
			double low = atof(cData->rowFile_[6]);
			double close = atof(cData->rowFile_[7]);

			CandleData * data = new CandleData(symbol, 
									           vol,
											   open,
											   high,
											   low,
											   close,
											   jdate,
											   startTime,
											   timeType,
											   CandleData::RETRIEVAL);

			candleData.push_back(data);
		}
	}
	delete cData;
}

unsigned long CandleDataManipulation::getDateRange(std::string & symbol, CandleData::CandleTimeType timeType, DateTimeRange & dateData)
{
	unsigned long numCandles = 0;
	std::string tableName = symbolToTableSymbol(symbol);
	tableName += "_";
	tableName += CandleData::getStrType(timeType);

	std::string sqlQuery = "Select count(*) from backtest.";
	sqlQuery += tableName;
	sqlQuery += ";";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0 && cData->next())
	{
		numCandles = atol(cData->rowFile_[0]);
	}

	sqlQuery = "Select max(jdate) from backtest.";
	sqlQuery += tableName;
	sqlQuery += ";";

	cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0 && cData->next())
	{
		dateData.endJDate_ = atol(cData->rowFile_[0]);
	}

	sqlQuery = "Select max(startTime) from backtest.";
	sqlQuery += tableName;
	sqlQuery += " where jdate=";
	sqlQuery += cData->rowFile_[0];
	sqlQuery += ";";

	cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0 && cData->next())
	{
		dateData.endTime_ = atol(cData->rowFile_[0]);
	}

	sqlQuery = "Select min(jdate) from backtest.";
	sqlQuery += tableName;
	sqlQuery += ";";

	cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0 && cData->next())
	{
		dateData.startJDate_ = atol(cData->rowFile_[0]);
	}

	sqlQuery = "Select min(startTime) from backtest.";
	sqlQuery += tableName;
	sqlQuery += " where jdate=";
	sqlQuery += cData->rowFile_[0];
	sqlQuery += ";";

	cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0 && cData->next())
	{
		dateData.startTime_ = atol(cData->rowFile_[0]);
	}

	return numCandles;
}


void CandleDataManipulation::getCandleData(std::string & symbol, CandleData::CandleTimeType timeType, std::vector<CandleData*> & candleData, DateTimeRange & dateData)
{
	std::string sqlQuery = "Select Symbol,jdate,startTime,vol,open,high,low,close From backtest.candledata where Symbol=\"";
	sqlQuery += symbol;
	sqlQuery += "\" and timetype=";
	sqlQuery += Conversions::getStrFromInt((int)timeType);
	sqlQuery += " and jdate between ";
	sqlQuery += Conversions::getStrFromULong(dateData.startJDate_);
	sqlQuery += " AND ";
	sqlQuery += Conversions::getStrFromULong(dateData.endJDate_);
	sqlQuery += " order by jDate,startTime;";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
//		candleData.resize(cData->size_);

		while ( cData->next())
		{
			unsigned long jdate = atol(cData->rowFile_[1]);
			unsigned long startTime = atol(cData->rowFile_[2]);
			unsigned long vol = atol(cData->rowFile_[3]);
			double open = atof(cData->rowFile_[4]);
			double high = atof(cData->rowFile_[5]);
			double low = atof(cData->rowFile_[6]);
			double close = atof(cData->rowFile_[7]);

			CandleData * data = new CandleData(symbol, 
									           vol,
											   open,
											   high,
											   low,
											   close,
											   jdate,
											   startTime,
											   timeType,
											   CandleData::RETRIEVAL);

			candleData.push_back(data);
		}
	}
	delete cData;
}

void CandleDataManipulation::saveCandleData(const CandleData* data)
{
	std::string sqlQuery;
	if(data->candleUpdateType_ == CandleData::UPDATE)
	{
		bulkSave(data);
	}
	else if(data->candleUpdateType_ == CandleData::INITIAL ||
		    data->candleUpdateType_ == CandleData::NEW)
	{
		sqlQuery = "INSERT INTO backtest.candledata (Symbol,timetype,jdate,startTime,vol,open,high,low,close) values (\"";
		sqlQuery += data->symbol_;
		sqlQuery += "\",";
		sqlQuery += Conversions::getStrFromULong(data->candleTimeType_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->startTime_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->volume_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->open_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->high_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->low_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->close_);
		sqlQuery += ")";
		
		delete data;
	}
	MySQLLayer::instance()->insertData(sqlQuery);
}

bool CandleDataManipulation::bulkInsertCandleData(std::vector<CandleData*> & dataVec, std::string & tableName)
{
	std::string sqlQuery = "INSERT INTO backtest.candledata (Symbol,timetype,jdate,startTime,vol,open,high,low,close,reason) values";
	std::vector<CandleData*>::iterator iter;
	for(iter = dataVec.begin(); iter != dataVec.end();)
	{
		CandleData * data = (*iter);
		sqlQuery += " (\"";
		sqlQuery += data->symbol_ + "\",";
		sqlQuery += Conversions::getStrFromInt(data->candleTimeType_) + ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_) + ",";
		sqlQuery += Conversions::getStrFromULong(data->startTime_) + ",";
		sqlQuery += Conversions::getStrFromULong(data->volume_) + ",";
		sqlQuery += Conversions::getStrFromDouble(data->open_) + ",";
		sqlQuery += Conversions::getStrFromDouble(data->high_) + ",";
		sqlQuery += Conversions::getStrFromDouble(data->low_) + ",";
		sqlQuery += Conversions::getStrFromDouble(data->close_) + ",";
		sqlQuery += Conversions::getStrFromInt(data->candleUpdateType_) + ")";
		if(++iter != dataVec.end())
		{
			sqlQuery += ",";
		}
	}
	sqlQuery += ";";
	bool result = MySQLLayer::instance()->insertData(sqlQuery);
	if(!result)
	{
		for(iter = dataVec.begin(); iter != dataVec.end(); ++iter)
		{
			CandleData * data = (*iter);
			saveCandleData(data);
		}
	}
	for(iter = dataVec.begin(); iter != dataVec.end(); ++iter)
	{
		CandleData * data = (*iter);
		delete data;
	}
	dataVec.erase(dataVec.begin(), dataVec.end());
	return result;
}

void CandleDataManipulation::populateTables(std::vector<std::string> & fileNames)
{
	std::vector<std::string>::iterator iter;
	std::cout << "Deleting candle table data" << std::endl;

	std::string sqlQuery = "drop table backtest.candledata";
	MySQLLayer::instance()->insertData(sqlQuery);

	sqlQuery = "CREATE TABLE `candledata` (";
	sqlQuery += "`symbol` varchar(7) NOT NULL,";
	sqlQuery += "`timeType` tinyint(3) unsigned NOT NULL,";
	sqlQuery += "`jdate` int(10) unsigned NOT NULL,";
	sqlQuery += "`startTime` int(10) unsigned NOT NULL,";
	sqlQuery += "`high` float unsigned NOT NULL,";
	sqlQuery += "`low` float unsigned NOT NULL,";
	sqlQuery += "`open` float unsigned NOT NULL,";
	sqlQuery += "`close` float unsigned NOT NULL,";
	sqlQuery += "`vol` int(10) unsigned NOT NULL,";
	sqlQuery += "`reason` tinyint(3) NOT NULL DEFAULT '3',";
	sqlQuery += "PRIMARY KEY (`symbol`,`timeType`,`jdate`,`startTime`))";
	MySQLLayer::instance()->insertData(sqlQuery);

	CandleDataHelper helper;

	for(iter = fileNames.begin(); iter != fileNames.end(); ++iter)
	{
		std::string fileName = (*iter);
		std::string tableName = fileName.substr(0, fileName.length()-4);
		std::ifstream istrm(fileName.c_str());
		std::string fileSymbol = parseSymbolName(fileName);
		std::string symbol = fileSymbol.substr(0,3);
		symbol += "/";
		symbol += fileSymbol.substr(3,3);
		std::string timeFrame = parseTimeFrame(fileName);
		CandleData::CandleTimeType tf = CandleData::getType(atoi(timeFrame.c_str()) * 60);

		std::cout << "Loading: " << symbol << ":" << timeFrame << std::endl;
		std::cout << "CF: " << tf << std::endl;
		CandleData *data;

		if(istrm.is_open())
		{
			char dummybuff[256];
		
			istrm.getline(dummybuff, 256); // First line is assumed to be header
			std::vector<CandleData*> dataVec;
			while(getFileRow(istrm, data, 0, symbol,tf))
			{
				dataVec.push_back(data);
			}
			helper.fillDBData(dataVec, tf);
			std::vector<CandleData*> insertData;
			std::vector<CandleData*>::iterator insIter;
			int cnt = 0;
			for(insIter = dataVec.begin(); insIter != dataVec.end(); ++insIter)
			{
				insertData.push_back(*insIter);
				++cnt;
				if(cnt > 10000)
				{
					bulkInsertCandleData(insertData,tableName);
					cnt = 0;
				}
			}
			bulkInsertCandleData(insertData,tableName);
			dataVec.erase(dataVec.begin(), dataVec.end());
		}
		MySQLLayer::instance()->commit();
		istrm.close();
	}
}

bool CandleDataManipulation::getFileRow(std::ifstream & istrm, CandleData *& data,int adj, std::string & symbol, CandleData::CandleTimeType candleType)
{
	int jDate = 0;
	char year[5];
	if(!istrm.getline(year, 5, '.').eof())
	{
		char volume[10];
		char open[10];
		char close[10];
		char high[10];
		char low[10];
		char day[3];
		char month[3];
		char hour[3];
		char minute[3];
			
		istrm.getline(month,3,'.');
		istrm.getline(day,3,',');
		istrm.getline(hour,3,':');
		istrm.getline(minute,3,',');

		istrm.getline(open, 10,',');
		istrm.getline(high, 10, ',');
		istrm.getline(low, 10,',');
		istrm.getline(close, 10,',');
		istrm.getline(volume, 10);			

		std::string dateStr = month;
		dateStr += '/';
		dateStr += day;
		dateStr += '/';	
		dateStr += year;

		jDate = TimeZone::instance()->getJDate(dateStr);

		int openTime = (atoi(hour) *3600) + (atoi(minute) * 60); 

		//data is seven hour fast
		openTime += adj * 3600;
		if(openTime < 0)
		{
			openTime += 86400;
			jDate -= 1;
		}
		data = new CandleData(symbol,
							  atoi(volume),
							  atof(open),
							  atof(high),
							  atof(low),
							  atof(close),
							  jDate,
							  openTime,
							  candleType,
							  CandleData::INITIAL);

		return true;
	}
	return false;
}

void CandleDataManipulation::bulkDataFlush()
{
	UpdateMapIter iter;
	for(iter = updateMap_.begin(); iter != updateMap_.end(); ++iter)
	{
		const CandleData * data = (*iter).second;
		if(data->candleUpdateType_ == CandleData::UPDATE)
		{
			std::string sqlQuery = "UPDATE backtest.candledata SET vol=";
			sqlQuery += Conversions::getStrFromULong(data->volume_);
			sqlQuery += ", open=";
			sqlQuery += Conversions::getStrFromDouble(data->open_);
			sqlQuery += ", high=";
			sqlQuery += Conversions::getStrFromDouble(data->high_);
			sqlQuery += ", low=";
			sqlQuery += Conversions::getStrFromDouble(data->low_);
			sqlQuery += ",close=";
			sqlQuery += Conversions::getStrFromDouble(data->close_);
			sqlQuery += " where symbol=\"";
			sqlQuery += data->symbol_;
			sqlQuery += "\" AND timetype=";
			sqlQuery += Conversions::getStrFromULong(data->candleTimeType_);
			sqlQuery += " AND jdate=";
			sqlQuery += Conversions::getStrFromULong(data->jdate_);
			sqlQuery += " AND startTime=";
			sqlQuery += Conversions::getStrFromULong(data->startTime_);

			MySQLLayer::instance()->insertData(sqlQuery);
		}
		delete data;
	}
	updateMap_.erase(updateMap_.begin(), updateMap_.end());
}

void CandleDataManipulation::bulkSave(const CandleData* data)
{
	std::strstream strstr;
	strstr << data->symbol_ << data->candleTimeType_ << data->jdate_ << data->startTime_;
	std::string key = strstr.str();

	strstr.clear();
	strstr.rdbuf()->freeze(0);

	UpdateMapIter iter = updateMap_.find(key);
	if(iter != updateMap_.end())
	{
		delete (*iter).second;
	}
	updateMap_[key] = data;

	if(updateMap_.size() > 100)
	{
		bulkDataFlush();
	}
	MySQLLayer::instance()->commit();
}
