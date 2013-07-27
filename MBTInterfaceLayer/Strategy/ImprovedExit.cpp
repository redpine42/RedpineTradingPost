// ImprovedExit.cpp: implementation of the ImprovedExit class.
//
//////////////////////////////////////////////////////////////////////

#include "ImprovedExit.h"
#include <strstream>

#include "ATRMetric.h"
#include "CandleStickManager.h"
#include "CandleStick.h"
#include "StockWatch.h"
#include "StockWatchList.h"
#include "PurchaseData.h"
#include "DataLogger.h"
#include "ConfigurationData.h"
#include "AnalysisManager.h"
#include "Recomendation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ImprovedExit::ImprovedExit(std::string symbol, int atrBars, int timeExit, double mmstp, double ptlim, double stpa, double stpb, double ptga, long startTime, long endTime)
	: ExitStrategy("Improved Exit Strategy", startTime, endTime),
	  firstTest_(true),
	  stopLoss_(0.0),
	  takeProfit_(0.0),
	  ATRBars_(atrBars),
	  timeExit_(timeExit),
	  mmstp_(mmstp),
	  ptlim_(ptlim),
	  stpa_(stpa),
	  stpb_(stpb),
	  ptga_(ptga),
	  lastTime_(0)
{
	seconds_ = (long)CandleStickManager::instance()->seconds();
	precision_ = ConfigurationData::instance()->precision(symbol);
}

ImprovedExit::~ImprovedExit()
{

}

bool ImprovedExit::sell(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	if(0 == stock->openData())
	{
		return false;
	}
	CandleStick * cb = CandleStickManager::instance()->getLatestCandleStick(symbol);
	long cbStartTimeTime = cb->startTime();

	long startTime = stock->openData()->timeFilled();

	if(!tradeTime())
	{
		if(TimeZone::instance()->isFriday())
		{
			firstTest_ = true;
			reason_ = "Time Expired (End of Week)";
			return true;
		}
	}
	if(stock->time() > startTime + timeExit_)
	{
		firstTest_ = true;
		reason_ = "Time Expired (Limit)";
		return true;
	}

	double atr = getATR(symbol, ATRBars_);
	if(atr == 0.0)
	{
		atr = .0005;
	}

	if(firstTest_)
	{
		firstTest_ = false;
		takeProfit_ = openPrice + (ptlim_ * atr);
		stopLoss_ = openPrice - (mmstp_ * atr);
		lastTime_ = cbStartTimeTime;

	    std::strstream strstr;
		strstr << symbol << "," 
			   << "First Setting" << ","
			   << TimeZone::instance()->formatDateTZ(cb->date(), cb->endTime()) << " " << TimeZone::instance()->formatTZ(cb->endTime()) << ","
			   << cb->openPrice() << "," 
			   << cb->highPrice() << "," 
			   << cb->lowPrice() << "," 
			   << cb->closePrice() << "," 
			   << stopLoss_ << "," 
			   << takeProfit_ << std::ends;
		std::string  msg = strstr.str();
		strstr.clear();
	    strstr.rdbuf()->freeze(0);
		DataLogger::instance()->recordCSVDebug(msg, symbol, "IE");

		DataLogger::instance()->recordDebug(msg, symbol);
	}
	else if((price >= takeProfit_ || (price <= stopLoss_)  || price >= openPrice + (150.0 * precision_) || price <= openPrice - (120.0 * precision_)))
	{
		firstTest_ = true;
		return true;
	}

	if(cbStartTimeTime != lastTime_)
	{
		double tmp = cb->highPrice() - (stpa_ * atr) - stopLoss_;
		if(tmp > 0.0)
		{
			stopLoss_ += stpb_ * tmp;
		}
		takeProfit_ = takeProfit_ - (ptga_ * (takeProfit_ - cb->closePrice()));
		lastTime_ = cbStartTimeTime;

		if(stopLoss_ > cb->closePrice())
		{
			stopLoss_ = cb->closePrice();
		}
		else if(takeProfit_ < cb->closePrice())
		{
			takeProfit_ = cb->closePrice();
		}
//		if(cb->closePrice() > openPrice + (20.0 * precision_))
//		{
//			stopLoss_ = stopLoss_ + (.1 * atr);;
//		}
	    std::strstream strstr;
		strstr << symbol << "," 
			   << "Update Settings" << ","
			   << TimeZone::instance()->formatDateTZ(cb->date(), cb->endTime()) << " " << TimeZone::instance()->formatTZ(cb->endTime()) << ","
			   << cb->openPrice() << "," 
			   << cb->highPrice() << "," 
			   << cb->lowPrice() << "," 
			   << cb->closePrice() << "," 
			   << stopLoss_ << "," 
			   << takeProfit_ << std::ends;
		std::string  msg = strstr.str();
		strstr.clear();
	    strstr.rdbuf()->freeze(0);
		DataLogger::instance()->recordCSVDebug(msg, symbol, "IE");

		DataLogger::instance()->recordDebug(msg, symbol);
	}


	return false;
}

