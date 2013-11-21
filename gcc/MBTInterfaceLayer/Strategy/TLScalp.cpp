// TLScalp.cpp: implementation of the TLScalp class.
//
//////////////////////////////////////////////////////////////////////

#include "TLScalp.h"

#include "ADXMetric.h"
#include "SlopeMetric.h"
#include "ATRMetric.h"
#include "EMAMetric.h"
#include "CorrSlopeMetric.h"
#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLScalp::TLScalp(StockWatch * stock, int SlopeBars, int ADXBars, int ATRBars, int TLTradeTime, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "TL Scalp Entry",startTradeTime, endTradeTime),
	  SlopeBars_(SlopeBars),
	  ATRBars_(ATRBars),
	  ADXBars_(ADXBars),
	  TLTradeTime_(TLTradeTime)
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
	debugPath += "TLScalpData.csv";

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
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, Slope,ATR,ADX" << std::endl;
	}
}

TLScalp::~TLScalp()
{

}

bool TLScalp::sellShort()
{
	return false;
}
bool TLScalp::buy(CandleStick * stick)
{
	if(stock_->time() < TLTradeTime_ || stock_->time() > TLTradeTime_ + 1200)
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlope(stock_->symbol(), SlopeBars_);
		double adx = getADX(stock_->symbol(),ADXBars_);
		double ema = getEMA(stock_->symbol(), 14);

		bool corrTest = false;
		int corrCount = 0;

		ConfigurationData::SymbolVec symbols = ConfigurationData::instance()->getWatchList();
		ConfigurationData::SymbolVecIter iter;
		for(iter = symbols.begin(); iter != symbols.end(); ++iter)
		{
			if(stock_->symbol() != (*iter))
			{
				CorrSlope data = getCorrSlope(stock_->symbol(), (*iter), SlopeBars_, 50);
				if((data.corr_ > .8 && data.slope_ > 0.0) || (data.corr_ < -.8 && data.slope_ < -0.0))
				{
					++corrCount;
				}
				else if((data.corr_ > .8 && data.slope_ < 0.0) || (data.corr_ < -.8 && data.slope_ > 0.0))
				{
					--corrCount;
				}
			}
		}

		if(corrCount > 0)
		{
			corrTest = true;
		}
		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << atr << ","
			   << adx << std::endl;
		if(corrTest && adx > 40.0 && atr > 5.0 * precision_ && slope > 0.0)// && ema < stick->closePrice())
		{
			std::strstream strstr;
			strstr << "\n\nTL Scalp (Long)\nClose Price: " << closePrice 
				   << "\nSlope: " << slope
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

bool TLScalp::buy()
{
	return false;
}

bool TLScalp::sellShort(CandleStick * stick)
{
	if(stock_->time() < TLTradeTime_ || stock_->time() > TLTradeTime_ + 1200)
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlope(stock_->symbol(), SlopeBars_);
		double adx = getADX(stock_->symbol(),ADXBars_);
		double ema = getEMA(stock_->symbol(), 14);


		bool corrTest = false;
		int corrCount = 0;

		ConfigurationData::SymbolVec symbols = ConfigurationData::instance()->getWatchList();
		ConfigurationData::SymbolVecIter iter;
		for(iter = symbols.begin(); iter != symbols.end(); ++iter)
		{
			if(stock_->symbol() != (*iter))
			{
				CorrSlope data = getCorrSlope(stock_->symbol(), (*iter), SlopeBars_, 50);
				if((data.corr_ > .8 && data.slope_ < 0.0) || (data.corr_ < -.8 && data.slope_ > -0.0))
				{
					++corrCount;
				}
				else if((data.corr_ > .8 && data.slope_ > 0.0) || (data.corr_ < -.8 && data.slope_ < 0.0))
				{
					--corrCount;
				}
			}
		}

		if(corrCount > 0)
		{
			corrTest = true;
		}
		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << atr << ","
			   << adx << std::endl;
		if(corrTest && adx > 40.0 && atr > 5.0 * precision_ && slope < 0.0)// && ema > stick->closePrice())
		{
			std::strstream strstr;
			strstr << "\n\nTL Scalp (Short)\nClose Price: " << closePrice 
				   << "\nSlope: " << slope
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
