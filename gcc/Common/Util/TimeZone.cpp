// TimeZone.cpp: implementation of the TimeZone class.
//
//////////////////////////////////////////////////////////////////////
//
#define VC_EXTRALEAN
#define _WIN32_WINNT 0x0600

#include <afxwin.h>         // MFC core and standard components
#include <afxdisp.h>        // MFC Automation classes

#include <strstream>
#include <iomanip>

#include "TimeZone.h"
#include <time.h>
#include <sys/timeb.h>

#include <stdlib.h>
#include <stdio.h>
#include "Time.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TimeZone * TimeZone::instance_ = 0;
short TimeZone::offset_ = 0;

TimeZone::TimeZone()
{
	timeZone_ = EST;
}


TimeZone::~TimeZone()
{

}

TimeZone * TimeZone::instance()
{
	if(0 == instance_)
	{
		instance_ = new TimeZone();
		time_t ltime;
		time(&ltime);

		tm* tstruct = localtime(&ltime);
		
		long adj = 0;
		std::string tzName = _tzname[0];
		if(tstruct->tm_isdst)
		{
			tzName = _tzname[1];
			adj = _dstbias;
		}
		offset_ = (_timezone + adj)/3600;
	}
	return instance_;
}


std::string TimeZone::formatTZ(long seconds)
{
	int hours = 0;
	int minutes = 0;
	int sec = 0;
	
	if(seconds > 1.0)
	{
		hours = seconds/3600;
		minutes = (seconds - (hours * 3600))/60;
		sec = seconds %60;

	}
	
	hours -= offset_;
	if(hours >= 24)
	{
		hours = hours - 24;
	}
	else if (hours < 0)
	{
		hours = hours + 24;
	}
	

    std::strstream strstr;
	strstr.fill('0');
    strstr << std::setw(2) << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2) << sec << std::ends;
	std::string  ret = strstr.str();
    strstr.clear();
    strstr.rdbuf()->freeze(0);
	return ret;
}

long TimeZone::convertToSecondsGMT(long seconds)
{
	long gmtSeconds = seconds;

	seconds += (offset_ * 3600);
	if(seconds >= 86400)
	{
		seconds = seconds - 86400;
	}
	else if (seconds < 0)
	{
		seconds = seconds + 86400;
	}
	return seconds;
}

long TimeZone::getSecondsGMT(double time)
{
	COleDateTime datetime = COleDateTime(time);

    long timeVal = datetime.GetSecond();
    timeVal += 3600*datetime.GetHour();
    timeVal += 60*datetime.GetMinute();

	return timeVal;
}

long TimeZone::getSecondsGMT()
{
	time_t ltime;
	time(&ltime);

	tm* tstruct = gmtime(&ltime);
	int seconds = tstruct->tm_sec;
	int minutes = tstruct->tm_min;
	int hours = tstruct->tm_hour;
	int dayOfWeek = tstruct->tm_wday;

	return (hours * 3600) + (minutes * 60) + seconds;
}
bool TimeZone::isFriday(std::string & date)
{
	COleDateTime datetime;
	datetime = COleDateTime::GetCurrentTime();

	size_t pos = 0;

	pos = date.find('/');
	size_t firstPos = pos;
	std::string monthStr = date.substr(0,pos);
	pos = date.find('/', pos+1);
	std::string dayStr = date.substr(firstPos+1, pos-(firstPos+1));
	std::string yearStr = date.substr(pos+1);

	int month = atoi(monthStr.c_str());
	int day = atoi(dayStr.c_str());
	int year = atoi(yearStr.c_str());

	datetime.SetDate(year,month,day);
	int dayOfWeek = datetime.GetDayOfWeek();
	return dayOfWeek == 6;
}

