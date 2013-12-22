#ifndef L1Data_h
#define L1Data_h

#ifndef string_h
#include <string>
#define string_h
#endif

struct L1Data
{
    const std::string symbol_;
    const unsigned long size_;
    const double price_;
    const unsigned long time_;
	const unsigned long jdate_;
    const unsigned long long seq_;

    const  double bid_;
    const  double ask_;
    const unsigned long bidSize_;
    const unsigned long askSize_;
    const bool upTick_;
    const unsigned long volume_;
	const bool shortable_;
	const double timeStamp_;

	L1Data(const std::string & symbol_,
			    const unsigned long size_,
				const double price_,
				const unsigned long time_,
				const unsigned long jdate_,
				const unsigned long long seq_,
				const double timestamp,
				const double bid_,
				const double ask_,
				const unsigned long bidSize_,
				const unsigned long askSize_,
				const bool upTick_,
				const unsigned long volume_,
				const bool shortable_);

};

#endif
