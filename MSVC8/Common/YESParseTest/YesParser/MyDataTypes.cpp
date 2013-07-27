#include "MyDataTypes.h"

#ifndef PARSERTEST
#include "TimeZone.h"
#endif


std::string toString(bool val)
{
	if(val)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

void MaxDDMSAData::printData(std::ofstream & ostrm)
{
	ostrm << "\tMaxDrawDownMSA" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tMaxHistDrawDown = " << (float)maxHistDrawDown_ << "\n";
	ostrm << "\t\tCurrentEquity = " << (float)currentEquity_ << "\n";
	ostrm << "\t\tMarginPercentage = " << (float)marginPercentage_ << "\n";
	ostrm << "\t\tMaxDDPercent = " << (float)maxDDPercent_ << "\n";
	ostrm << "\t}" << std::endl;
}

void MaxDDData::printData(std::ofstream & ostrm)
{
	ostrm << "\tMaxDrawDown" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tPercentRisk = " << (float)percentRisk_ << "\n";
	ostrm << "\t\tMaxDrawdownPips = " << maxDDPips_ << "\n";
	ostrm << "\t\tNumberTrades = " << numTrades_ << "\n";
	ostrm << "\t\tNumberWins = " << numWins_ << "\n";
	ostrm << "\t}" << std::endl;
}


void MarketPricingRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tMarketPricing" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}
void MarketLimitPricingRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tMarketLimitPricing" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void MarketTPLimitPricingRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tMarketTPLimitPricing" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tTakeProfit = " << takeProfit_ << "\n";
	ostrm << "\t}" << std::endl;
}

void HalfBarPricingRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tHalfBarLimitPrice" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void MatchBidPricingRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tMatchBidLimitPricing" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void CandlePatternEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tCandlePatternEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}


void SpreadPricing::printData(std::ofstream & ostrm)
{
	ostrm << "\tSpreadPricing" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tPipsStopLoss = " << (float)pipsStopLoss_ << "\n";
	ostrm << "\t\tPipsTakeProfit = " << (float)pipsTakeProfit_ << "\n";
	ostrm << "\t}" << std::endl;
}


void TLSymbolData::printData(std::ofstream & ostrm, std::string & symbol)
{
#ifndef PARSERTEST
	ostrm << "YesTLPair" << "\n";
	ostrm << "{" << "\n";
	ostrm << "\tSymbol = " << symbol << "\n";
	ostrm << "\tStartTradeTime = " << TimeZone::instance()->formatTZ(startTradeTime_) << "\n";
	ostrm << "\tEndTradeTime = " << TimeZone::instance()->formatTZ(endTradeTime_) << "\n";
	ostrm << "\tFirstEntrySignalTime = " << TimeZone::instance()->formatTZ(firstEntrySignalTime_) << "\n";
	ostrm << "\tFirstTrendLineTime = " << TimeZone::instance()->formatTZ(TLStartTime_) << "\n";
	ostrm << "\tSecondTrendLineTime = " << TimeZone::instance()->formatTZ(TLEndTime_) << "\n";
	ostrm << "\tPipsStopLoss = " << (int)(pipsStopLoss_) << "\n";
	ostrm << "\tTrailOnceStopLossTrigger = " << (int)(trailOnceStopLossTrigger_) << "\n";
	ostrm << "\tTrailOnceStopLoss = " << (int)(trailOnceStopLoss_) << "\n";
	ostrm << "\tPIPSPrecision = " << pipsPrecision_ << "\n";

	if(0 != msaData_)
	{
		msaData_->printData(ostrm);
	}
	else if(0 != maxDDData_)
	{
		maxDDData_->printData(ostrm);
	}
	else if(defaultLotSize_ >= 0)
	{
		ostrm << "\tDefaultLotSize = " << (int)defaultLotSize_ << "\n";
	}
	ostrm << "}" << "\n";
#endif
}

