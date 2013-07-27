#include "L2Data.h"

L2Data::L2Data(const std::string & symbol,
		   const std::string & MMID,
		   const std::string & source,
		   const DataEnums::OrderSide marketSide,
		   const double price,
	       const unsigned long size,
		   const unsigned long time,
		   const unsigned long jdate,
		   const double timeStamp,
		   const bool closed,
		   const unsigned long long seq)
	: symbol_(symbol),
	  MMID_(MMID),
	  source_(source),
	  marketSide_(marketSide),
	  price_(price),
	  size_(size),
      time_(time),
      jdate_(jdate),
	  timeStamp_(timeStamp),
	  closed_(closed),
	  seq_(seq)
{

}
