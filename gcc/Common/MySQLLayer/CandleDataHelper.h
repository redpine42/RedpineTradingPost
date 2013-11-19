#pragma once
#include "DateTimeRange.h"
#include "CandleData.h"

#include <vector>
#include <map>
#include <fstream>

class CandleDataHelper
{
public:
	CandleDataHelper(void);
	~CandleDataHelper(void);

	long alignData(std::vector<std::string> & symbols, CandleData::CandleTimeType timeType);
	CandleData * getAlignedData(const std::string & symbol);
	void fillDBData(std::vector<CandleData*> & dataVec, CandleData::CandleTimeType timeType);

private:
	DateTimeRange range_;
	long timeStepVal_;
	
	void fillData(std::vector<CandleData*> & oData);
	void correctForDayRollover(unsigned long & curDate, unsigned long & curTime);
	void correctForYearRollover(unsigned long & curDate);
	void correctForEndOfWeek(unsigned long & curDate, unsigned long & curTime);
	unsigned int countGap(CandleData * prevData, CandleData * CurData);
	double getRandomStep(int numSteps, double firstVal, double secondVal);

	typedef std::map<std::string, std::vector<CandleData*>, std::less<std::string> > DataMap;
	typedef DataMap::iterator DataMapIter;
	std::ofstream ostrm_;

	DataMap dataMap_;
};
