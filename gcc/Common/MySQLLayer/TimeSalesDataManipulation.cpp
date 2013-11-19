#include "TimeSalesDataManipulation.h"
#include "MySQLLayer.h"
#include "CursorData.h"
#include "Conversions.h"
#include "TimeSalesData.h"
 
TimeSalesDataManipulation * TimeSalesDataManipulation::instance_ = 0;

TimeSalesDataManipulation * TimeSalesDataManipulation::instance()
{
	if(0 == instance_)
	{
		instance_ = new TimeSalesDataManipulation();
	}
	return instance_;
}

TimeSalesDataManipulation::TimeSalesDataManipulation()
{
}

TimeSalesDataManipulation::~TimeSalesDataManipulation()
{
	bulkDataFlush();
}

void TimeSalesDataManipulation::getTimeSalesData(std::string & symbol, std::vector<TimeSalesData*> & tsData)
{
}

void TimeSalesDataManipulation::bulkDataFlush()
{
	std::string sqlQuery = "INSERT INTO backtest.timeSalesdata (Symbol,sizeVal,price,timeval,jdate,timeStamp,tsstatus,tstype) values ";
	TimeSalesDataVecIter iter;
	for(iter = timeSalesDataVec_.begin(); iter != timeSalesDataVec_.end();)
	{
		const TimeSalesData * data = (*iter);
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
		sqlQuery += Conversions::getStrFromInt(data->TSStatus_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromInt(data->TSType_);
		sqlQuery += ")";
		if(++iter != timeSalesDataVec_.end())
		{
			sqlQuery += ",";
		}
	}
	sqlQuery += ";";
	bool result = MySQLLayer::instance()->insertData(sqlQuery);
	if(!result)
	{
		for(iter = timeSalesDataVec_.begin(); iter != timeSalesDataVec_.end(); ++iter)
		{
			const TimeSalesData * data = (*iter);
			saveTimeSalesData(data);
		}
		timeSalesDataVec_.erase(timeSalesDataVec_.begin(), timeSalesDataVec_.end());
	}
	for(iter = timeSalesDataVec_.begin(); iter != timeSalesDataVec_.end(); ++iter)
	{
		const TimeSalesData * data = (*iter);
		delete data;
	}
	timeSalesDataVec_.erase(timeSalesDataVec_.begin(), timeSalesDataVec_.end());
	MySQLLayer::instance()->commit();
}

void TimeSalesDataManipulation::getTimeSalesData(std::string & symbol, std::vector<TimeSalesData*> & tsData, DateTimeRange & dateData)
{
	std::string sqlQuery = "Select Symbol,seq,price,sizeVal,timeval,jdate,timeStamp,tsstatus,tstype From backtest.timeSalesdata where Symbol=\"";
	sqlQuery += symbol;
	sqlQuery += "\" and jdate between ";
	sqlQuery += Conversions::getStrFromULong(dateData.startJDate_);
	sqlQuery += " AND ";
	sqlQuery += Conversions::getStrFromULong(dateData.endJDate_);
	sqlQuery += " and timeVal between ";
	sqlQuery += Conversions::getStrFromULong(dateData.startTime_);
	sqlQuery += " AND ";
	sqlQuery += Conversions::getStrFromULong(dateData.endTime_);
	sqlQuery += " order by seq;";

	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
//		tsData.resize(cData->size_);

		while ( cData->next())
		{
			unsigned long long seq = atol(cData->rowFile_[1]);
			double price = atof(cData->rowFile_[3]);
			unsigned long size = atol(cData->rowFile_[2]);
			unsigned long time = atol(cData->rowFile_[4]);
			unsigned long jdate = atol(cData->rowFile_[5]);
			double timeStamp = atof(cData->rowFile_[6]);
			DataEnums::TickStatus tsstatus = (DataEnums::TickStatus)atoi(cData->rowFile_[7]);
  			DataEnums::TickType tstype = (DataEnums::TickType)atoi(cData->rowFile_[8]);

			TimeSalesData * data = new TimeSalesData(symbol, 
													 size,
													 price,
													 time,
													 jdate,
													 seq,
													 timeStamp,
													 tsstatus,
													 tstype);

			tsData.push_back(data);
		}
	}
	delete cData;
}

void TimeSalesDataManipulation::saveTimeSalesData(const TimeSalesData* data)
{
	std::string sqlQuery = "INSERT INTO backtest.timeSalesdata (Symbol,sizeVal,price,timeval,jdate,timeStamp,tsstatus,tstype) values (\"";
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
		sqlQuery += Conversions::getStrFromInt(data->TSStatus_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromInt(data->TSType_);
		sqlQuery += ")";

	MySQLLayer::instance()->insertData(sqlQuery);
	delete data;
}

void TimeSalesDataManipulation::bulkSave(const TimeSalesData* data)
{
	timeSalesDataVec_.push_back(data);
	if(timeSalesDataVec_.size() >= 1000)
	{
		bulkDataFlush();
	}
}

void TimeSalesDataManipulation::getJDates(std::vector<long> & dates)
{
	std::string sqlQuery = "Select distinct(jdate)from backtest.timeSalesdata";
	CursorData * cData = MySQLLayer::instance()->selectData(sqlQuery);
	if(cData->size_ > 0)
	{
		while ( cData->next())
		{
			unsigned long jdate = atol(cData->rowFile_[0]);

			dates.push_back(jdate);
		}
	}

}