void VolatilityBreakOutWImprovedExitData::printData(std::ofstream & ostrm, std::string & symbol)
{
#ifndef PARSERTEST
	ostrm << "VolatilityBreakOutWImprovedExit" << "\n";
	ostrm << "{" << "\n";
	ostrm << "\tSymbol = " << symbol << "\n";
	ostrm << "\tStartTradeTime = " << TimeZone::instance()->formatTZ(startTradeTime_) << "\n";
	ostrm << "\tEndTradeTime = " << TimeZone::instance()->formatTZ(endTradeTime_) << "\n";
	ostrm << "\tPIPSPrecision = " << pipsPrecision_ << "\n";
	ostrm << "\tInvertTrade = " << toString(invertTrade_) << "\n";
	ostrm << "\tEntryATRBars = " << entryATRBars_ << "\n";
	ostrm << "\tEMABars = " << EMABars_ << "\n";
	ostrm << "\tATRMult = " << ATRMult_ << "\n";
	ostrm << "\tTimeExit = " << timeExit_ << "\n";
	ostrm << "\tATRBars = " << entryATRBars_ << "\n";
	ostrm << "\tmmstp = " << mmstp_ << "\n";
	ostrm << "\tptlim = " << ptlim_ << "\n";
	ostrm << "\tstpa = " << stpa_ << "\n";
	ostrm << "\tstpb = " << stpb_ << "\n";
	ostrm << "\tptga = " << ptga_ << "\n";

	if(0 != msaData_)
	{
		msaData_->printData(ostrm);
	}
	else if(0 != maxDDData_)
	{
		maxDDData_->printData(ostrm);
	}
	else if(defaultLotSize_ >= 0)
	{
		ostrm << "\tDefaultLotSize = " << (int)defaultLotSize_ << "\n";
	}
	ostrm << "}" << "\n";
#endif
}

void TrendLineWImprovedExitData::printData(std::ofstream & ostrm, std::string & symbol)
{
#ifndef PARSERTEST
	ostrm << "TrendLineWImprovedExit" << "\n";
	ostrm << "{" << "\n";
	ostrm << "\tSymbol = " << symbol << "\n";
	ostrm << "\tInvertTrade = " << toString(invertTrade_) << "\n";
	ostrm << "\tStartTradeTime = " << TimeZone::instance()->formatTZ(startTradeTime_) << "\n";
	ostrm << "\tEndTradeTime = " << TimeZone::instance()->formatTZ(endTradeTime_) << "\n";
	ostrm << "\tPIPSPrecision = " << pipsPrecision_ << "\n";
	ostrm << "\tATRBars = " << atrBars_ << "\n";
	ostrm << "\tTL1Bars = " << TL1Bars_ << "\n";
	ostrm << "\tTL2Bars = " << TL2Bars_ << "\n";
	ostrm << "\tRSIBars = " << RSIBars_ << "\n";
	ostrm << "\tStochBars = " << StochBars_ << "\n";
	ostrm << "\tTimeExit = " << timeExit_ << "\n";
	ostrm << "\tmmstp = " << mmstp_ << "\n";
	ostrm << "\tptlim = " << ptlim_ << "\n";
	ostrm << "\tstpa = " << stpa_ << "\n";
	ostrm << "\tstpb = " << stpb_ << "\n";
	ostrm << "\tptga = " << ptga_ << "\n";

	if(0 != msaData_)
	{
		msaData_->printData(ostrm);
	}
	else if(0 != maxDDData_)
	{
		maxDDData_->printData(ostrm);
	}
	else if(defaultLotSize_ >= 0)
	{
		ostrm << "\tDefaultLotSize = " << (int)defaultLotSize_ << "\n";
	}
	ostrm << "}" << std::endl;
#endif
}

void ADXEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tADXEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tADXBars = " << adxBars_ << "\n";
	ostrm << "\t\tPlusDIBars = " << plusDIBars_ << "\n";
	ostrm << "\t\tMinusDIBars = " << minusDIBars_ << "\n";
	ostrm << "\t}" << std::endl;
};

void TestEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTestEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
};

void FXPrimeEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tFXPrimeEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tRSIBars = " << rsiBars_ << "\n";
	ostrm << "\t\tCCISlowBars = " << cciSlowBars_ << "\n";
	ostrm << "\t\tCCIFastBars = " << cciFastBars_ << "\n";
	ostrm << "\t}" << std::endl;
};

void ROCWImprovedExitData::printData(std::ofstream & ostrm, std::string & symbol)
{
#ifndef PARSERTEST
	ostrm << "ROCWImprovedExit" << "\n";
	ostrm << "{" << "\n";
	ostrm << "\tSymbol = " << symbol << "\n";
	ostrm << "\tInvertTrade = " << toString(invertTrade_) << "\n";
	ostrm << "\tStartTradeTime = " << TimeZone::instance()->formatTZ(startTradeTime_) << "\n";
	ostrm << "\tEndTradeTime = " << TimeZone::instance()->formatTZ(endTradeTime_) << "\n";
	ostrm << "\tPIPSPrecision = " << pipsPrecision_ << "\n";
	ostrm << "\tATRBars = " << atrBars_ << "\n";
	ostrm << "\tROCBars = " << rocBars_ << "\n";
	ostrm << "\tADXBars = " << adxBars_ << "\n";
	ostrm << "\tROCCount = " << ROCCount_ << "\n";
	ostrm << "\tStdROCBars = " << stdROCBars_ << "\n";
	ostrm << "\tTimeExit = " << timeExit_ << "\n";
	ostrm << "\tmmstp = " << mmstp_ << "\n";
	ostrm << "\tptlim = " << ptlim_ << "\n";
	ostrm << "\tstpa = " << stpa_ << "\n";
	ostrm << "\tstpb = " << stpb_ << "\n";
	ostrm << "\tptga = " << ptga_ << "\n";

	if(0 != msaData_)
	{
		msaData_->printData(ostrm);
	}
	else if(0 != maxDDData_)
	{
		maxDDData_->printData(ostrm);
	}
	else if(defaultLotSize_ >= 0)
	{
		ostrm << "\tDefaultLotSize = " << (int)defaultLotSize_ << "\n";
	}
	ostrm << "}" << std::endl;
#endif
}
void RLCandleEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tRLCandleEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tEntryAgent = " << entryAgent_ << "\n";
	ostrm << "\t}" << std::endl;
}

