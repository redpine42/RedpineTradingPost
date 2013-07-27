#include "CursorData.h"
#include <mysql.h>

CursorData::CursorData()
	: resFile_(0),
	  size_(0)
{
}


CursorData::~CursorData()
{
	mysql_free_result( resFile_ );
}

bool CursorData::next()
{
	return (rowFile_ = mysql_fetch_row( resFile_ )) > 0;
}
