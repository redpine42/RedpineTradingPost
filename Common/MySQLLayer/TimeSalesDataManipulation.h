#ifndef TimeSalesDataManipulation_h
#define TimeSalesDataManipulation_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

struct TimeSalesData;
#ifndef DateTimeRange_h
#include "DateTimeRange.h"
#endif

class TimeSalesDataManipulation
{
public:
	static TimeSalesDataManipulation * instance();

	void getTimeSalesData(std::string & symbol, std::vector<TimeSalesData*> & data, DateTimeRange & dateData);
	void getTimeSalesData(std::string & symbol, std::vector<TimeSalesData*> & data);
	void saveTimeSalesData(const TimeSalesData* data);

	void bulkSave(const TimeSalesData* data);
	void bulkDataFlush();

	void getJDates(std::vector<long> & dates);

	~TimeSalesDataManipulation();

private:
	static TimeSalesDataManipulation * instance_;
	TimeSalesDataManipulation();

	typedef std::vector<const TimeSalesData*> TimeSalesDataVec;
	typedef TimeSalesDataVec::iterator TimeSalesDataVecIter;

	TimeSalesDataVec timeSalesDataVec_;
};

#endif
