#pragma warning(disable:4786)
#ifndef SymbolData_h
#define SymbolData_h

#ifndef PurchaseData_h
#include "PurchaseData.h"
#endif

#ifndef L1Data_h
#include "L1Data.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

class SymbolData
{
public:
    SymbolData(std::string symbol);

    ~SymbolData();
	
	void updateLevel1(L1Data * data);
    const L1Data * getLevel1Data() {return data_;}

    double getLastPrice() const { return data_->price_;}
    double getVolume() const { return data_->volume_;}

    const long time() const {return data_->time_;}
	const long jdate() const {return data_->jdate_;}
	const std::string date() const;

    double bestBid() const{return data_->bid_;}
    double bestAsk() const {return data_->ask_;}
    long bidSize() const {return data_->bidSize_;}
    long askSize() const {return data_->askSize_;}
	bool upTick() const {return data_->upTick_;}
    bool shortable()const {return (realShortable_);}

	void failShort(){realShortable_ = false;}
	void closePosition(){nextOrderTime_ = data_->time_ + 60;}
//	void updateTime(int secondsUTC){data_->time_ = secondsUTC;}
	bool tradeable(){return tradable_;}
	
	std::string symbol() const { return symbol_;}
	bool shortable(){return true;}

    PurchaseData * openData(){return openData_;}
    PurchaseData * closeData(){return closeData_;}

    void openData(PurchaseData * data){openData_ = data;}
    void closeData(PurchaseData * data){closeData_ = data;}
	void recordTrade();

	const long numberTrades() const {return count_;}
	const long nextOrderTime() const {return nextOrderTime_;}
	bool tradeSuccess(){return success_;}

	void failedOrder(std::string symbol);
	void updateTradeStatus(PurchaseData::TradeStatus status);

private:
	void recordTrade(const PurchaseData * open, const PurchaseData * close);
	void failedOrder(std::string msg, PurchaseData * data);

	long count_;
	std::string symbol_;
	bool success_;

    PurchaseData * openData_;
    PurchaseData * closeData_;

	long nextOrderTime_;


	bool filter(L1Data * data);
	double filterATR_;
	int badValues_;
	L1Data * data_;

	// According to trying
	bool realShortable_;

    long totalVol_;
	bool tradable_;
};

#endif

