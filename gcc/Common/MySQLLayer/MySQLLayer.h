#pragma once
#include "CursorData.h"
#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#include <fstream>

#include <mysql.h>
#include <pthread.h>



class MySQLLayer
{
public:
    static MySQLLayer * instance();
    static void removeInstance();
	bool connectDB(const std::string & host, const std::string & user, const std::string& password, const std::string & database);
    void commit();

	bool tableExists(std::string schemaName, std::string tableName);
	void dropTable(std::string schemaName, std::string tableName);

	bool insertData(std::string & insertStr);
	CursorData * selectData(std::string & selectStr);

private:
	pthread_mutex_t hMutex;
    static MySQLLayer * instance_;
	virtual ~MySQLLayer(void);

	MySQLLayer(void);
    MYSQL * mysql_;

    std::ofstream errorLog_;
};



