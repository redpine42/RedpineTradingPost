#include "CandleDataHelper.h"
#include "CandleDataManipulation.h"
#include "RandNum.h"
#include "SymbolHelper.h"
#include <iostream>
#include <math.h>

CandleDataHelper::CandleDataHelper(void)
{
	RandNum::instance()->initializeSeed(582);
	ostrm_.open("d:\\TradeLogs\\CandleGapReport.csv");
	ostrm_ << "Symbol,Time Frame,Total Candles,Num added,Quality" << std::endl;

}

CandleDataHelper::~CandleDataHelper(void)
{
}

long CandleDataHelper::alignData(std::vector<std::string> & symbols, CandleData::CandleTimeType timeType)
{
	timeStepVal_ = CandleData::candleTime(timeType);

	std::cout << "Getting Date Range" << std::endl;
	std::vector<std::string>::iterator iter;
	for(iter = symbols.begin(); iter != symbols.end(); ++iter)
	{
		std::string symbol = (*iter);
		DateTimeRange dateData;
		CandleDataManipulation::instance()->getDateRange(symbol, timeType, dateData);
		if(dateData.startJDate_ > range_.startJDate_)
		{
			range_.startJDate_ = dateData.startJDate_;
			range_.startTime_ = dateData.startTime_;
		}
		else if(dateData.startJDate_ == range_.startJDate_ &&
			    dateData.startTime_ > range_.startTime_)
		{
			range_.startTime_ = dateData.startTime_;
		}

		if(dateData.endJDate_ < range_.endJDate_)
		{
			range_.endJDate_ = dateData.endJDate_;
			range_.endTime_ = dateData.endTime_;
		}
		else if(dateData.endJDate_ == range_.endJDate_ &&
			    dateData.endTime_ > range_.endTime_)
		{
			range_.endTime_ = dateData.endTime_;
		}
	}

	std::cout << "Getting data" << std::endl;
	for(iter = symbols.begin(); iter != symbols.end(); ++iter)
	{
		std::string symbol = (*iter);
		std::vector<CandleData*> data;
		CandleDataManipulation::instance()->getCandleData(symbol, timeType, data, range_);

		dataMap_[symbol] = data;
	}

	std::cout << "Aligning data" << std::endl;
	DataMapIter oIter;
	for(oIter = dataMap_.begin(); oIter != dataMap_.end(); ++oIter)
	{
		std::string oSymbol = (*oIter).first;
		std::vector<CandleData*> & oData = (*oIter).second;
		fillData(oData);
	}
	return dataMap_.begin()->second.size();
}

CandleData * CandleDataHelper::getAlignedData(const std::string & symbol)
{
	CandleData* data;
	DataMapIter iter;
	iter = dataMap_.find(symbol);
	if(iter != dataMap_.end())
	{
		std::vector<CandleData *>  & dataVec = (*iter).second;
		data = new CandleData[dataVec.size()];
		std::vector<CandleData *>::iterator dIter;
		long i = 0;
		for(dIter = dataVec.begin(); dIter != dataVec.end(); ++dIter, ++i)
		{
			data[i] = *(*dIter);
		}
	}
	return data;
}

void CandleDataHelper::fillData(std::vector<CandleData*> & dataVec)
{
	unsigned long curDate = range_.startJDate_;
	unsigned long curTime = range_.startTime_;
	std::vector<CandleData*>::iterator iter;

	iter = dataVec.begin();
	// Trim any front stuff
	while((*iter)->jdate_ == curDate && (*iter)->startTime_ < curTime)
	{
		iter = dataVec.erase(iter);
	}

	CandleData * curData = *dataVec.begin();
	CandleData * prevData = *dataVec.begin();
	for(iter = dataVec.begin(); iter != dataVec.end(); ++iter)
	{
		curData = (*iter);
		// data runs past the end of the range
		if(curData->jdate_ > range_.endJDate_ ||
			(curData->jdate_ == range_.endJDate_ && curData->startTime_ > range_.endTime_))
		{
			dataVec.erase(iter, dataVec.end());
			break;
		}
		while(curData->jdate_ > curDate ||
			(curData->jdate_ == curDate && curData->startTime_ > curTime))
		{
			CandleData * newData = new CandleData(*prevData);
			newData->startTime_ += timeStepVal_;
			correctForDayRollover(newData->jdate_, newData->startTime_);
			correctForEndOfWeek(newData->jdate_, newData->startTime_);

			unsigned int numMissing = countGap(prevData, curData);
			newData->high_ = getRandomStep(numMissing, prevData->high_, curData->high_);
			newData->low_ = getRandomStep(numMissing, prevData->low_, curData->low_);
			if(newData->low_ > newData->high_)
			{
				double temp = newData->low_;
				newData->low_ = newData->high_;
				newData->high_= temp;
			}
			newData->close_ = getRandomStep(numMissing, prevData->close_, curData->close_);
			newData->open_ = prevData->close_;
			iter = dataVec.insert(iter,newData);
			curData = (*iter);
		}
		prevData = curData;
		curTime += timeStepVal_;
		correctForDayRollover(curDate, curTime);
		correctForEndOfWeek(curDate, curTime);
	}
}

