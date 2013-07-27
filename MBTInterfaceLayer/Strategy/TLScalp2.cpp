// TLScalp.cpp: implementation of the TLScalp class.
//
//////////////////////////////////////////////////////////////////////

#include "TLScalp2.h"

#include "ADXMetric.h"
#include "SlopeMetric.h"
#include "ATRMetric.h"
#include "Hilbert.h"

#include "StockWatch.h"
#include "ConfigurationData.h"
#include <strstream>
#include "DataLogger.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TLScalp2::TLScalp2(StockWatch * stock, int SlopeBars, int ADXBars, int ATRBars, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "TL Scalp 2 Entry",startTradeTime, endTradeTime),
	  SlopeBars_(SlopeBars),
	  ATRBars_(ATRBars),
	  ADXBars_(ADXBars),
	  tradeState_(Waiting)
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
	debugPath += "TLScalp2Data.csv";

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
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, Slope,LongSlope,ADX" << std::endl;
	}
}

TLScalp2::~TLScalp2()
{

}

bool TLScalp2::sellShort()
{
	return false;
}

bool TLScalp2::buy(CandleStick * stick)
{
	if(!isTradingTime(stick->endTime()))
	{
		return false;
	}
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlopeVal(stock_->symbol(), SlopeBars_);
		double longSlope = getSlopeVal(stock_->symbol(), 240);
		double slopeSlope = getSlope(stock_->symbol(), 240);
		double adx = getADX(stock_->symbol(),ADXBars_);

		double phase = getPhase(stock_->symbol());
		int trend = isTrendMode(stock_->symbol());

		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << longSlope << ","
			   << adx << std::endl;
//		if(slope > longSlope && stick->closePrice() < (longSlope - 25.0 * precision_))// && ema < stick->closePrice())
		if(tradeState_ == Waiting && slopeSlope > 0.0 && getPhaseEnum(phase) == PhaseTwo && !trend)
		{
			tradeState_ = InLong;
		}
		else if (tradeState_ == InLong && (getPhaseEnum(phase) == PhaseOne || getPhaseEnum(phase) == PhaseFour))
		{
			tradeState_ = Waiting;
		}
		if(tradeState_ == InLong  && getPhaseEnum(phase) == PhaseThree)
		{
			tradeState_ = Waiting;

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

bool TLScalp2::buy()
{
	return false;
}

bool TLScalp2::sellShort(CandleStick * stick)
{
	if(!isTradingTime(stick->endTime()))
	{
		return false;
	}
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		double atr = getATR(stock_->symbol(), ATRBars_);
		double slope = getSlopeVal(stock_->symbol(), SlopeBars_);
		double longSlope = getSlopeVal(stock_->symbol(), 240);
		double slopeSlope = getSlope(stock_->symbol(), 240);
		double adx = getADX(stock_->symbol(),ADXBars_);

		double phase = getPhase(stock_->symbol());
		int trend = isTrendMode(stock_->symbol());


		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << slope << ","
			   << longSlope << ","
			   << adx << std::endl;
//		if(slope < longSlope && stick->closePrice() > longSlope + (25.0 * precision_))// && ema > stick->closePrice())
		if(tradeState_ == Waiting && slopeSlope < 0.0 && getPhaseEnum(phase) == PhaseFour && !trend)
		{
			tradeState_ = InShort;
		}
		else if (tradeState_ == InShort && (getPhaseEnum(phase) == PhaseTwo || getPhaseEnum(phase) == PhaseThree))
		{
			tradeState_ = Waiting;
		}
		if(tradeState_ == InShort  && getPhaseEnum(phase) == PhaseOne)
		{
			tradeState_ = Waiting;


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