void RLCandleExit::printData(std::ofstream & ostrm)
{
	ostrm << "\tRLCandleExit" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tExitAgent = " << exitAgent_ << "\n";
	ostrm << "\t}" << std::endl;
}

void DynamicRulesData::printData(std::ofstream & ostrm, std::string & symbol)
{
#ifndef PARSERTEST
	ostrm << "DynamicDefinition" << "\n";
	ostrm << "{" << "\n";
	ostrm << "\tSymbol = " << symbol << "\n";
	ostrm << "\tStartTradeTime = " << TimeZone::instance()->formatTZ(startTradeTime_) << "\n";
	ostrm << "\tEndTradeTime = " << TimeZone::instance()->formatTZ(endTradeTime_) << "\n";
	ostrm << "\tPIPSPrecision = " << pipsPrecision_ << "\n";

	if(0 != priceRule_)
	{
		priceRule_->printData(ostrm);
	}

	if(0 != entryRule_)
	{
		entryRule_->printData(ostrm);
	}

	if(0 != exitRule_)
	{
		exitRule_->printData(ostrm);
	}

	if(0 != openMonitor_)
	{
		openMonitor_->printData(ostrm);
	}

	if(0 != closeMonitor_)
	{
		closeMonitor_->printData(ostrm);
	}

	if(0 != msaData_)
	{
		msaData_->printData(ostrm);
	}
	else if(0 != maxDDData_)
	{
		maxDDData_->printData(ostrm);
	}
	else if(defaultLotSize_ >= 0)
	{
		ostrm << "\tDefaultLotSize = " << (int)defaultLotSize_ << "\n";
	}
	ostrm << "}" << "\n";
#endif
}



void VolatilityBreakoutEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tVolatilityBreakoutEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\tInvertTrade = " << toString(invertTrade_) << "\n";
	ostrm << "\t\tATRBars = " << ATRBars_ << "\n";
	ostrm << "\t\tEMABars = " << EMABars_ << "\n";
	ostrm << "\t\tATRMult = " << ATRMult_ << "\n";
	ostrm << "\t}" << std::endl;
}

void TurtleBreakoutEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTurtleBreakoutEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tNumBarsEvaluate = " << numBars_ << "\n";
	ostrm << "\t}" << std::endl;
}
void GeneticProgramEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tGeneticProgramEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\talgorithm = " << algorithm_ << "\n";
	ostrm << "\t}" << std::endl;
}

void TLGeneticProgramEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTLGeneticProgramEntry" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\talgorithm = " << algorithm_ << "\n";
#ifndef PARSERTEST
	ostrm << "\t\tTLStartTime_ = " << TimeZone::instance()->formatTZ(TLStartTime_) << "\n";
	ostrm << "\t\tTLEndTime_ = " << TimeZone::instance()->formatTZ(TLEndTime_) << "\n";
#endif
	ostrm << "\t}" << std::endl;
}

void TripleMVAEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTrippleMVAEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tBarsFast = " << fast_ << "\n";
	ostrm << "\t\tBarsMedium = " << medium_ << "\n";
	ostrm << "\t\tBarsSlow = " << slow_ << "\n";
	ostrm << "\t}" << std::endl;
}
void EMAScalpEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tEMAScalpEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tADXBars = " << adxBars_ << "\n";
	ostrm << "\t\tATRBars = " << atrBars_ << "\n";
	ostrm << "\t\tEMABars = " << emaBars_ << "\n";
	ostrm << "\t}" << std::endl;
}
void TLScalpEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTLScalpEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tADXBars = " << adxBars_ << "\n";
	ostrm << "\t\tATRBars = " << atrBars_ << "\n";
	ostrm << "\t\tSlopeBars = " << slopeBars_ << "\n";
#ifndef PARSERTEST
	ostrm << "\t\tTLEndTime = " << TimeZone::instance()->formatTZ(tlEndTime_) << "\n";
