// PriceStrategyFactory.cpp: implementation of the PriceStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "PriceStrategyFactory.h"
#include "StrategyHeaders.h"
#include "ConfigurationData.h"
#include "StockWatch.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
PriceStrategyFactory * PriceStrategyFactory::instance_ = 0;

PriceStrategyFactory::PriceStrategyFactory()
{

}

PriceStrategyFactory::~PriceStrategyFactory()
{

}
 
PriceStrategyFactory * PriceStrategyFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new PriceStrategyFactory();
	}
	return instance_;
}

PriceStrategy * PriceStrategyFactory::getStrategy(StockWatch * stock)
{
	PriceStrategy * strat = 0;
	StrategyMapIter iter = priceStrategies_.find(stock->symbol());
	if(iter == priceStrategies_.end())
	{
		TradingSystem tradeSystem = ConfigurationData::instance()->getTradingSystemType(stock->symbol());
	
		if(tradeSystem == TLTrading)
		{
			SymbolData * data = ConfigurationData::instance()->symbolData(stock->symbol());
			TLSymbolData * tldata = dynamic_cast<TLSymbolData*>(data);

			strat = new COTLPriceStrategy(tldata->pipsStopLoss_);
			priceStrategies_[stock->symbol()] = strat;
		}
		else if(tradeSystem == VolatilityBreakOutWImprovedExit)
		{
			SymbolData * data = ConfigurationData::instance()->symbolData(stock->symbol());
			TrendLineWImprovedExitData * vbed = dynamic_cast<TrendLineWImprovedExitData*>(data);
			strat = new MatchBidPrice(vbed->pipsTrail_);
//			strat = new MarketPrice();
			priceStrategies_[stock->symbol()] = strat;
		}
		else if(tradeSystem == TrendLineWImprovedExit)
		{
			SymbolData * data = ConfigurationData::instance()->symbolData(stock->symbol());
			TrendLineWImprovedExitData * vbed = dynamic_cast<TrendLineWImprovedExitData*>(data);
			strat = new MatchBidPrice(vbed->pipsTrail_);
//			strat = new MarketPrice();
			priceStrategies_[stock->symbol()] = strat;
		}
		else if(tradeSystem == DynamicRulesTrading)
		{
			SymbolData * data = ConfigurationData::instance()->symbolData(stock->symbol());
			DynamicRulesData * dData = dynamic_cast<DynamicRulesData*>(data);
			PriceRule * prData = dData->priceRule_;
			if(0 == prData)
			{
				strat = new MarketPrice();
				priceStrategies_[stock->symbol()] = strat;
				return strat;
			}

			MarketPricingRule * mpRule = dynamic_cast<MarketPricingRule*>(prData);
			HalfBarPricingRule * hbRule = dynamic_cast<HalfBarPricingRule*>(prData);
			MatchBidPricingRule * mbRule = dynamic_cast<MatchBidPricingRule*>(prData);
			SpreadPricing * sRule = dynamic_cast<SpreadPricing*>(prData);
			MarketTPLimitPricingRule * tpRule = dynamic_cast<MarketTPLimitPricingRule*>(prData);
			MarketLimitPricingRule * mlRule = dynamic_cast<MarketLimitPricingRule*>(prData);

			if(0 != mpRule)
			{
				strat = new MarketPrice();
			}
			else if(0 != mlRule)
			{
				strat = new MarketLimitPricing();
			}
			else if(0 != hbRule)
			{
				strat = new HalfBarPrice();
			}
			else if(0 != mbRule)
			{
				strat = new MatchBidPrice(100000);
			}
			else if(0 != sRule)
			{
				strat = new SpreadPrice(sRule->pipsStopLoss_, sRule->pipsTakeProfit_);
			}
			else if(0 != tpRule)
			{
				double precision = ConfigurationData::instance()->precision(stock->symbol());
				strat = new MarketTPLimitPrice(tpRule->takeProfit_ * precision);
			}
		}
		if(0 == strat)
		{
			strat = new MarketPrice();
		}
		priceStrategies_[stock->symbol()] = strat;
	}
	else 
	{
		strat = (*iter).second;
	}
	return strat;
}
