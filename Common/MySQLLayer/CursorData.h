#ifndef CursorData_h
#define CursorData_h

#include <winsock.h>
#include <mysql.h>


struct CursorData
{
	MYSQL_RES * resFile_;
    MYSQL_ROW rowFile_;
	long size_;

	CursorData();
	~CursorData();
	bool next();

};

#endif;