#endif
	ostrm << "\t}" << std::endl;
}
void TLScalp2Entry::printData(std::ofstream & ostrm)
{
	ostrm << "\tTLScalp2EntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tADXBars = " << adxBars_ << "\n";
	ostrm << "\t\tATRBars = " << atrBars_ << "\n";
	ostrm << "\t\tSlopeBars = " << slopeBars_ << "\n";
	ostrm << "\t}" << std::endl;
}
void FiveMinuteEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tFiveMinuteEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}
void ANNEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tANNEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void CommitteeVoteEntry::printData(std::ofstream & ostrm)
{
	ostrm << "\tCommitteeVoteEntryRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tANN1Lower = " << ann1Lower_ << "\n";
	ostrm << "\t\tANN2Lower = " << ann2Lower_ << "\n";
	ostrm << "\t\tANN3Lower = " << ann3Lower_ << "\n";
	ostrm << "\t\tANN4Lower = " << ann4Lower_ << "\n";
	ostrm << "\t\tANN5Lower = " << ann5Lower_ << "\n";
	ostrm << "\t\tANN6Lower = " << ann6Lower_ << "\n";
	ostrm << "\t\tANN7Lower = " << ann5Lower_ << "\n";
	ostrm << "\t\tANN8Lower = " << ann6Lower_ << "\n";
/*	ostrm << "\t\tANN1ScaleType = " << ann1ScaleType_ << "\n";
	ostrm << "\t\tANN2ScaleType = " << ann2ScaleType_ << "\n";
	ostrm << "\t\tANN3ScaleType = " << ann3ScaleType_ << "\n";
	ostrm << "\t\tANN4ScaleType = " << ann4ScaleType_ << "\n";
	ostrm << "\t\tANN5ScaleType = " << ann5ScaleType_ << "\n";
	ostrm << "\t\tANN6ScaleType = " << ann6ScaleType_ << "\n";
	ostrm << "\t\tANN7ScaleType = " << ann7ScaleType_ << "\n";
	ostrm << "\t\tANN7ScaleType = " << ann8ScaleType_ << "\n";
*/
	ostrm << "\t}" << std::endl;
}

void ImprovedExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tImprovedExitRule" << "\n";
	ostrm << "\t{" << "\n";
//	ostrm << "\t\tPIPSTrail = " << pipsTrail_ << "\n";
	ostrm << "\t\tATRBars = " << atrBars_ << "\n";
	ostrm << "\t\tTimeExit = " << timeExit_ << "\n";
	ostrm << "\t\tmmstp = " << mmstp_ << "\n";
	ostrm << "\t\tptlim = " << ptlim_ << "\n";
	ostrm << "\t\tstpa = " << stpa_ << "\n";
	ostrm << "\t\tstpb = " << stpb_ << "\n";
	ostrm << "\t\tptga = " << ptga_ << "\n";
	ostrm << "\t}" << std::endl;
};

void FixedExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tFixedExitRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tTakeProfit = " << takeProfit_ << "\n";
	ostrm << "\t\tStopLoss = " << stopLoss_ << "\n";
	ostrm << "\t\tTimeExit = " <<timeExit_<< "\n";
	ostrm << "\t}" << std::endl;
};
void TestExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tTestExitRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
};
void HAExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tHAExitRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tTakeProfit = " << takeProfit_ << "\n";
	ostrm << "\t\tStopLoss = " << stopLoss_ << "\n";
	ostrm << "\t}" << std::endl;
};

void ExitExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tExitExitRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
};
void FXPrimeExitRule::printData(std::ofstream & ostrm)
{
	ostrm << "\tFXPrimeExitRule" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tStopLoss = " << stopLoss_ << "\n";
	ostrm << "\t\tTakeProfit = " << takeProfit_<< "\n";
	ostrm << "\t\tTrailTrigger = " << trailTrigger_<< "\n";
	ostrm << "\t\tPIPSTrail = " << trailStop_<< "\n";
	ostrm << "\t\tHAPipsExit = " << HAExitPips_<< "\n";
	ostrm << "\t}" << std::endl;
};

void OpenChaseMonitor::printData(std::ofstream & ostrm)
{
	ostrm << "\tOpenOrderChase" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void CloseChaseMonitor::printData(std::ofstream & ostrm)
{
	ostrm << "\tCloseOrderChase" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t}" << std::endl;
}

void TPSLCloseMonitor::printData(std::ofstream & ostrm)
{
	ostrm << "\tTPSLCloseMonitor" << "\n";
	ostrm << "\t{" << "\n";
	ostrm << "\t\tStopLoss = " << stopLoss_ << "\n";
	ostrm << "\t}" << std::endl;
}
