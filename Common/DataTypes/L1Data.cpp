#include "L1Data.h"

L1Data::L1Data(const std::string & symbol,
			    const unsigned long size,
				const double price,
				const unsigned long time,
				const unsigned long jdate,
				const unsigned long long seq,
				const double timeStamp,
				const double bid,
				const double ask,
				const unsigned long bidSize,
				const unsigned long askSize,
				const bool upTick,
				const unsigned long volume,
				const bool shortable)
	: symbol_(symbol),
	  size_(size),
	  price_(price),
	  time_(time),
	  jdate_(jdate),
	  seq_(seq),
	  timeStamp_(timeStamp),
	  bid_(bid),
	  ask_(ask),
	  bidSize_(bidSize),
	  askSize_(askSize),
	  upTick_(upTick),
	  volume_(volume),
	  shortable_(shortable)
{
}

