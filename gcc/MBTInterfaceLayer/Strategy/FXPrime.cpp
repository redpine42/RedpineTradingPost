// FXPrime.cpp: implementation of the TLScalp class.
//
//////////////////////////////////////////////////////////////////////

#include "FXPrime.h"

#include "SlopeMetric.h"
#include "ATRMetric.h"
#include "Hilbert.h"
#include "CCIMetric.h"
#include "RSIMetric.h"
#include "HACandle.h"

#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FXPrime::FXPrime(StockWatch * stock, int ATRBars, int RSIBars, int CCISlowBars, int CCIFastBars, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "FX Prime Entry",startTradeTime, endTradeTime),
	  ATRBars_(ATRBars),
	  RSIBars_(RSIBars),
	  CCISlowBars_(CCISlowBars),
	  CCIFastBars_(CCIFastBars),
	  cciFastPrev_(0.0)
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
	debugPath += "FXPrime.csv";

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
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, Slope,CCI Slow,CCI Fast, HA Open, HA High, HA Low, HA Close,RSI, CCI Fast Slope" << std::endl;
	}
}

FXPrime::~FXPrime()
{

}

bool FXPrime::sellShort()
{
	return false;
}

bool FXPrime::buy(CandleStick * stick)
{
	if(!isTradingTime(stick->endTime()))
	{
		return false;
	}
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double rsi = getRSI(stock_->symbol(), RSIBars_);
		double cciSlow = getCCI(stock_->symbol(), CCISlowBars_);
		double cciFast = getCCI(stock_->symbol(), CCIFastBars_);
		double cciFastSlope = getCCISlope(stock_->symbol(), 4);

		HACandle * haCandle = CandleStickManager::instance()->getLatestHACandleStick(stock_->symbol());
		if(0 == haCandle)
		{
			return false;
		}
		double haOpen = haCandle->openPrice();
		double haClose = haCandle->closePrice();

		double haHigh = haCandle->highPrice();
		double haLow = haCandle->lowPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlope(stock_->symbol(), 240);
		int trend = isTrendMode(stock_->symbol());

		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << cciSlow << ","
			   << cciFast << ","
			   << haOpen << ","
			   << haHigh << ","
			   << haLow << ","
			   << haClose << ","
			   << rsi << ","
			   << cciFastSlope << std::endl;
		if(cciSlow > 0.0 && cciFast > 0.0 /*&& cciFastPrev_ < 0.0 */&& rsi > 55.0 && haClose > haOpen)
		{
			std::strstream strstr;
			strstr << "\n\nFX Prime (Long)"
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << cciSlow << ","
			   << cciFast << ","
			   << haOpen << ","
			   << haHigh << ","
			   << haLow << ","
			   << haClose << ","
			   << rsi << ","
			   << cciFastSlope << std::ends;

			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());
			cciFastPrev_ = 0.0;

			return true;
		}
		cciFastPrev_ = cciFast;
	}
	return false;
}

bool FXPrime::buy()
{
	return false;
}

bool FXPrime::sellShort(CandleStick * stick)
{
	if(!isTradingTime(stick->endTime()))
	{
		return false;
	}
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double rsi = getRSI(stock_->symbol(), RSIBars_);
		double cciSlow = getCCI(stock_->symbol(), CCISlowBars_);
		double cciFast = getCCI(stock_->symbol(), CCIFastBars_);
		double cciFastSlope = getCCISlope(stock_->symbol(), 4);

		HACandle * haCandle = CandleStickManager::instance()->getLatestHACandleStick(stock_->symbol());
		if(0 == haCandle)
		{
			return false;
		}
		double haOpen = haCandle->openPrice();
		double haClose = haCandle->closePrice();
		double haHigh = haCandle->highPrice();
		double haLow = haCandle->lowPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlope(stock_->symbol(), 240);
		int trend = isTrendMode(stock_->symbol());

		if(cciSlow < 0.0 && cciFast < 0.0 /*&& cciFastPrev_ > 0.0*/ && rsi < 45.0 && haClose < haOpen)
		{
			std::strstream strstr;
			strstr << "\n\nFX Prime (Short)"
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << cciSlow << ","
			   << cciFast << ","
			   << haOpen << ","
			   << haHigh << ","
			   << haLow << ","
			   << haClose << ","
			   << rsi << ","
			   << cciFastSlope << std::ends;

			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());
			cciFastPrev_ = 0;

			return true;
		}
		cciFastPrev_ = cciFast;
	}
	return false;
}
