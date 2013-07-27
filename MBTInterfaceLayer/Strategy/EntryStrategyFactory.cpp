// EntryStrategyFactory.cpp: implementation of the EntryStrategyFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "EntryStrategyFactory.h"
#include "StrategyHeaders.h"
#include "ConfigurationData.h"
#include "StockWatch.h"
#include "FXPrime.h"

EntryStrategyFactory * EntryStrategyFactory::instance_ = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EntryStrategyFactory::EntryStrategyFactory()
{

}

EntryStrategyFactory::~EntryStrategyFactory()
{

}

EntryStrategyFactory * EntryStrategyFactory::instance()
{
	if(0 == instance_)
	{
		instance_ = new EntryStrategyFactory();
	}
	return instance_;
}

EntryStrategy * EntryStrategyFactory::getStrategy(StockWatch * stock)
{
	TradingSystem tradeSystem = ConfigurationData::instance()->getTradingSystemType(stock->symbol());

	if(tradeSystem == TLTrading)
	{
		SymbolData * symbolData = ConfigurationData::instance()->symbolData(stock->symbol());
		TLSymbolData * data = dynamic_cast<TLSymbolData*>(symbolData);
		return new COTLEntry(stock, 
							 data->firstEntrySignalTime_,
							 data->TLStartTime_,
							 data->TLEndTime_,
							 data->startTradeTime_,
							 data->endTradeTime_);
	}
	else if(tradeSystem == VolatilityBreakOutWImprovedExit)
	{
		SymbolData * symbolData = ConfigurationData::instance()->symbolData(stock->symbol());
		VolatilityBreakOutWImprovedExitData * data = dynamic_cast<VolatilityBreakOutWImprovedExitData*>(symbolData);

		if(data->invertTrade_)
		{
			return new VolatilityBreakoutPullback(stock, 
										  data->atrBars_, 
										  data->EMABars_, 
										  data->ATRMult_,
										  data->startTradeTime_,
										  data->endTradeTime_);
		}
		else
		{
			return new VolatilityBreakout(stock, 
										  data->atrBars_, 
										  data->EMABars_, 
										  data->ATRMult_,
										  data->startTradeTime_,
										  data->endTradeTime_);
		}
	}
	else if(tradeSystem == TrendLineWImprovedExit)
	{
		SymbolData * symbolData = ConfigurationData::instance()->symbolData(stock->symbol());
		TrendLineWImprovedExitData * data = dynamic_cast<TrendLineWImprovedExitData*>(symbolData);


		return new TrendLineEntry(stock, 
								  data->TL1Bars_, 
								  data->TL2Bars_, 
								  data->RSIBars_,
								  data->StochBars_,
								  data->startTradeTime_,
								  data->endTradeTime_);
	}
	else if(tradeSystem == DynamicRulesTrading)
	{
		SymbolData * data = ConfigurationData::instance()->symbolData(stock->symbol());
		DynamicRulesData * dData = dynamic_cast<DynamicRulesData*>(data);
		EntryRule * eData = dData->entryRule_;

		if(0 != eData)
		{
			VolatilityBreakoutEntry * vbRule = dynamic_cast<VolatilityBreakoutEntry*>(eData);
			TurtleBreakoutEntry * tbRule = dynamic_cast<TurtleBreakoutEntry*>(eData);
			TripleMVAEntry * tRule = dynamic_cast<TripleMVAEntry*>(eData);
			EMAScalpEntry * emaRule = dynamic_cast<EMAScalpEntry*>(eData);
			TLScalpEntry * tlRule = dynamic_cast<TLScalpEntry*>(eData);
			TLScalp2Entry * tl2Rule = dynamic_cast<TLScalp2Entry*>(eData);
			CommitteeVoteEntry * taRule = dynamic_cast<CommitteeVoteEntry*>(eData);
			FXPrimeEntry * cciRule = dynamic_cast<FXPrimeEntry*>(eData);

			if(0 != vbRule)
			{
				if(vbRule->invertTrade_)
				{
					return new VolatilityBreakoutPullback(stock, 
												  vbRule->ATRBars_, 
												  vbRule->EMABars_, 
										          vbRule->ATRMult_,
										          dData->startTradeTime_,
										          dData->endTradeTime_);
				}
				else
				{
					return new VolatilityBreakout(stock, 
												  vbRule->ATRBars_, 
												  vbRule->EMABars_, 
										          vbRule->ATRMult_,
										          dData->startTradeTime_,
										          dData->endTradeTime_);
				}
			}
			else if(0 != tbRule)
			{
				return new TurtleBreakout(stock, 
									  tbRule->numBars_, 
							          dData->startTradeTime_,
							          dData->endTradeTime_);
			}
			else if(0 != tRule)
			{
				return new TripileMVAEntry(stock, 
										  tRule->fast_, 
										  tRule->medium_, 
								          tRule->slow_,
								          dData->startTradeTime_,
								          dData->endTradeTime_);
			}
			else if(0 != emaRule)
			{
				return new EMAScalp(stock, 
									emaRule->emaBars_, 
									emaRule->adxBars_,
									emaRule->atrBars_,
								    dData->startTradeTime_,
								    dData->endTradeTime_);
			}
			else if(0 != tlRule)
			{
				return new TLScalp(stock, 
									tlRule->slopeBars_, 
									tlRule->adxBars_,
									tlRule->atrBars_,
									tlRule->tlEndTime_,
								    dData->startTradeTime_,
								    dData->endTradeTime_);
			}
			else if(0 != tl2Rule)
			{
				return new TLScalp2(stock, 
									tl2Rule->slopeBars_, 
									tl2Rule->adxBars_,
									tl2Rule->atrBars_,
								    dData->startTradeTime_,
								    dData->endTradeTime_);
			}
			else if(0 != cciRule)
			{
				return new FXPrime(stock,
								   14,
								   cciRule->rsiBars_,
								   cciRule->cciSlowBars_,
								   cciRule->cciFastBars_,
								    dData->startTradeTime_,
								    dData->endTradeTime_);
			}
			else if(0 != taRule)
			{
				std::string name = stock->symbol();
				int pos = name.find("/");
				if( pos != std::string::npos)
				{
					name.replace(pos, 1, "");
				}
				std::string ANNPath = ConfigurationData::instance()->logPath();
				ANNPath += "\\ANN\\";
				ANNPath += name;
				std::string ann1File = ANNPath + ".UpDown.Net.Pattern";
				std::string ann2File = ANNPath + ".4Bars.Net.Pattern";
				std::string ann3File = ANNPath + ".UpDown.Net.GMMA";
				std::string ann4File = ANNPath + ".4Bars.Net.GMMA";
				std::string ann5File = ANNPath + ".UpDown.Net.Hilbert";
				std::string ann6File = ANNPath + ".4Bars.Net.Hilbert";
				std::string ann7File = ANNPath + ".UpDown.Net.MishMash";
				std::string ann8File = ANNPath + ".4Bars.Net.MishMash";
				std::string annChairmanFile = ANNPath + ".UpDown.Net.Chairman";
				return new TwoAnn(stock, 
					                   ann1File, 
									   ann2File, 
					                   ann3File, 
									   ann4File, 
					                   ann5File, 
									   ann6File, 
									   ann7File,
									   ann8File,
									   annChairmanFile,
									   taRule->ann1Lower_, 
									   taRule->ann2Lower_, 
									   taRule->ann3Lower_, 
									   taRule->ann4Lower_, 
									   taRule->ann5Lower_, 
									   taRule->ann6Lower_, 
 								       dData->startTradeTime_,
								       dData->endTradeTime_);
			}
		}
	}
	return 0;
}
