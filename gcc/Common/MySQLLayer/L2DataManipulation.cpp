#include "L2DataManipulation.h"
#include "MySQLLayer.h"
#include "CursorData.h"
#include "Conversions.h"
#include "L2Data.h"
#include "DataEnums.h"
#include "TimeZone.h"

L2DataManipulation * L2DataManipulation::instance_ = 0;

L2DataManipulation * L2DataManipulation::instance()
{
	if(0 == instance_)
	{
		instance_ = new L2DataManipulation();
	}
	return instance_;
}

L2DataManipulation::L2DataManipulation()
{
	std::string startBook = "START";
	std::string blank = "";

	L2Data * data = 
		new L2Data(startBook,
					blank,
					blank,
					DataEnums::ASK,
					0.0,
					0,
					TimeZone::instance()->getSecondsGMT(),
					TimeZone::instance()->getCurrentJDate(),
					TimeZone::instance()->getUSecondsLocal(),
					false,
					0);
	saveL2Data(data);
}

L2DataManipulation::~L2DataManipulation()
{
	bulkDataFlush();
}

void L2DataManipulation::bulkDataFlush()
{
	std::string sqlQuery = "INSERT INTO backtest.l2data (symbol,mmid,source,marketside,price,size,jdate,time,timeStamp,closed) values ";
	L2DataVecIter iter;
	for(iter = l2DataVec_.begin(); iter != l2DataVec_.end();)
	{
		const L2Data * data = (*iter);
	    sqlQuery += "(\"";
	    sqlQuery += data->symbol_;
		sqlQuery += "\",\"";
		sqlQuery += data->MMID_;
		sqlQuery += "\",\"";
		sqlQuery += data->source_;
		sqlQuery += "\",";
		sqlQuery += Conversions::getStrFromULong(data->marketSide_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->price_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->size_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->time_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->timeStamp_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromInt(data->closed_);
		sqlQuery += ")";
		if(++iter != l2DataVec_.end())
		{
			sqlQuery += ",";
		}
	}
	sqlQuery += ";";
	bool result = MySQLLayer::instance()->insertData(sqlQuery);
	if(!result)
	{
		for(iter = l2DataVec_.begin(); iter != l2DataVec_.end(); ++iter)
		{
			const L2Data * data = (*iter);
			saveL2Data(data);
		}
		l2DataVec_.erase(l2DataVec_.begin(), l2DataVec_.end());
	}
	for(iter = l2DataVec_.begin(); iter != l2DataVec_.end(); ++iter)
	{
		const L2Data * data = (*iter);
		delete data;
	}
	l2DataVec_.erase(l2DataVec_.begin(), l2DataVec_.end());
	MySQLLayer::instance()->commit();
}

void L2DataManipulation::getL2Data(std::string & symbol, std::vector<L2Data*> & l2Data)
{
}

void L2DataManipulation::getL2Data(std::string & symbol, std::vector<L2Data*> & l2Data, DateTimeRange & dateData)
{
	std::string sqlQuery = "Select Symbol,seq,mmid,source,marketside,price,size,jdate,time,timeStamp,closed From backtest.l2data where Symbol=\"";
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
//		l2Data.resize(cData->size_);

		while ( cData->next())
		{
			unsigned long long seq = atol(cData->rowFile_[1]);
			std::string mmid = cData->rowFile_[2];
			std::string source = cData->rowFile_[3];
			DataEnums::OrderSide marketside = (DataEnums::OrderSide)atoi(cData->rowFile_[4]);
			double price = atof(cData->rowFile_[5]);
			unsigned long size = atol(cData->rowFile_[6]);
			unsigned long jdate = atol(cData->rowFile_[7]);
			unsigned long time = atol(cData->rowFile_[8]);
			double timeStamp = atof(cData->rowFile_[9]);
	  		int iClosed = atoi(cData->rowFile_[10]);
			bool closed = false;
			if(iClosed > 0)
			{
				closed = true;
			}

			L2Data * data = new L2Data(symbol, 
									   mmid,
									   source,
									   marketside,
									   price,
									   size,
									   time,
									   jdate,
									   timeStamp,
									   closed,
								       seq);

			l2Data.push_back(data);
		}
	}
	delete cData;
}

void L2DataManipulation::saveL2Data(const L2Data* data)
{
	std::string sqlQuery = "INSERT INTO backtest.l2data (symbol,mmid,source,marketside,price,size,jdate,time,timeStamp,closed) values (\"";
	    sqlQuery += data->symbol_;
		sqlQuery += "\",\"";
		sqlQuery += data->MMID_;
		sqlQuery += "\",\"";
		sqlQuery += data->source_;
		sqlQuery += "\",";
		sqlQuery += Conversions::getStrFromULong(data->marketSide_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->price_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->size_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->jdate_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromULong(data->time_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromDouble(data->timeStamp_);
		sqlQuery += ",";
		sqlQuery += Conversions::getStrFromInt(data->closed_);
		sqlQuery += ")";

	MySQLLayer::instance()->insertData(sqlQuery);
	delete data;
}

void L2DataManipulation::bulkSave(const L2Data* data)
{
	l2DataVec_.push_back(data);
	if(l2DataVec_.size() >= 1000)
	{
		bulkDataFlush();
	}
}