void CandleDataHelper::fillDBData(std::vector<CandleData*> & dataVec, CandleData::CandleTimeType timeType)
{
	int cnt = 0;
	timeStepVal_ = CandleData::candleTime(timeType);

	unsigned long curDate = (*dataVec.begin())->jdate_;
	unsigned long curTime = (*dataVec.begin())->startTime_;
	std::vector<CandleData*>::iterator iter;

	CandleData * curData = *dataVec.begin();
	CandleData * prevData = *dataVec.begin();
	std::string symbol = curData->symbol_;
	for(iter = dataVec.begin(); iter != dataVec.end(); ++iter)
	{
		curData = (*iter);
		unsigned int numMissing = countGap(prevData, curData);
		while(curData->jdate_ > curDate ||
			(curData->jdate_ == curDate && curData->startTime_ > curTime))
		{
			CandleData * newData = new CandleData(*prevData);
			newData->startTime_ += timeStepVal_;
			correctForDayRollover(newData->jdate_, newData->startTime_);
			correctForEndOfWeek(newData->jdate_, newData->startTime_);
			
			newData->high_ = getRandomStep(numMissing, prevData->high_, curData->high_);
			newData->low_ = getRandomStep(numMissing, prevData->low_, curData->low_);
			if(newData->low_ > newData->high_)
			{
				double temp = newData->low_;
				newData->low_ = newData->high_;
				newData->high_= temp;
			}
			newData->close_ = getRandomStep(numMissing, prevData->close_, curData->close_);
			newData->open_ = prevData->close_;
			newData->candleUpdateType_ = CandleData::MISSING_DATA;
			iter = dataVec.insert(iter,newData);
			++cnt;
//			newCandles.push_back(newData);
//			curData = (*iter);
			curDate = newData->jdate_;
			curTime = newData->startTime_ + timeStepVal_;
			prevData = newData;
			correctForDayRollover(curDate, curTime);
			correctForEndOfWeek(curDate, curTime);
			--numMissing;
		}
		prevData = curData;
		curTime += timeStepVal_;
		correctForDayRollover(curDate, curTime);
		correctForEndOfWeek(curDate, curTime);
	}
	std::cout << "Total Candles: " << dataVec.size() << " Num added: " << cnt << " Quality: " << 1.0 - (double)cnt/(double)dataVec.size() << std::endl;
	ostrm_ << symbol << "," << CandleData::candleTime(timeType) << "," << dataVec.size() << "," << cnt << "," << 1.0 - (double)cnt/(double)dataVec.size() << std::endl;
}

void CandleDataHelper::correctForDayRollover(unsigned long & curDate, unsigned long & curTime)
{
	// Roll over past the end of the day.
	if(curTime >= 86400)
	{
		curTime = 0;
		++curDate;
		correctForYearRollover(curDate);
	}
}

void CandleDataHelper::correctForYearRollover(unsigned long & curDate)
{
	long year = curDate/1000;
	long day = curDate - year * 1000;
	bool leapYear = (year%4) == 0;

	// Roll over past the end of the year.
	if((leapYear && day > 366) ||
	   (!leapYear && day > 365))
	{
		++year;
		day = 2;
	}
	curDate = (year * 1000) + day;
}
void CandleDataHelper::correctForEndOfWeek(unsigned long & curDate, unsigned long & curTime)
{
	// skip to sunday
/*	if(TimeZone::instance()->isFriday(TimeZone::instance()->getDateStr(curDate)) && curTime > 64800)
	{
		curTime = 64800;
		curDate += 2;
		correctForYearRollover(curDate);
	}
	*/
	// TODO:  Do we need this function.  Used for data prep in data mining program
}

unsigned int CandleDataHelper::countGap(CandleData * prevData, CandleData * curData)
{
	int ret = 0;
	unsigned long thisTime = prevData->startTime_;
	unsigned long thisDay = prevData->jdate_;
	while(thisDay < curData->jdate_ ||
		(thisDay == curData->jdate_ && thisTime < curData->startTime_))
	{
		thisTime += timeStepVal_;
		correctForDayRollover(thisDay, thisTime);
		correctForEndOfWeek(thisDay, thisTime);
		++ret;
	}
	return ret;
}

double CandleDataHelper::getRandomStep(int numSteps, double firstVal, double secondVal)
{
	int intVal = (int)firstVal;
	double step = fabs((firstVal - secondVal)/(double)numSteps);
	double ret = 0.0;
	if(firstVal < secondVal)
	{
		ret = RandNum::instance()->uniformInRange(firstVal - (1.0 * step) - intVal, firstVal + (2.0 * step) - intVal);
	}
	else
	{
		ret = RandNum::instance()->uniformInRange(firstVal - (2.0 * step) - intVal, firstVal + (1.0 * step) - intVal);
	}
	ret += (double) intVal;
	return ret;
}
