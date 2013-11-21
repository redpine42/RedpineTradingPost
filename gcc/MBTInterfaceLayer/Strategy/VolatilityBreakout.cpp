// VolatilityBreakout.cpp: implementation of the VolatilityBreakout class.
//
//////////////////////////////////////////////////////////////////////

#include "VolatilityBreakout.h"
#include "ATRMetric.h"
#include "EMAMetric.h"
#include "SlopeMetric.h"
#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

VolatilityBreakout::VolatilityBreakout(StockWatch * stock, int ATRBars, int EMABars, double ATRMult, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "Volatility Breakout Entry",startTradeTime, endTradeTime),
	  ATRMultiple_(ATRMult),
	  ATRBars_(ATRBars),
	  EMABars_(EMABars)
{
	precision_ = ConfigurationData::instance()->precision(stock->symbol());
}

VolatilityBreakout::~VolatilityBreakout()
{

}

bool VolatilityBreakout::sellShort()
{
	return false;
}
bool VolatilityBreakout::buy(CandleStick * stick)
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

		double slope = getSlope(stock_->symbol(), 5);

		double atr = getATR(stock_->symbol(), ATRBars_);
		double ema = getEMA(stock_->symbol(), EMABars_);
		double upperBand = ema + (atr * ATRMultiple_);

		std::strstream vbo;
		vbo << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << atr << ","
			   << ema << std::ends;
		std::string  msgvbo = vbo.str();
		vbo.clear();
		vbo.rdbuf()->freeze(0);
		
		DataLogger::instance()->recordCSVDebug(msgvbo, stock_->symbol(), "VBO");

		if(slope > 0.0 && closePrice > upperBand && atr > precision_ && ema != 0.0)
		{
			std::strstream strstr;
			strstr << "\n\nVolatility Breakout (Long)\nClose Price: " << closePrice 
				   << "\nEMA: " << ema
				   << "\nATR: " << atr
				   << "\nSlope: " << slope
				   << "\nUpper Band: " << upperBand <<std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}

bool VolatilityBreakout::buy()
{
	return false;
}

bool VolatilityBreakout::sellShort(CandleStick * stick)
{
	if(!isTradingTime(stock_->time()))
	{
		return false;
	}

	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();
		int barPips = (int)((closePrice - openPrice)/precision_);

		double slope = getSlope(stock_->symbol(), 5);

		double atr = getATR(stock_->symbol(), ATRBars_);
		double ema = getEMA(stock_->symbol(), EMABars_);
		double lowerBand = ema - (atr * ATRMultiple_);

		if(slope < 0.0 && closePrice < lowerBand && atr > precision_ && ema != 0.0)
		{
			std::strstream strstr;
			strstr << "\n\nVolatility Breakout (Short)\nClose Price: " << closePrice 
				   << "\nEMA: " << ema
				   << "\nATR: " << atr
				   << "\nSlope: " << slope
				   << "\nLower Band: " << lowerBand <<std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}
