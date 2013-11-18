#ifndef TimeSalesData_h
#define TimeSalesData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

struct TimeSalesData
{
    const std::string symbol_;
    const unsigned long size_;
    const double price_;
    const unsigned long time_;
	const unsigned long jdate_;
    const unsigned long long seq_;
	const double timeStamp_;

	const DataEnums::TickStatus TSStatus_;
	const DataEnums::TickType TSType_;

	TimeSalesData(const std::string & symbol,
				  const unsigned long size,
				  const double price,
				  const unsigned long time,
				  const unsigned long jdate,
				  const unsigned long long seq,
				  const double timestamp,
				  const DataEnums::TickStatus TSStatus,
				  const DataEnums::TickType TSType);
};

#endif