bool TimeZone::isSaturday(std::string & date)
{
	COleDateTime datetime;
	datetime = COleDateTime::GetCurrentTime();

	size_t pos = 0;

	pos = date.find('/');
	size_t firstPos = pos;
	std::string monthStr = date.substr(0,pos);
	pos = date.find('/', pos+1);
	std::string dayStr = date.substr(firstPos+1, pos-(firstPos+1));
	std::string yearStr = date.substr(pos+1);

	int month = atoi(monthStr.c_str());
	int day = atoi(dayStr.c_str());
	int year = atoi(yearStr.c_str());

	datetime.SetDate(year,month,day);
	int dayOfWeek = datetime.GetDayOfWeek();
	return dayOfWeek == 7;
}

bool TimeZone::isSunday(std::string & date)
{
	COleDateTime datetime;
	datetime = COleDateTime::GetCurrentTime();

	size_t pos = 0;

	pos = date.find('/');
	size_t firstPos = pos;
	std::string monthStr = date.substr(0,pos);
	pos = date.find('/', pos+1);
	std::string dayStr = date.substr(firstPos+1, pos-(firstPos+1));
	std::string yearStr = date.substr(pos+1);

	int month = atoi(monthStr.c_str());
	int day = atoi(dayStr.c_str());
	int year = atoi(yearStr.c_str());

	datetime.SetDate(year,month,day);
	int dayOfWeek = datetime.GetDayOfWeek();
	return dayOfWeek == 1;
}
bool TimeZone::isMonday(std::string & date)
{
	COleDateTime datetime;
	datetime = COleDateTime::GetCurrentTime();

	size_t pos = 0;

	pos = date.find('/');
	size_t firstPos = pos;
	std::string monthStr = date.substr(0,pos);
	pos = date.find('/', pos+1);
	std::string dayStr = date.substr(firstPos+1, pos-(firstPos+1));
	std::string yearStr = date.substr(pos+1);

	int month = atoi(monthStr.c_str());
	int day = atoi(dayStr.c_str());
	int year = atoi(yearStr.c_str());

	datetime.SetDate(year,month,day);
	int dayOfWeek = datetime.GetDayOfWeek();
	return dayOfWeek == 2;
}

long TimeZone::getSecondsLocal()
{
	time_t ltime;
	time(&ltime);

	tm* tstruct = localtime(&ltime);
	int seconds = tstruct->tm_sec;
	int minutes = tstruct->tm_min;
	int hours = tstruct->tm_hour;

	return (hours * 3600) + (minutes * 60) + seconds;
}

double TimeZone::getUSecondsLocal()
{
    struct _timeb tstruct;
    _ftime_s( &tstruct ); 

	double uTime = getSecondsLocal();
	return uTime + ((double)tstruct.millitm/1000.0);
}

// local time Julian Date
long TimeZone::getCurrentJDate()
{
	COleDateTime datetime;
	datetime = COleDateTime::GetCurrentTime();

	long jDate = datetime.GetYear() * 1000;
	jDate += datetime.GetDayOfYear();

	return jDate;
}

std::string TimeZone::getDate(double date)
{
	long jDate = getJDate(date);
	return getDateStr(jDate);
}

long TimeZone::getJDate(double date)
{
	COleDateTime datetime = COleDateTime(date);
	long jDate = datetime.GetYear() * 1000;
	jDate += datetime.GetDayOfYear();

	return jDate;
}


long TimeZone::getJDate(std::string & dateStr)
{
	long day = 0;
	size_t pos = 0;

	pos = dateStr.find('/');
	size_t firstPos = pos;
	std::string monthStr = dateStr.substr(0,pos);
	pos = dateStr.find('/', pos+1);
	std::string dayStr = dateStr.substr(firstPos+1, pos-(firstPos+1));
	std::string yearStr = dateStr.substr(pos+1);

	int month = atoi(monthStr.c_str());
	int days = atoi(dayStr.c_str());
	int year = atoi(yearStr.c_str());

	long rem = year%4;
	long leapDay = 0;
	if(rem == 0)
	{
		leapDay = 1;
	}

	switch (month)
	{
	case 1:
	{
		day = days;
		break;
	}
	case 2:
	{
		day = days + 31;
		break;
	}
	case 3:
	{
		day = days + 59 + leapDay;
		break;
	}
	case 4:
	{
		day = days + 90 + leapDay;
		break;
	}
	case 5:
	{
		day = days + 120 + leapDay;
		break;
	}
	case 6:
	{
		day = days + 151 + leapDay;
		break;
	}
	case 7:
	{
		day = days + 181 + leapDay;
		break;
	}
	case 8:
	{
		day = days + 212 + leapDay;
		break;
	}
	case 9:
	{
		day = days + 243 + leapDay;
		break;
	}
	case 10:
	{
		day = days + 273 + leapDay;
		break;
	}
	case 11:
	{
		day = days + 304 + leapDay;
		break;
	}
	case 12:
	{
		day = days + 334 + leapDay;
		break;
	}
	}

	long jDate = year * 1000;
	jDate += day;

	return jDate;
}

