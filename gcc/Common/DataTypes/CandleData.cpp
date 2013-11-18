#include "CandleData.h"

CandleData::CandleData(const std::string & symbol,
			   const unsigned long volume,
			   const double open,
			   const double high,
			   const double low,
			   const double close,
			   const unsigned long jdate,
			   const unsigned long startTime,
			   const CandleTimeType candleTimeType,
			   const CandleUpdateType candleUpdateType)
	: symbol_(symbol),
	  volume_(volume),
	  open_(open),
	  high_(high),
	  low_(low),
	  close_(close),
	  jdate_(jdate),
	  startTime_(startTime),
	  candleTimeType_(candleTimeType),
	  candleUpdateType_(candleUpdateType)
{
}

double * CandleData::getData(const CandleData * data, 
							const CandleData::CandleValue value, 
							const long numSticks)
{
	double * ret = new double[numSticks];
	for(int i = 0; i < numSticks; ++i)
	{
		switch(value)
		{
		case JDATE:
			ret[i] = data[i].jdate_;
			break;
		case TIME:
			ret[i] = data[i].startTime_;
			break;
		case OPEN:
			ret[i] = data[i].open_;
			break;
		case HIGH:
			ret[i] = data[i].high_;
			break;
		case LOW:
			ret[i] = data[i].low_;
			break;
		case CLOSE:
			ret[i] = data[i].close_;
			break;
		default:
			ret[i] = 0.0;
			break;
		}
	}
	return ret;
}
