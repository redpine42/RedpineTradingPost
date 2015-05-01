#include "CandleManager.h"
#include "MsgProducer.h"
#include "CHistSink.h"
#include "HistoryObserver.h"
#include "HistQuery.h"
#include "CandleData.h"
#include "MsgProducer.h"

CandleManager * CandleManager::instance_ = 0;

CandleManager * CandleManager::createInstance(IComMgr * pComMgr)
{
	if(0 == instance_)
	{
		instance_ = new CandleManager(pComMgr);
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Info, CornerTurnConst::CANDLEMANAGER, "Candle Manager created");
	}
	return instance_;
}

CandleManager * CandleManager::instance()
{
	if(0 == instance_)
	{
	    MsgProducer::instance()->sendTextMessage(CornerTurnConst::Error, CornerTurnConst::CANDLEMANAGER, "Instance called before creation!");
	}
	return instance_;
}

CandleManager::CandleManager(IComMgr * pComMgr)
{
	DWORD cookie;
	histSink_ = new CHistSink();
	histSink_->SetComMgr(pComMgr);
	histMgr_ = pComMgr->HistMgr;

	LPUNKNOWN pSink = histSink_->GetIDispatch(FALSE);
	AfxConnectionAdvise(histMgr_, __uuidof(_IMbtHistEvents), pSink, FALSE, &cookie);
	histCnt_ = 0;
}

void CandleManager::add(std::vector<std::string> & symbols, long time)
{
	std::vector<std::string>::iterator iter;
	for(iter = symbols.begin(); iter != symbols.end(); ++iter)
	{
		add((*iter), time);
	}
}


void CandleManager::add(std::string & symbol, long time)
{
	HistQuery *query = new HistQuery();
	query->hist_ = histMgr_->CreateHistMinBar();
	histMap_[++histCnt_] = query;
	query->requestId_ = histCnt_;
	query->symbol_ = symbol;
	query->timeType_ = CandleData::getType(time);

	query->hist_->SendRequest(symbol.c_str(),histCnt_,time,0,0,1000,true, true);
}

unsigned long CandleManager::getHist(HistQuery * request)
{
	int time = CandleData::candleTime(request->timeType_);
	request->hist_ = histMgr_->CreateHistMinBar();
	histMap_[++histCnt_] = request;
	request->requestId_ = histCnt_;

	request->hist_->SendRequest(request->symbol_.c_str(),histCnt_,time,request->timeStart_,request->timeEnd_,1000,false, true);
	return histCnt_;
}

void CandleManager::finishHist(unsigned long requestId, DATE lastDate, int numCandles)
{
	HistQuery * query = histMap_[requestId];
	query->lastDate_ = lastDate;
	query->numCandles_ = numCandles;
	if(0 != query->observer_)
	{
		query->observer_->update(query);
	}
}
void CandleManager::addCandle(CandleData & data, long requestId)
{
	HistQuery * query = histMap_[requestId];

	data.candleTimeType_ = histMap_[requestId]->timeType_;
	data.symbol_ = query->symbol_;

/*	std::string updateType;
	switch(data.candleType_)
	{
		case CandleData::INITIAL:
			updateType = "Init";
			break;
		case CandleData::NEW:
			updateType = "New";
			break;
		case CandleData::UPDATE:
			updateType = "Update";
			break;
	}
	std::cout << updateType << " " << data.date_ << " " << data.startTime_ << std::endl;
	*/
	MsgProducer::instance()->sendCandleData(data);

}

void CandleManager::getCandleData(std::vector<std::string> & symbols)
{
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::M1));
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::M5));
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::M15));
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::M30));
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::H1));
	CandleManager::instance()->add(symbols, CandleData::candleTime(CandleData::H4));
//	CandleManager::instance()->add(symbols, CandleData::D1);
}

