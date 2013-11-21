// COTLEntry.cpp: implementation of the COTLEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "COTLEntry.h"

#include <strstream>

#include "PurchaseData.h"
#include "ConfigurationData.h"
#include "CandleStickManager.h"
#include "CandleStick.h"

#include "DataLogger.h"
#include "ErrorLog.h"
#include "SlopeMetric.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COTLEntry::COTLEntry(StockWatch * stock,
		      long firstEntrySignalTime,
			  long TLStartTime,
			  long TLEndTime, long startTradeTime, long endTradeTime)
	: EntryStrategy(stock, "COTL Entry", startTradeTime, endTradeTime),
	  transactions_(0),
	  numSticks_(0),
	  numTradesPerStick_(0),
	  tradeType_(PurchaseData::NoTrade),
	  belowTL_(true),
	  lastTickInPosition_(false),
	  baseTLTime_(0),
	  baseTLPrice_(0.0),
	  rateOfChange_(0.0),
	  numReversals_(0),
	  TLCrossTrading_(true),
	  tlrSlope_(0.0),
	  priceTime_(firstEntrySignalTime),
	  TLStartTime_(TLStartTime),
	  TLEndTime_(TLEndTime)
{
	TLCrossTrading_ = ConfigurationData::instance()->TLCrossTrading();
	ReverseTrading_ = ConfigurationData::instance()->reverseTrading();	

}

COTLEntry::~COTLEntry()
{

}

bool COTLEntry::buy()
{
	// buy conditions checked before sell. So just check once here
	if(CandleStickManager::instance()->numSticks(stock_->symbol()) > numSticks_)
	{
		numSticks_ = CandleStickManager::instance()->numSticks(stock_->symbol());
		reset();
	}

	if(numTradesPerStick_ == 2)
	{
		return false;
	}

	double expectedTLPrice = baseTLPrice_ + ((stock_->time() - baseTLTime_) * rateOfChange_);

	if(isTradingTime(stock_->time()))
	{
		if(transactions_ == 0)
		{
			CandleStick * stick = CandleStickManager::instance()->getCandleStick(stock_->symbol());
			if(0.0 == rateOfChange_)
			{
				if(!setTrendLine())
				{
					return false;
				}
			}
			
			bool triggerLong = false;
			if(ConfigurationData::instance()->trendLineOpenPosition())
			{

				triggerLong = rateOfChange_ > 0.0;
			}
			else
			{
				triggerLong = stick->openPrice() <= stock_->getLastPrice();
			}
	
			if(0 != stick &&
				stock_->time() >= priceTime_ && 
				triggerLong)
			{
				reason("First Entry Signal");
				++transactions_;
				++numTradesPerStick_;
				tradeType_ = PurchaseData::Buy;

				DataLogger::instance()->recordDebug(stock_->getLevel1Data());
				lastTickInPosition_ = true;
				numReversals_ = 0;
				return true;
			}
		}
		else if(ReverseTrading_ && tradeType_ == PurchaseData::SellShort &&
			    numReversals_ == 0 &&
				numTradesPerStick_ < 2 &&
				!stock_->tradeSuccess())
		{
			reason("Reverse position");
			++transactions_;
			++numTradesPerStick_;
			tradeType_ = PurchaseData::Buy;

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
			lastTickInPosition_ = true;
			++numReversals_;
			return true;
		}
		else if(TLCrossTrading_ && belowTL_ && 
			    numTradesPerStick_ < 2 &&
				!lastTickInPosition_ &&
				stock_->bestAsk() > expectedTLPrice  && stock_->bestAsk() != 0.0)
		{
			belowTL_ = false;
			reason("Transition Above Trend Line");
			++transactions_;
			++numTradesPerStick_;
			tradeType_ = PurchaseData::Buy;

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
			lastTickInPosition_ = true;
			numReversals_ = 0;
			return true;
		}
//		lastTickInPosition_ = false;
	}
	if(stock_->bestAsk() > expectedTLPrice && stock_->bestAsk() != 0.0)
	{
		belowTL_ = false;
	}

	return false;
}

