#ifndef CandleData_h
#define CandleData_h

#ifndef string_h
#include <string>
#define string_h
#endif

struct CandleData
{
	enum CandleTimeType
	{
		M1,
		M5,
		M15,
		M30,
		H1,
		H4,
		D1
	};

	enum CandleUpdateType
	{
		RETRIEVAL,
		UPDATE,
		NEW,
		INITIAL,
		MISSING_DATA
	};

	enum CandleValue
	{
		TIME,
		JDATE,
		OPEN,
		HIGH,
		LOW,
		CLOSE
	};

	std::string symbol_;
	unsigned long volume_;
	double open_;
	double high_;
	double low_;
	double close_;
	unsigned long jdate_;
	unsigned long startTime_;
	CandleTimeType candleTimeType_;
	CandleUpdateType candleUpdateType_;

	CandleData(){};
	CandleData(const std::string & symbol,
			   const unsigned long volume,
			   const double open,
			   const double high,
			   const double low,
			   const double close,
			   const unsigned long jdate,
			   const unsigned long startTime,
			   const CandleTimeType candleTimeType,
			   const CandleUpdateType candleUpdateType);



	static int candleTime(const CandleTimeType timeType)
	{
		switch(timeType)
		{
		case M1:
			return 60;
		case M5:
			return 300;
		case M15:
			return 900;
		case M30:
			return 1800;
		case H1:
			return 3600;
		case H4:
			return 14400;
		case D1:
			return 86400;
		default:
			return 60;
		}
	}
	static CandleTimeType getType(int time)
	{
		switch(time)
		{
		case 60:
			return M1;
		case 300:
			return M5;
		case 900:
			return M15;
		case 1800:
			return M30;
		case 3600:
			return H1;
		case 14400:
			return H4;
		case 86400:
			return D1;
		default:
			return M1;
		}
	}

	static std::string getStrType(const CandleTimeType timeType)
	{
		switch(timeType)
		{
		case M1:
			return "M1";
		case M5:
			return "M5";
		case M15:
			return "M15";
		case M30:
			return "M30";
		case  H1:
			return "H1";
		case H4:
			return "H4";
		case D1:
			return "D1";
		default:
			return "M1";
		}
	}

	static double * getData(const CandleData * data, const CandleData::CandleValue value, const long numSticks);
};
#endif
