#include "CandleHistMaker.h"
#include "HistQuery.h"
#include "CandleManager.h"

CandleHistMaker * CandleHistMaker::instance_ = 0;

CandleHistMaker * CandleHistMaker::instance()
{
	if(0 == instance_)
	{
		instance_ = new CandleHistMaker();
	}
	return instance_;
}

CandleHistMaker::CandleHistMaker()
{
}

void CandleHistMaker::getCandleHistory(std::vector<std::string> & symbols)
{
	std::vector<std::string>::iterator iter;
	for(iter = symbols.begin(); iter != symbols.end(); ++iter)
	{
		HistQuery * query = new HistQuery();
		query->symbol_ = (*iter);
		query->timeStart_ = 0.0;
		query->timeEnd_ = 0.0;
		query->timeType_ = CandleData::M1;
		query->observer_ = this;
		CandleManager::instance()->getHist(query);
	}
}

void CandleHistMaker::update(HistQuery * query)
{
	if(query->lastDate_ > query->timeStart_ && query->numCandles_ >= 1000)
	{
		query->timeEnd_ = query->lastDate_;
		CandleManager::instance()->getHist(query);
	}
	else
	{
	}
}



