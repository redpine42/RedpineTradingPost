// TimeZone.h: interface for the TimeZone class.
//
// Works with times in current time zone
//////////////////////////////////////////////////////////////////////

#ifndef TimeWrapper_h
#define TimeWrapper_h

#ifndef string_h
#include <string>
#define string_h
#endif

class TimeWrapper
{
public:
	enum TimeZoneEnum 
	{
		CET,
		GMT,
		EST,
	};

	static TimeWrapper * instance();

	virtual ~TimeWrapper();

	long convertToSecondsGMT(long seconds);
	long stringToSecondsGMT(const std::string time);
	std::string formatTZ(long seconds);
	std::string formatDateTZ(std::string & date, long seconds);

	long getSecondsLocal();

	double getUSecondsLocal();

	bool isFriday(std::string & date);
	bool isSaturday(std::string & date);
	bool isSunday(std::string & date);
	bool isMonday(std::string & date);
	long getSecondsGMT(double time);
	std::string getDateStr(long jDate);
	long getJDate(std::string & dateStr);
	long getJDate(double date);
	std::string getDate(double date);
	long getCurrentJDate();
	static TimeZoneEnum timeZoneEnum(std::string & TZ);
	static std::string timeZoneStr(TimeZoneEnum);

	static std::string getLocalDateTime();
	static std::string getLocalISODateTime();


	long getSecondsGMT();


private:
	static TimeWrapper * instance_;
	TimeWrapper();

	TimeZoneEnum timeZone_;
	static long offset_;
};

#endif 
