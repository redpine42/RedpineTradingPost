#include "SymbolData.h"
#include <string>
#include <ios>
#include <strstream>
#include <fstream>
#include <math.h>
#include <string>
#include "PurchaseData.h"
#include "MsgProducer.h"
#include "TimeZone.h"
#include "PairPricing.h"


SymbolData::SymbolData(std::string symbol)
    : symbol_(symbol),
      openData_(0),
      closeData_(0),
	  nextOrderTime_(0),
	  success_(false),
      totalVol_(0),
	  realShortable_(true),
	  count_(0),
	  badValues_(0)
{
    data_ = new L1Data(symbol, 
						0,
                           0.0, 
                           0, 
                           0,
							0,
							0.0,
                            0.0,
                            0.0,
                            0,
                            0,
                            false,
                            0,
                            false);
}

SymbolData::~SymbolData()
{
    if(openData_ != 0)
    {
        delete openData_;
    }

    if(closeData_ != 0)
    {
        delete closeData_;
    }

}


void SymbolData::recordTrade()
{
	double priceChange = 0.0;

	if(openData_->typeTrade_ == PurchaseData::Buy)
	{
		priceChange = closeData_->price_ - openData_->price_;
	}
	else
	{
		priceChange = openData_->price_ - closeData_->price_;
	}
	if(priceChange > 0.0)
	{
		success_ = true;
	}
	else
	{
		success_ = false;
	}

	recordTrade(openData_, closeData_);

	delete openData_;
	delete closeData_;
	openData_ = 0;
	closeData_ = 0;
	++count_;
}

void SymbolData::failedOrder(std::string msg)
{
	if(0 != closeData_)
	{
		delete closeData_;
		closeData_ = 0;
	}
	failedOrder(msg, openData_);
	delete openData_;
	openData_ = 0;
}

void SymbolData::recordTrade(const PurchaseData * open, const PurchaseData * close)
{
	double profit = 0.0;
	double priceChange = 0.0;
	std::string typeTrade;
	if(open->typeTrade_ == PurchaseData::Buy)
	{
		typeTrade = "Long";
		priceChange = close->price_ - open->price_;
		profit = priceChange * open->size_;
	}
	else
	{
		typeTrade = "Short";
		priceChange = open->price_ - close->price_;
		profit = priceChange * open->size_;
	}
	std::strstream ostrm;

	ostrm << "Trade Completed:\n" << "Profit: " << profit << "\nOpen Purchase:" << *open
	      << "\nClosing Purchase: " << *close << std::ends;

	std::string tradeMsg = ostrm.str();
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::SYMBOLDATA, tradeMsg);

}

void SymbolData::failedOrder(std::string msg, PurchaseData * data)
{
	std::strstream ostrm;
	ostrm << "FAILED ORDER\n" <<  msg << *data << std::ends;
	std::string tradeMsg = ostrm.str();

	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::SYMBOLDATA, tradeMsg);
}

void SymbolData::updateLevel1(L1Data * data)
{
	if(data->price_ == 0.0  || filter(data))
    {
        delete data;
        return;
    }
	++count_;

	delete data_;
	data_ = data;

	totalVol_ = data_->volume_;

	PairPricing::instance()->setPairPrice(symbol_,data_->price_);
}

bool SymbolData::filter(L1Data * data)
{
/*	double filterATR = CandleStickManager::instance()->getFilterATR(symbol_);
	if(filterATR != 0.0 && badValues_ < 10 && fabs(data->price() - data_->price()) > 2 * filterATR)
	{
		++badValues_;
		std::strstream strstr;
		strstr << "Bad tick Value suspected\nSymbol: " << symbol_ << "\nPrice: " << data->price() << "\nATR: " << filterATR << std::ends;
		std::string  msg = strstr.str();
		strstr.clear();
		strstr.rdbuf()->freeze(0);

		ErrorLog::instance()->reportError(msg);
		return true;
	}
	badValues_ = 0;
*/
	return false;
}

void SymbolData::updateTradeStatus(PurchaseData::TradeStatus status)
{
	if(0 != closeData_)
	{
		closeData_->status_ = status;
	}
	else if(0 != openData_)
	{
		openData_->status_ = status;
	}
}


const std::string SymbolData::date() const 
{ 
	return TimeZone::instance()->getDateStr(data_->jdate_);
}