std::string TimeZone::getDateStr(long jDate)
{
	long year = jDate/1000;
	long days = jDate - (year * 1000);

	long rem = year%4;
	long leapDay = 0;
	if(rem == 0)
	{
		leapDay = 1;
	}

	long month = 0;
	long day = 0;

	if(days <= 31)
	{
		month = 1;
		day = days;
	}
	else if(days <= 59 + leapDay)
	{
		month = 2;
		day = days - 31;
	}
	else if(days <= 90 + leapDay)
	{
		month = 3;
		day = days - 59 - leapDay;
	}
	else if(days <= 120 + leapDay)
	{
		month = 4;
		day = days - 90 - leapDay;
	}
	else if(days <= 151 + leapDay)
	{
		month = 5;
		day = days - 120 - leapDay;
	}
	else if(days <= 181 + leapDay)
	{
		month = 6;
		day = days - 151 - leapDay;
	}
	else if(days <= 212 + leapDay)
	{
		month = 7;
		day = days - 181 - leapDay;
	}
	else if(days <= 243 + leapDay)
	{
		month = 8;
		day = days - 212 - leapDay;
	}
	else if(days <= 273 + leapDay)
	{
		month = 9;
		day = days - 243 - leapDay;
	}
	else if(days <= 304 + leapDay)
	{
		month = 10;
		day = days - 273 - leapDay;
	}
	else if(days <= 334 + leapDay)
	{
		month = 11;
		day = days - 304 - leapDay;
	}
	else if(days <= 365 + leapDay)
	{
		month = 12;
		day = days - 334 - leapDay;
	}
    std::strstream strstr;
	strstr << month << "/" << day << "/" << year << std::ends;
	std::string  date = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return date;
}

std::string TimeZone::formatDateTZ(std::string & date, long seconds)
{
	long jDate = getJDate(date);

	int hours = 0;
	int minutes = 0;
	int sec = 0;
	
	if(seconds > 1.0)
	{
		hours = seconds/3600;
		minutes = (seconds - (hours * 3600))/60;
		sec = seconds %60;

	}
	
	hours -= offset_;
	if(hours >= 24)
	{
		++jDate;
	}
	else if (hours < 0)
	{
		--jDate;
	}
	return getDateStr(jDate);
}



TimeZone::TimeZoneEnum TimeZone::timeZoneEnum(std::string & TZ)
{
	if(TZ == "CET")
	{
		return CET;
	}
	else if(TZ == "EST")
	{
		return EST;
	}
	return GMT;
}

std::string TimeZone::timeZoneStr(TimeZoneEnum TZ)
{
	if(TZ == CET)
	{
		return "CET";
	}
	else if(TZ == EST)
	{
		return "EST";
	}
	return "GMT";
}


long TimeZone::stringToSecondsGMT(const std::string time)
{
	long lTime = 0;
	size_t pos = 0;

	pos = time.find(':');
	size_t firstPos = pos;
	std::string hourStr = time.substr(0,pos);
	pos = time.find(':', pos+1);
	std::string minuteStr = time.substr(firstPos+1, pos-(firstPos+1));
	std::string secondStr = time.substr(pos+1);
	
	int seconds = atoi(hourStr.c_str()) * 3600 + atoi(minuteStr.c_str()) * 60 + atoi(secondStr.c_str());

	return convertToSecondsGMT(seconds);
}