bool ImprovedExit::buyToCover(const std::string & symbol, const double openPrice, const double price)
{
	StockWatch * stock = StockWatchList::instance()->getStockWatch(symbol);
	if(0 == stock->openData())
	{
		return false;
	}
	CandleStick * cb = CandleStickManager::instance()->getLatestCandleStick(symbol);
	long cbStartTimeTime = cb->startTime();

	long startTime = stock->openData()->timeFilled();

	if(!tradeTime())
	{
		if(TimeZone::instance()->isFriday())
		{
			firstTest_ = true;
			reason_ = "Time Expired (End of Week)";
			return true;
		}
	}
  	if(stock->time() > startTime + timeExit_)
	{
		firstTest_ = true;
		reason_ = "Time Expired (Limit)";
		return true;
	}

	double atr = getATR(symbol, ATRBars_);
	if(atr == 0.0)
	{
		atr = .0005;
	}

	if(firstTest_)
	{
		firstTest_ = false;
		takeProfit_ = openPrice - (ptlim_ * atr);
		stopLoss_ = openPrice + (mmstp_ * atr);
		lastTime_ = cbStartTimeTime;

	    std::strstream strstr;
		strstr << symbol << "," 
			   << "First Setting" << ","
			   << TimeZone::instance()->formatDateTZ(cb->date(), cb->endTime()) << " " << TimeZone::instance()->formatTZ(cb->endTime()) << ","
			   << cb->openPrice() << "," 
			   << cb->highPrice() << "," 
			   << cb->lowPrice() << "," 
			   << cb->closePrice() << "," 
			   << stopLoss_ << "," 
			   << takeProfit_ << std::ends;
		std::string  msg = strstr.str();
		strstr.clear();
	    strstr.rdbuf()->freeze(0);
		DataLogger::instance()->recordCSVDebug(msg, symbol, "IE");

		DataLogger::instance()->recordDebug(msg, symbol);
	}
	else if((price <= takeProfit_ || (price >= stopLoss_) || price <= openPrice - (150.0 * precision_) || price >= openPrice + (120.0 * precision_)))
	{
		firstTest_ = true;
		return true;
	}
	
	if(cbStartTimeTime != lastTime_)
	{
		double tmp = cb->lowPrice() + (stpa_ * atr) - stopLoss_;
		if(tmp < 0.0)
		{
			stopLoss_ += stpb_ * tmp;
		}
		takeProfit_ = takeProfit_ + (ptga_ * (cb->closePrice() - takeProfit_));
		lastTime_ = cbStartTimeTime;

		if(stopLoss_ < cb->closePrice())
		{
			stopLoss_ = cb->closePrice();
		}
		else if(takeProfit_ > cb->closePrice())
		{
			takeProfit_ = cb->closePrice();
		}
//		if(cb->closePrice() < openPrice - (20.0 * precision_))
//		{
//			stopLoss_ = stopLoss_ - (.1 * atr);
//		}
	    std::strstream strstr;
		strstr << symbol << "," 
			   << "Update Settings" << ","
			   << TimeZone::instance()->formatDateTZ(cb->date(), cb->endTime()) << " " << TimeZone::instance()->formatTZ(cb->endTime()) << ","
			   << cb->openPrice() << "," 
			   << cb->highPrice() << "," 
			   << cb->lowPrice() << "," 
			   << cb->closePrice() << "," 
			   << stopLoss_ << "," 
			   << takeProfit_ << std::ends;
		std::string  msg = strstr.str();
		strstr.clear();
	    strstr.rdbuf()->freeze(0);
		DataLogger::instance()->recordCSVDebug(msg, symbol, "IE");

		DataLogger::instance()->recordDebug(msg, symbol);
	}

	return false;
}


