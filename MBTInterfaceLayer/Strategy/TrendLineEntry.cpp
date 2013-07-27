// TrendLineEntry.cpp: implementation of the TrendLineEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "TrendLineEntry.h"
#include "SlopeMetric.h"
#include "RSIMetric.h"
#include "StochMetric.h"
#include "StochRSIMetric.h"
#include "ADXMetric.h"
#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TrendLineEntry::TrendLineEntry(StockWatch * stock, int TL1Bars, int TL2Bars, int RSIBars, int StochBars,long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "Regression Slope Entry",startTradeTime, endTradeTime),
	  TL1Bars_(TL1Bars),
	  TL2Bars_(TL2Bars),
	  RSIBars_(RSIBars),
	  StochBars_(StochBars)
{
	precision_ = ConfigurationData::instance()->precision(stock->symbol());
	std::string name = stock->symbol();
	int pos = name.find("/");
	if( pos != std::string::npos)
	{
		name.replace(pos, 1, "");
	}
	std::string debugPath = ConfigurationData::instance()->logPath();
	debugPath += "\\";
	debugPath += name;
	debugPath += "TLData.csv";

	bool fileExists = false;
	std::fstream fin;
	fin.open(debugPath.c_str(),std::ios::in);
	if( fin.is_open() )
	{
		fileExists = true;
	}
	fin.close();

	debugLog_.open(debugPath.c_str(), std::ios_base::app);
	if(!fileExists)
	{
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, Slope1,Slope2" << std::endl;
	}
}

TrendLineEntry::~TrendLineEntry()
{

}

bool TrendLineEntry::sellShort()
{
	return false;
}
bool TrendLineEntry::buy(CandleStick * stick)
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();
//		int barPips = (closePrice - openPrice)/precision_;

		double slope1 = getSlope(stock_->symbol(), TL1Bars_);
		double slope2 = getSlope(stock_->symbol(), TL2Bars_);
		double rsi = getRSI(stock_->symbol(), 15);
		double adx = getADX(stock_->symbol(),15);
		double stochK = 0.0;
		double stochD = 0.0;
		getStochRSI(stock_->symbol(),RSIBars_,StochBars_, 5,stochK,stochD);


		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope1 << ","
			   << slope2 << ","
			   << rsi << ","
			   << stochK << ","
			   << stochD << ","
			   << adx << std::endl;
//		if(slope1 > slope2)
		if(slope1 > slope2 && adx > 35.0 && stochD > stochK && stochK < 35.0)
		{
			std::strstream strstr;
			strstr << "\n\nRegression Line (Long)\nClose Price: " << closePrice 
				   << "\nTL 1: " << slope1
				   << "\nTL 2: " << slope2 
				   << "\nRSI: " << rsi 
				   << "\nStoch K: " << stochK 
				   << "\nStoch D: " << stochD 
				   << "\nADX: " << adx << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}

bool TrendLineEntry::buy()
{
	return false;
}

bool TrendLineEntry::sellShort(CandleStick * stick)
{
	return false;
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();
		int barPips = (int)((closePrice - openPrice)/precision_);

		double slope1 = getSlope(stock_->symbol(), TL1Bars_);
		double slope2 = getSlope(stock_->symbol(), TL2Bars_);
		double rsi = getRSI(stock_->symbol(), 15);
		double adx = getADX(stock_->symbol(),15);
		double stochK = 0.0;
		double stochD = 0.0;
		getStochRSI(stock_->symbol(),RSIBars_,StochBars_, 5,stochK,stochD);


		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope1 << ","
			   << slope2 << ","
			   << rsi << ","
			   << stochK << ","
			   << stochD << ","
			   << adx << std::endl;
		if(slope1 < slope2 && adx > 35 && stochD < stochK && stochK > 65)
		{
			std::strstream strstr;
			strstr << "\n\nRegression Line (Short)\nClose Price: " << closePrice 
				   << "\nTL 1: " << slope1
				   << "\nTL 2: " << slope2 
				   << "\nRSI: " << rsi 
				   << "\nStoch K: " << stochK 
				   << "\nStoch D: " << stochD 
				   << "\nADX: " << adx << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);


			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}