bool COTLEntry::sellShort()
{
	if(numTradesPerStick_ == 2)
	{
		return false;
	}

	double expectedTLPrice = baseTLPrice_ + ((stock_->time() - baseTLTime_) * rateOfChange_);

	if(isTradingTime(stock_->time()))
	{
		if(transactions_ == 0)
		{
			CandleStick * stick = CandleStickManager::instance()->getCandleStick(stock_->symbol());
			if(0.0 == rateOfChange_)
			{
				if(!setTrendLine())
				{
					return false;
				}
			}

			bool triggerShort = false;
			if(ConfigurationData::instance()->trendLineOpenPosition())
			{
				triggerShort = rateOfChange_ < 0.0;
			}
			else
			{
				triggerShort = stick->openPrice() > stock_->getLastPrice();
			}
			if(0 != stick &&
				stock_->time() >= priceTime_ && 
				triggerShort)
			{
				reason("First Entry Signal");
				++transactions_;
				++numTradesPerStick_;
			    tradeType_ = PurchaseData::SellShort;

				DataLogger::instance()->recordDebug(stock_->getLevel1Data());
				lastTickInPosition_ = true;
				numReversals_ = 0;
				return true;
			}
		}
		else if(ReverseTrading_ && tradeType_ == PurchaseData::Buy &&
			    numReversals_ == 0 &&
				numTradesPerStick_ < 2 &&
				!stock_->tradeSuccess())
		{
			reason("Reverse position");
			++transactions_;
			++numTradesPerStick_;
			tradeType_ = PurchaseData::SellShort;

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
			lastTickInPosition_ = true;
			++numReversals_;
			return true;
		}
		else if(TLCrossTrading_ && !belowTL_ && 
			    numTradesPerStick_ < 2 &&
				!lastTickInPosition_ &&
			    stock_->bestBid() < expectedTLPrice  && stock_->bestBid() != 0.0)
		{
			belowTL_ = true;
			reason("Transition Below Trend Line");
			++transactions_;
			++numTradesPerStick_;
		    tradeType_ = PurchaseData::SellShort;

			DataLogger::instance()->recordDebug(stock_->getLevel1Data());
			lastTickInPosition_ = true;
			numReversals_ = 0;
			return true;
		}
		// value is used by both long and short positions.  It should only be reset after both have
		// checked their code to check the trendline.  Since buys are checked before shorts,
		// this value is set here.
		lastTickInPosition_ = false;
	}
	if(stock_->bestBid() < expectedTLPrice  && stock_->bestBid() != 0.0)
	{
		belowTL_ = true;
	}

	return false;
}

void COTLEntry::reset()
{
	numTradesPerStick_ = 0;
 //   tradeType_ = PurchaseData::TradeType::NoTrade;

}

bool COTLEntry::setTrendLine()
{
	long tlStartTime = 0;
	long tlEndTime = 0;
	double tlStartPrice = 0.0;
	double tlEndPrice = 0.0;


	CandleStick * currentStick =
		CandleStickManager::instance()->getCandleStick(stock_->symbol(), 
													   TLEndTime_);
	CandleStick * firstStick = 		
		CandleStickManager::instance()->getCandleStick(stock_->symbol(), 
													   TLStartTime_);

	if(0 == currentStick || 0 == firstStick || currentStick->jdate() != stock_->jdate())
	{
		rateOfChange_ = 0.0;
		std::string msg = "!!!!!Failed to get first or last candle stick for trend line: ";
		msg += stock_->symbol();
//		ErrorLog::instance()->reportError(msg);
		return false;
	}
	

	switch (ConfigurationData::instance()->candleStickVal())
	{
	case CandleStick::OPEN:
		{
			tlStartPrice = firstStick->openPrice();
			tlEndPrice = currentStick->openPrice();
			break;
		}
	case CandleStick::CLOSE:
		{
			tlStartPrice = firstStick->closePrice();
			tlEndPrice = currentStick->closePrice();
			TLStartTime_ += (long)(CandleStickManager::instance()->seconds()-1.0);
			TLEndTime_ += (long)(CandleStickManager::instance()->seconds()-1.0);
			break;
		}
	case CandleStick::HIGH:
		{
			tlStartPrice = firstStick->highPrice();
			tlEndPrice = currentStick->highPrice();
			break;
		}
	case CandleStick::LOW:
		{
			tlStartPrice = firstStick->lowPrice();
			tlEndPrice = currentStick->lowPrice();
			break;
		}
	default:
		{
			tlStartPrice = firstStick->openPrice();
			tlEndPrice = currentStick->openPrice();
			break;
		}
	}

	baseTLTime_ = TLEndTime_;
	baseTLPrice_ = tlEndPrice;

	double priceChange = tlEndPrice - tlStartPrice;
	long totalSecs = 0;

	if(tlStartTime > tlEndTime)
	{
		totalSecs = 86400 - TLStartTime_ + TLEndTime_;
	}
	else
	{
		totalSecs = TLEndTime_ - TLStartTime_;
	}
	rateOfChange_ = priceChange/totalSecs;
	tlrSlope_ = getSlope(stock_->symbol(),totalSecs/900)/900.0;

    std::strstream strstr;
    strstr << "tlStartTime: " << TimeZone::instance()->formatTZ(TLStartTime_)
		   << "\ntlStartPrice: " << tlStartPrice 
		   << "\ntlEndTime: " << TimeZone::instance()->formatTZ(TLEndTime_) 
		   << "\ntlEndPrice: " << tlEndPrice 
		   << "\ntRate Of Change: " << rateOfChange_ << std::ends;
	std::string  msg = strstr.str();
    strstr.clear();
    strstr.rdbuf()->freeze(0);

	DataLogger::instance()->recordDebug(msg, stock_->symbol());
	return true;
}


void COTLEntry::newTradeDay()
{
	transactions_ = 0;
	numSticks_ = 0;
	numTradesPerStick_ = 0;
	tradeType_ = PurchaseData::NoTrade;
	belowTL_ = true;
	lastTickInPosition_ = false;
	baseTLTime_ = 0;
	baseTLPrice_= 0.0;
	rateOfChange_= 0.0;
	numReversals_= 0;
}

