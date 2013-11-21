// EMAScalp.cpp: implementation of the EMAScalp class.
//
//////////////////////////////////////////////////////////////////////

#include "EMAScalp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// TrendLineEntry.cpp: implementation of the TrendLineEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "EMAScalp.h"
#include "ADXMetric.h"
#include "EMAMetric.h"
#include "ATRMetric.h"
#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EMAScalp::EMAScalp(StockWatch * stock, int EMABars, int ADXBars, int ATRBars, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "EMA Scalp Entry",startTradeTime, endTradeTime),
	  EMABars_(EMABars),
	  ATRBars_(ATRBars),
	  ADXBars_(ADXBars)
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
	debugPath += "EMAData.csv";

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
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, EMA,ATR,ADX" << std::endl;
	}
}

EMAScalp::~EMAScalp()
{

}

bool EMAScalp::sellShort()
{
	return false;
}
bool EMAScalp::buy(CandleStick * stick)
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double ema = getEMA(stock_->symbol(), EMABars_);
		double adx = getADX(stock_->symbol(),ADXBars_);


		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << ema << ","
			   << atr << ","
			   << adx << std::endl;
		if(adx > 35.0 && atr > 5.0 * precision_ && ema > closePrice)
		{
			std::strstream strstr;
			strstr << "\n\nEMA Scalp (Long)\nClose Price: " << closePrice 
				   << "\nEMA: " << ema
				   << "\nADX: " << adx 
				   << "\nATR: " << atr  << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}

bool EMAScalp::buy()
{
	return false;
}

bool EMAScalp::sellShort(CandleStick * stick)
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double ema = getEMA(stock_->symbol(), EMABars_);
		double adx = getADX(stock_->symbol(),ADXBars_);


		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << ema << ","
			   << atr << ","
			   << adx << std::endl;
		if(adx > 35.0 && atr > 5.0 * precision_ && ema < closePrice)
		{
			std::strstream strstr;
			strstr << "\n\nEMA Scalp (Long)\nClose Price: " << closePrice 
				   << "\nEMA: " << ema
				   << "\nADX: " << adx 
				   << "\nATR: " << atr  << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}
