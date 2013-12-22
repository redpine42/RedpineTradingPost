#include "MySQLLayer.h"
#include <iostream>
#include <mysql.h>
#include <map>
#include "CursorData.h"
#include "Conversions.h"

#include <stdlib.h>

MySQLLayer * MySQLLayer::instance_ = new MySQLLayer();


MySQLLayer * MySQLLayer::instance()
{
    if(0 == instance_)
    {
        instance_ = new MySQLLayer();
    }
    return instance_;
}

void MySQLLayer::removeInstance()
{
    if(0 != instance_)
    {
        delete instance_;
        instance_ = 0;
    }
}

MySQLLayer::~MySQLLayer()
{
    mysql_commit(mysql_);
    mysql_close(mysql_);
}


MySQLLayer::MySQLLayer()
{
    mysql_ = new MYSQL;
    mysql_init(mysql_);
    if (!mysql_real_connect(mysql_,"localhost","dan","lostcode","backtest",3306,NULL,0))
    {
	     std::cerr << "Failed to connect to database: Error: " << mysql_error(mysql_) << std::endl;
	     errorLog_ << "Failed to connect to database: Error: " << mysql_error(mysql_) << std::endl;
    }
    mysql_commit(mysql_);
    mysql_autocommit(mysql_, 1);

	std::string fileName = "d:\\TradeLogs\\logs\\MySqlError.log";
	errorLog_.open(fileName.c_str());

}

bool MySQLLayer::connectDB(const std::string & host, const std::string & user, const std::string& password, const std::string & database)
{
    mysql_commit(mysql_);
    mysql_close(mysql_);

	mysql_ = new MYSQL;
    mysql_init(mysql_);
    if (!mysql_real_connect(mysql_,host.c_str(),user.c_str(),password.c_str(),database.c_str(),3306,NULL,0))
    {
	     std::cerr << "Failed to connect to database: Error: " << mysql_error(mysql_) << std::endl;
	     errorLog_ << "Failed to connect to database: Error: " << mysql_error(mysql_) << std::endl;
		 return false;
    }
    mysql_commit(mysql_);
	return true;
}

void MySQLLayer::commit()
{
    mysql_commit(mysql_);
}

bool MySQLLayer::insertData(std::string & insertStr)
{
	pthread_mutex_lock(&hMutex);
	int result = mysql_query( mysql_, insertStr.c_str());
    if (result)
    {
		errorLog_ << "Fail resutlt: " << Conversions::getStrFromInt(result) << std::endl;
		errorLog_ << "Query: " << insertStr << std::endl;
		pthread_mutex_unlock(&hMutex);
        return false;
	   
    }
    pthread_mutex_unlock(&hMutex);
    return true;
}

CursorData * MySQLLayer::selectData(std::string & selectStr)
{
	CursorData * cData = new CursorData();
	cData->size_ = 0;
	int result = mysql_query( mysql_, selectStr.c_str() );
	if (result) 
	{
		errorLog_ << "Fail resutlt: " << Conversions::getStrFromInt(result) << std::endl;
		errorLog_ << "Select: " << selectStr << std::endl;
	}
	else
	{
	    cData->resFile_ = mysql_store_result( mysql_ ) ;
		cData->size_ = (int) mysql_num_rows( cData->resFile_ ) ; 
	}
	return cData;
}


void MySQLLayer::dropTable(std::string schemaName, std::string tableName)
{
	std::string sqlQuery = "DROP TABLE ";
	sqlQuery += schemaName;
	sqlQuery += ".";
	sqlQuery += tableName;
	sqlQuery += ";";
	insertData(sqlQuery);
}

bool MySQLLayer::tableExists(std::string schemaName, std::string tableName)
{
    MYSQL_RES * resFile = 0;
    MYSQL_ROW row;

	std::string sqlQuery = "SELECT COUNT(*) FROM information_schema.tables WHERE table_schema = ";
	sqlQuery += schemaName;
	sqlQuery += " AND table_name = ";
	sqlQuery += tableName;
	sqlQuery += ";";
	bool ret = false;
	if (!mysql_query( mysql_, sqlQuery.c_str() ) ) 
	{
	    resFile = mysql_store_result( mysql_ ) ;
		int i = (int) mysql_num_rows( resFile ) ; 

	    while ( row = mysql_fetch_row( resFile ) )
		{
			if(atoi(row[0]) > 0)
			{
				ret = true;
			}
		}
	}
	mysql_free_result(resFile);
	return ret;
}


