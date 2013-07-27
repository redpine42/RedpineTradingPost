#include "TimeSalesData.h"

TimeSalesData::TimeSalesData(const std::string & symbol,
				  const unsigned long size,
				  const double price,
				  const unsigned long time,
				  const unsigned long jdate,
				  const unsigned long long seq,
				  const double timeStamp,
				  const DataEnums::TickStatus TSStatus,
				  const DataEnums::TickType TSType)
	: symbol_(symbol),
	  size_(size),
	  price_(price),
	  time_(time),
	  jdate_(jdate),
	  seq_(seq),
	  timeStamp_(timeStamp),
	  TSStatus_(TSStatus),
	  TSType_(TSType)
{
}

