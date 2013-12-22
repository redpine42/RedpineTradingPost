#ifndef HistQuery_h
#define HistQuery_h

#ifndef CandleData_h
#include "CandleData.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

struct HistQuery
{
	double timeStart_;
	double timeEnd_;
	std::string symbol_;
	CandleData::CandleTimeType timeType_;

	IMbtHistMinBarPtr hist_;
	HistoryObserver * observer_;
	int numCandles_;
	long requestId_;
	double lastDate_;

	HistQuery()
		: timeStart_(0.0),
		  timeEnd_(0.0),
		  hist_(0),
		  observer_(0),
		  numCandles_(0),
		  requestId_(0),
		  lastDate_(0.0)
	{}
};
#endif
