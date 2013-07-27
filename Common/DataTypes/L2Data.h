#ifndef L2Data_h
#define L2Data_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef DataEnums_h
#include "DataEnums.h"
#endif

struct L2Data
{
    const std::string symbol_;
	const std::string MMID_;
	const std::string source_;
	const DataEnums::OrderSide marketSide_;
	const double price_;
	const unsigned long size_;

    const unsigned long time_;
    const unsigned long jdate_;
	const bool closed_;
	const unsigned long long seq_;
	const double timeStamp_;

	L2Data(const std::string & symbol,
		   const std::string & MMID,
		   const std::string & source,
		   const DataEnums::OrderSide marketSide,
		   const double price,
	       const unsigned long size,
		   const unsigned long time,
		   const unsigned long jdate,
		   const double timestamp,
		   const bool closed,
		   const unsigned long long seq);

};

#endif
