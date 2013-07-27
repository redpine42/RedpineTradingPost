header
{
#include <iostream>
#include <strstream>
#include <iomanip>

#include "MyDataTypes.h"

#ifndef PARSERTEST
#include "ConfigurationData.h"
#include "TimeZone.h"
#endif
}

options 
{
	language="Cpp";
}

class MyParser extends Parser;
options {
         defaultErrorHandler=false;
}


tokens 
{
    MBDEMOTRADING="MBDemoTrading";
    FOREXACCT="ForexAcct";  				// Trades Forex
    EQUITYACCT="EquityAcct";				// Trades Equity
    SIMULATETRADING="SimulateTrading";		// Simulated Trading against real account - Not Available
	TIMEZONE="TimeZone";					// Time zone. Currently support CET, EST and GMT
	MAXTRADES="MaxTrades"; 					// Can use to limit the number of trades in a run
	NUMCANDLEMINUTES="NumCandleMinutes";	// Number of minutes in a candlestick
	LOGPATH="LogPath";				 		// Location of trade log data
	LOGL1DATA="LogL1Data";

	CURRENCYPAIR="YesTLPair";			// Definition used in trading a currency pair
	VOLATILITYBREAKOUTWITHIMPROVEDEXIT="VolatilityBreakOutWImprovedExit";
	TRENDLINEWITHIMPROVEDEXIT="TrendLineWImprovedExit";
	DYNAMICDEFINITION="DynamicDefinition";
	ROCWITHIMPROVEDEXIT="ROCWImprovedExit";
	
	SYMBOL="Symbol";						// Currency pair symbol
	STARTTRADETIME="StartTradeTime";		// Start trade time
	ENDTRADETIME="EndTradeTime";			// End trade time
	FIRSTENTRYSIGNALTIME="FirstEntrySignalTime";		// Time that first trade is made
	CANDLESTICKVALUE="CandleSickValue";		// Values are OPEN, CLOSE, HIGH, LOW
	
	FIRSTTRENDLINETIME="FirstTrendLineTime";		// Time for first point in trend line
	SECONDTRENDLINETIME="SecondTrendLineTime";		// Time for second point in trend line
	
	PIPSTOPLOSS="PipsStopLoss";				//  Pips for stop loss
	STOPLOSS="StopLoss";				//  Pips for stop loss
	TRAILONECESTOPLOSSTRIGGER="TrailOnceStopLossTrigger";		//  Pips for Trail once stop loss to be recognized
	TRAILONCESTOPLOSS="TrailOnceStopLoss";			//  Pips new Stop Loss when trail once stop loss triggered.
	TAKEPROFIT="TakeProfit";
	PIPSPRECISION="PIPSPrecision";
	PIPSTRAIL="PIPSTrail";
	NUMBARS="NumBarsEvaluate";


	BACKFILEDATAFILE="BackFillDataFile";		// File Contain history data to load on startup
	DEFAULTLOTSIZE ="DefaultLotSize";
	TRENDLINEOPENPOSITION="TrendLineOpenPosition";
	
	MAXDRAWDOWN="MaxDrawDown";
	PERCENTRISK="PercentRisk";
	MAXDRAWDOWNPIPS="MaxDrawdownPips";
	NUMBERTRADES="NumberTrades";
	NUMBERWINS="NumberWins";


	MAXDRAWDOWNMSA="MaxDrawDownMSA";
 	MAXHISTDRAWDOWN="MaxHistDrawDown";		// USD Maximum historical drawdown
	CURRENTEQUITY="CurrentEquity";   		// USD Current equity amount available for trading this pair 
    MARGINPERCENTAGE="MarginPercentage";	// Percentage of required for margin
    MAXDDPERCENT ="MaxDDPercent";			// Max allowable draw down. Express as a percentage 
	TLCROSSTRADING = "TLCrossTrading";
	REVERSETRADING = "ReverseTrading";


	TL1BARS = "TL1Bars";
	TL2BARS = "TL2Bars";
	STOCHBARS = "StochBars";
	RSIBARS = "RSIBars";
	EMABARS = "EMABars";
	ATRMULT = "ATRMult";
	ATRBARS = "ATRBars";
	ENTRYATRBARS = "EntryATRBars";
	ADXBARS = "ADXBars";
	PLUSDIBARS = "PlusDIBars";
	MINUSDIBARS = "MinusDIBars";
	TIMEEXIT = "TimeExit";
	MMSTP = "mmstp";
	PTLIM = "ptlim";
	STPA = "stpa";
	STPB = "stpb";
	PTGA = "ptga";
	ROCBARS = "ROCBars";
	ROCCOUNT = "ROCCount";
	STDROCBARS = "StdROCBars";	
	SLOPEBARS = "SlopeBars";
	
	TLENDTIME = "TLEndTime";

	SPREADPRICING="SpreadPricing";
	MARKETPRICING="MarketPricing";
	MARKETTPLIMITPRICING="MarketTPLimitPricing";
	PIPSTAKEPROFIT="PipsTakeProfit";
	HALFBARPRICING="HalfBarLimitPrice";
	MATCHBIDPRICING="MatchBidLimitPricing";


	VOLATILITYBREAKOUTENTRYRULE="VolatilityBreakoutEntryRule";
	TURTLEBREAKOUTENTRYRULE="TurtleBreakoutEntryRule";
	TRIPPLEMVAENTRYRULE="TrippleMVAEntryRule";
	EMASCALPENTRYRULE="EMAScalpEntryRule";
	TLSCALPENTRYRULE="TLScalpEntryRule";
	TLSCALP2ENTRYRULE="TLScalp2EntryRule";
	ADXENTRYRULE = "ADXEntry";
	FIVMINUTEENTRYRULE = "FiveMinuteEntryRule";
	INVERTTRADE="InvertTrade";
	BARSFAST="BarsFast";
	BARSMEDIUM="BarsMedium";
	BARSSLOW="BarsSlow";

	IMPROVEDEXITRULE="ImprovedExitRule";
	FIXEDEXITRULE="FixedExitRule";
	EXITEXITRULE="ExitExitRule";

	OPENORDERCHASE="OpenOrderChase";
	CLOSEORDERCHASE="CloseOrderChase";
	TPSLCLOSEMONITOR="TPSLCloseMonitor";



}

{

	struct TimeData
	{
		int hour;
		int minutes;
		int seconds;

		std::string str()
		{
			std::strstream strstr;
			strstr.fill('0');
		    strstr << std::setw(2) << hour << ":" << std::setw(2) << minutes << ":" << std::setw(2) << seconds << std::ends;
			std::string  ret = strstr.str();
		    strstr.clear();
		    strstr.rdbuf()->freeze(0);
			return ret;
		}
	};
}

fileparser : (configfile);

configfile 
	:	systemconfigitem (NEWLINE systemconfigitem)* 
	|	pairconfigitem (NEWLINE pairconfigitem)*
	;
	
systemconfigitem {bool bVal=false;}
	:	MBDEMOTRADING  ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "MBDEMOTRADING: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->MBDemoTrading(bVal);
		#endif
		}
    |	FOREXACCT ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "FOREXACCT: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->forexAcct(bVal);
		#endif
		}
    |	EQUITYACCT ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "EQUITYACCT: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->equityAcct(bVal);
		#endif
		}
    |	SIMULATETRADING ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "SIMULATETRADING: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->simulationTrades(bVal);
		#endif
		}
    |	LOGL1DATA ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "LOGL1DATA: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->logL1Data(bVal);
		#endif
		}
	|	TIMEZONE ASSIGN id1:ID						
		{
		#ifdef PARSERTEST
			std::cout << "TIMEZONE: " << id1->getText() << std::endl;
		#else
			ConfigurationData::instance()->timeZone(id1->getText());
		#endif
		}
	|	MAXTRADES ASSIGN int1:INT					
		{
		#ifdef PARSERTEST
			std::cout << "MAXTRADES: " << int1->getText() << std::endl;
		#else
			ConfigurationData::instance()->maxTrades(atoi(int1->getText().c_str()));
		#endif
		}
	|	NUMCANDLEMINUTES ASSIGN float1:FLOAT		
		{
		#ifdef PARSERTEST
			std::cout << "NUMCANDLEMINUTES: " << float1->getText() << std::endl;
		#else
			ConfigurationData::instance()->numCandleMinutes(atof(float1->getText().c_str()));
		#endif
		}
    |	CANDLESTICKVALUE ASSIGN id2:ID		
		{
		#ifdef PARSERTEST
			std::cout << "CANDLESTICKVALUES: " << id2->getText() << std::endl;
		#else
			ConfigurationData::instance()->candleStickVal(id2->getText());
		#endif
		}
	|	LOGPATH ASSIGN id3:STRING_LITERAL
		{
			std::string newString = id3->getText();
			newString.erase(newString.length()-1,1);
			newString.erase(0,1);
		#ifdef PARSERTEST
			std::cout << "LOGPATH: " << newString << std::endl;
		#else
			ConfigurationData::instance()->logPath(newString);
		#endif
		}
	|	TRENDLINEOPENPOSITION ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "TRENDLINEOPENPOSITION: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->trendLineOpenPosition(bVal);
		#endif
		}
	|	TLCROSSTRADING ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "TLCROSSTRADING: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->TLCrossTrading(bVal);
		#endif
		}
	|	REVERSETRADING ASSIGN bVal=boolean_literal	
		{
		#ifdef PARSERTEST
			std::cout << "REVERSETRADING: " << bVal << std::endl;
		#else
			ConfigurationData::instance()->reverseTrading(bVal);
		#endif
		}
	;
	
pairconfigitem 
	{
			TLSymbolData * data = new TLSymbolData();
			data->msaData_ = 0;
			data->maxDDData_ = 0;
			data->defaultLotSize_ = -1;
			data->pipsPrecision_ = 0.0001;

			VolatilityBreakOutWImprovedExitData * vbedata = new VolatilityBreakOutWImprovedExitData();
			vbedata->msaData_ = 0;
			vbedata->maxDDData_ = 0;
			vbedata->defaultLotSize_ = -1;
			vbedata->pipsPrecision_ = 0.0001;
			vbedata->pipsTrail_ = 10;
			vbedata->invertTrade_ = false;

			TrendLineWImprovedExitData * tledata = new TrendLineWImprovedExitData();
			tledata->msaData_ = 0;
			tledata->maxDDData_ = 0;
			tledata->defaultLotSize_ = -1;
			tledata->pipsPrecision_ = 0.0001;
			tledata->pipsTrail_ = 10;
			tledata->invertTrade_ = false;

			ROCWImprovedExitData * rocdata = new ROCWImprovedExitData();
			rocdata->msaData_ = 0;
			rocdata->maxDDData_ = 0;
			rocdata->defaultLotSize_ = -1;
			rocdata->pipsPrecision_ = 0.0001;
			rocdata->pipsTrail_ = 10;
			rocdata->invertTrade_ = false;

			DynamicRulesData * rulesdata = new DynamicRulesData();
			rulesdata->msaData_ = 0;
			rulesdata->maxDDData_ = 0;
			rulesdata->priceRule_ = 0;
			rulesdata->entryRule_ = 0;
			rulesdata->exitRule_ = 0;
			rulesdata->openMonitor_ = 0;
			rulesdata->closeMonitor_ = 0;

			rulesdata->defaultLotSize_ = -1;
			rulesdata->pipsPrecision_ = 0.0001;


			std::string symbol;
			std::string dummyS;
	}
	 : CURRENCYPAIR LCURLY symbol=pairitemlist[data] (dummyS=pairitemlist[data])+ RCURLY
		{
			delete vbedata;
			delete rulesdata;
			delete tledata;
			delete rocdata;
		#ifndef PARSERTEST
			ConfigurationData::instance()->symbolData(symbol, data);
			data = 0;
		#endif
		}	
	| VOLATILITYBREAKOUTWITHIMPROVEDEXIT LCURLY symbol=volbreakoutwepairitemlist[vbedata] (dummyS=volbreakoutwepairitemlist[vbedata])+ RCURLY
		{
			delete data;
			delete rulesdata;
			delete tledata;
			delete rocdata;
		#ifndef PARSERTEST
			ConfigurationData::instance()->symbolData(symbol, vbedata);
		#endif
		}	
	| TRENDLINEWITHIMPROVEDEXIT LCURLY symbol=trendlinewepairitemlist[tledata] (dummyS=trendlinewepairitemlist[tledata])+ RCURLY
		{
			delete data;
			delete rulesdata;
			delete vbedata;
			delete rocdata;
		#ifndef PARSERTEST
			ConfigurationData::instance()->symbolData(symbol, tledata);
		#endif
		}	
	| ROCWITHIMPROVEDEXIT LCURLY symbol=rocwepairitemlist[rocdata] (dummyS=rocwepairitemlist[rocdata])+ RCURLY
		{
			delete data;
			delete rulesdata;
			delete vbedata;
			delete tledata;
		#ifndef PARSERTEST
			ConfigurationData::instance()->symbolData(symbol, rocdata);
		#endif
		}	
	| DYNAMICDEFINITION LCURLY symbol=dynamicpairs[rulesdata] (dummyS=dynamicpairs[rulesdata])+ RCURLY
		{
			delete data;
			delete vbedata;
			delete tledata;
			delete rocdata;
		#ifndef PARSERTEST
			ConfigurationData::instance()->symbolData(symbol, rulesdata);
		#endif
		}	
	;

pairitemlist[TLSymbolData * data] returns [std::string symbol]
	{
		MyParser::TimeData timeData;
	}
	:	SYMBOL ASSIGN id1:ID								
		{
		#ifdef PARSERTEST
			std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
		#else
			symbol = id1->getText();
		#endif
		}
	 	STARTTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	ENDTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	FIRSTENTRYSIGNALTIME ASSIGN timeData=time				
		{
		#ifdef PARSERTEST
			std::cout << "\tFIRSTENTRYSIGNALTIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->firstEntrySignalTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	FIRSTTRENDLINETIME ASSIGN timeData=time					
		{
		#ifdef PARSERTEST
			std::cout << "\tFIRSTTRENDLINETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->TLStartTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	SECONDTRENDLINETIME ASSIGN timeData=time				
		{
		#ifdef PARSERTEST
			std::cout << "\tSECONDTRENDLINETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->TLEndTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	PIPSTOPLOSS ASSIGN int1:INT							
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSTOPLOSS: " << int1->getText() << std::endl;
		#else
			data->pipsStopLoss_ = double(atoi(int1->getText().c_str()));
		#endif
		}
	|	TRAILONECESTOPLOSSTRIGGER ASSIGN int2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTRAILONECESTOPLOSSTRIGGER: " << int2->getText() << std::endl;
		#else
			data->trailOnceStopLossTrigger_ = double(atoi(int2->getText().c_str()));
		#endif
		}
	|	TRAILONCESTOPLOSS ASSIGN int3:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tTRAILONCESTOPLOSS: " << int3->getText() << std::endl;
		#else
			data->trailOnceStopLoss_ = double(atoi(int3->getText().c_str()));
		#endif
		}
	|	PIPSPRECISION ASSIGN float1:FLOAT					
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
		#else
			data->pipsPrecision_ = atof(float1->getText().c_str());
		#endif
		}
	|	DEFAULTLOTSIZE ASSIGN int4:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tDEFAULTLOTSIZE: " << int4->getText() << std::endl;
		#else
			data->defaultLotSize_ = 0;
			data->defaultLotSize_ = atoi(int4->getText().c_str());
		#endif
		}
	|	msarules[data]
	|	maxddrules[data]
	;

	
dynamicpairs[DynamicRulesData * rulesdata] returns [std::string symbol]
	{
		MyParser::TimeData timeData;
	}
	:	SYMBOL ASSIGN id1:ID								
		{
		#ifdef PARSERTEST
			std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
		#else
			symbol = id1->getText();
		#endif
		}
	 	STARTTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			rulesdata->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	ENDTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			rulesdata->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	PIPSPRECISION ASSIGN float1:FLOAT					
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
		#else
			rulesdata->pipsPrecision_ = atof(float1->getText().c_str());
		#endif
		}
	|	DEFAULTLOTSIZE ASSIGN int4:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tDEFAULTLOTSIZE: " << int4->getText() << std::endl;
		#else
			rulesdata->defaultLotSize_ = 0;
			rulesdata->defaultLotSize_ = atoi(int4->getText().c_str());
		#endif
		}
	|	msarules[rulesdata]
	|	maxddrules[rulesdata]
	|	pricing[rulesdata]
	|	entryrules[rulesdata]
	|	exitrules[rulesdata]
	|	openmonitor[rulesdata]
	|	closemonitor[rulesdata]
	;


pricing[DynamicRulesData * rulesdata]
	: SPREADPRICING LCURLY spreadPricing[rulesdata](spreadPricing[rulesdata])+ RCURLY
	| MARKETPRICING LCURLY RCURLY {rulesdata->priceRule_ = new MarketPricingRule();}
	| HALFBARPRICING LCURLY RCURLY {rulesdata->priceRule_ = new HalfBarPricingRule();}
	| MATCHBIDPRICING LCURLY RCURLY {rulesdata->priceRule_ = new MatchBidPricingRule();}
	| MARKETTPLIMITPRICING LCURLY marketTPLimitPricing[rulesdata] RCURLY
	;

entryrules[DynamicRulesData * rulesdata]
	: VOLATILITYBREAKOUTENTRYRULE LCURLY volatiltiyEntry[rulesdata](volatiltiyEntry[rulesdata])+ RCURLY
	| TURTLEBREAKOUTENTRYRULE LCURLY turtleEntry[rulesdata](turtleEntry[rulesdata])+ RCURLY
	| TRIPPLEMVAENTRYRULE LCURLY trippleMVAEntry[rulesdata](trippleMVAEntry[rulesdata])+ RCURLY
	| ADXENTRYRULE LCURLY adxEntry[rulesdata](adxEntry[rulesdata])+ RCURLY
	| EMASCALPENTRYRULE LCURLY emaScalpEntry[rulesdata](emaScalpEntry[rulesdata])+ RCURLY
	| TLSCALPENTRYRULE LCURLY tlScalpEntry[rulesdata](tlScalpEntry[rulesdata])+ RCURLY
	| TLSCALP2ENTRYRULE LCURLY tlScalp2Entry[rulesdata](tlScalp2Entry[rulesdata])+ RCURLY
	| FIVMINUTEENTRYRULE LCURLY RCURLY {if(0 == rulesdata->entryRule_){rulesdata->entryRule_ = new FiveMinuteEntry();}}
	;
exitrules[DynamicRulesData * rulesdata]
	: IMPROVEDEXITRULE LCURLY improvedExit[rulesdata](improvedExit[rulesdata])+ RCURLY
	| FIXEDEXITRULE LCURLY fixedExit[rulesdata](fixedExit[rulesdata])+ RCURLY
	| EXITEXITRULE LCURLY RCURLY {rulesdata->exitRule_ = new ExitExitRule();}
	;
openmonitor[DynamicRulesData * rulesdata]
	: OPENORDERCHASE LCURLY RCURLY {rulesdata->openMonitor_ = new OpenChaseMonitor();}
	;

closemonitor[DynamicRulesData * rulesdata]
	: CLOSEORDERCHASE LCURLY RCURLY {rulesdata->closeMonitor_ = new CloseChaseMonitor();}
	| TPSLCLOSEMONITOR LCURLY tpslCloseMonitor[rulesdata] RCURLY
	;

improvedExit[DynamicRulesData * rulesdata]
	 {
		ImprovedExitRule * data = 0;
		if(0 == rulesdata->exitRule_)
		{
			data = new ImprovedExitRule();
			data->pipsTrail_ = 10;
			rulesdata->exitRule_ = data;
		}
		else 
		{
			data = dynamic_cast<ImprovedExitRule*>(rulesdata->exitRule_);
		}
	 }
	:	PIPSTRAIL ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSTRAIL: " << int3->getText() << std::endl;
		#else
			data->pipsTrail_ = atoi(int3->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int4->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int4->getText().c_str());
		#endif
		}
	|	TIMEEXIT ASSIGN int5:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
		#else
			data->timeExit_ = atoi(int5->getText().c_str());
		#endif
		}
	|	MMSTP ASSIGN float2:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tMMSTP: " << float2->getText() << std::endl;
		#else
			data->mmstp_ = atof(float2->getText().c_str());
		#endif
		}
	|	PTLIM ASSIGN float3:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTLIM: " << float3->getText() << std::endl;
		#else
			data->ptlim_ = atof(float3->getText().c_str());
		#endif
		}
	|	STPA ASSIGN float4:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPA: " << float4->getText() << std::endl;
		#else
			data->stpa_ = atof(float4->getText().c_str());
		#endif
		}
	|	STPB ASSIGN float5:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPB: " << float5->getText() << std::endl;
		#else
			data->stpb_ = atof(float5->getText().c_str());
		#endif
		}
	|	PTGA ASSIGN float6:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTGA: " << float6->getText() << std::endl;
		#else
			data->ptga_ = atof(float6->getText().c_str());
		#endif
		}
	;

tpslCloseMonitor[DynamicRulesData * rulesdata]
	 {
		TPSLCloseMonitor * data = 0;
		if(0 == rulesdata->closeMonitor_)
		{
			data = new TPSLCloseMonitor();
			rulesdata->closeMonitor_ = data;
		}
		else 
		{
			data = dynamic_cast<TPSLCloseMonitor*>(rulesdata->closeMonitor_);
		}
	 }
	:	STOPLOSS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTOPLOSS: " << int4->getText() << std::endl;
		#else
			data->stopLoss_ = atoi(int4->getText().c_str());
		#endif
		}
	;

marketTPLimitPricing[DynamicRulesData * rulesdata]
	 {
		MarketTPLimitPricingRule * data = 0;
		if(0 == rulesdata->priceRule_)
		{
			data = new MarketTPLimitPricingRule();
			rulesdata->priceRule_ = data;
		}
		else 
		{
			data = dynamic_cast<MarketTPLimitPricingRule*>(rulesdata->priceRule_);
		}
	 }
	:	TAKEPROFIT ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTAKEPROFIT: " << int3->getText() << std::endl;
		#else
			data->takeProfit_ = atoi(int3->getText().c_str());
		#endif
		}
	;


	
fixedExit[DynamicRulesData * rulesdata]
	 {
		FixedExitRule * data = 0;
		if(0 == rulesdata->exitRule_)
		{
			data = new FixedExitRule();
			rulesdata->exitRule_ = data;
		}
		else 
		{
			data = dynamic_cast<FixedExitRule*>(rulesdata->exitRule_);
		}
	 }
	:	TAKEPROFIT ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTAKEPROFIT: " << int3->getText() << std::endl;
		#else
			data->takeProfit_ = atoi(int3->getText().c_str());
		#endif
		}
	|	STOPLOSS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTOPLOSS: " << int4->getText() << std::endl;
		#else
			data->stopLoss_ = atoi(int4->getText().c_str());
		#endif
		}
	;


volatiltiyEntry[DynamicRulesData * rulesdata]
	 {
		bool bVal=false;
		VolatilityBreakoutEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new VolatilityBreakoutEntry();
			rulesdata->entryRule_ = data;
			data->invertTrade_ = false;
		}
		else 
		{
			data = dynamic_cast<VolatilityBreakoutEntry*>(rulesdata->entryRule_);
		}
	 }
    :	INVERTTRADE ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "INVERTTRADE: " << bVal << std::endl;
		#else
			data->invertTrade_ = bVal;
		#endif
		}
	|	ATRBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int4->getText() << std::endl;
		#else
			data->ATRBars_ = atoi(int4->getText().c_str());
		#endif
		}
	|	ATRMULT ASSIGN float7:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRMULT: " << float7->getText() << std::endl;
		#else
			data->ATRMult_ = atof(float7->getText().c_str());
		#endif
		}
	|	EMABARS ASSIGN int8:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tEMABARS: " << int8->getText() << std::endl;
		#else
			data->EMABars_ = atoi(int8->getText().c_str());
		#endif
		}
	;

turtleEntry[DynamicRulesData * rulesdata]
	 {
		TurtleBreakoutEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new TurtleBreakoutEntry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<TurtleBreakoutEntry*>(rulesdata->entryRule_);
		}
	 }
	:	NUMBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tNUMBARS: " << int4->getText() << std::endl;
		#else
			data->numBars_ = atoi(int4->getText().c_str());
		#endif
		}
	;

trippleMVAEntry[DynamicRulesData * rulesdata]
	 {
		TripleMVAEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new TripleMVAEntry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<TripleMVAEntry*>(rulesdata->entryRule_);
		}
	 }
	:	BARSFAST ASSIGN float1:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tBARSFAST: " << float1->getText() << std::endl;
		#else
			data->fast_ = atoi(float1->getText().c_str());
		#endif
		}
	|	BARSMEDIUM ASSIGN float2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tBARSMEDIUM: " << float2->getText() << std::endl;
		#else
			data->medium_ = atoi(float2->getText().c_str());
		#endif
		}
	|	BARSSLOW ASSIGN float7:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tBARSSLOW: " << float7->getText() << std::endl;
		#else
			data->slow_ = atoi(float7->getText().c_str());
		#endif
		}
	;
adxEntry[DynamicRulesData * rulesdata]
	 {
		ADXEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new ADXEntry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<ADXEntry*>(rulesdata->entryRule_);
		}
	 }
	:	ADXBARS ASSIGN int1:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tADXBARS: " << int1->getText() << std::endl;
		#else
			data->adxBars_ = atoi(int1->getText().c_str());
		#endif
		}
	|	PLUSDIBARS ASSIGN int2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPLUSDIBARS: " << int2->getText() << std::endl;
		#else
			data->plusDIBars_ = atoi(int2->getText().c_str());
		#endif
		}
	|	MINUSDIBARS ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tMINUSDIBARS: " << int3->getText() << std::endl;
		#else
			data->minusDIBars_ = atoi(int3->getText().c_str());
		#endif
		}
	;
emaScalpEntry[DynamicRulesData * rulesdata]
	 {
		EMAScalpEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new EMAScalpEntry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<EMAScalpEntry*>(rulesdata->entryRule_);
		}
	 }
	:	ADXBARS ASSIGN int1:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tADXBARS: " << int1->getText() << std::endl;
		#else
			data->adxBars_ = atoi(int1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int2->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int2->getText().c_str());
		#endif
		}
	|	EMABARS ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tEMABARS: " << int3->getText() << std::endl;
		#else
			data->emaBars_ = atoi(int3->getText().c_str());
		#endif
		}
	;
tlScalpEntry[DynamicRulesData * rulesdata]
	 {
		MyParser::TimeData timeData;
		TLScalpEntry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new TLScalpEntry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<TLScalpEntry*>(rulesdata->entryRule_);
		}
	 }
	:	ADXBARS ASSIGN int1:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tADXBARS: " << int1->getText() << std::endl;
		#else
			data->adxBars_ = atoi(int1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int2->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int2->getText().c_str());
		#endif
		}
	|	SLOPEBARS ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSLOPEBARS: " << int3->getText() << std::endl;
		#else
			data->slopeBars_ = atoi(int3->getText().c_str());
		#endif
		}
	|	TLENDTIME ASSIGN timeData=time				
		{
		#ifdef PARSERTEST
			std::cout << "\tTLENDTIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->tlEndTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	;
tlScalp2Entry[DynamicRulesData * rulesdata]
	 {
		TLScalp2Entry * data = 0;
		if(0 == rulesdata->entryRule_)
		{
			data = new TLScalp2Entry();
			rulesdata->entryRule_ = data;
		}
		else 
		{
			data = dynamic_cast<TLScalp2Entry*>(rulesdata->entryRule_);
		}
	 }
	:	ADXBARS ASSIGN int1:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tADXBARS: " << int1->getText() << std::endl;
		#else
			data->adxBars_ = atoi(int1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int2:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int2->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int2->getText().c_str());
		#endif
		}
	|	SLOPEBARS ASSIGN int3:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSLOPEBARS: " << int3->getText() << std::endl;
		#else
			data->slopeBars_ = atoi(int3->getText().c_str());
		#endif
		}
	;
spreadPricing[DynamicRulesData * rulesdata]
	 {
		SpreadPricing * data = 0;
		if(0 == rulesdata->priceRule_)
		{
			data = new SpreadPricing();
			rulesdata->priceRule_ = data;
		}
		else 
		{
			data = dynamic_cast<SpreadPricing*>(rulesdata->priceRule_);
		}
	 }
	:	PIPSTOPLOSS ASSIGN float1:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\n\tSpread Pricing rules!\n\t\tPIPSTOPLOSS: " << float1->getText() << std::endl;
		#else
			data->pipsStopLoss_ = atof(float1->getText().c_str());
		#endif
		}
	|	PIPSTAKEPROFIT ASSIGN float2:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tPIPSTAKEPROFIT: " << float2->getText() << std::endl;
		#else
			data->pipsTakeProfit_ = atof(float2->getText().c_str());
		#endif
		}
	;

volbreakoutwepairitemlist[VolatilityBreakOutWImprovedExitData * data] returns [std::string symbol]
	{
		bool bVal=false;
		MyParser::TimeData timeData;
//		std::string symbol;
	}
	:	SYMBOL ASSIGN id1:ID								
		{
		#ifdef PARSERTEST
			std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
		#else
			symbol = id1->getText();
		#endif
		}
    |	INVERTTRADE ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "INVERTTRADE: " << bVal << std::endl;
		#else
			data->invertTrade_ = bVal;
		#endif
		}
	| 	STARTTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	ENDTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	PIPSTRAIL ASSIGN int9:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
		#else
			data->pipsTrail_ = atoi(int9->getText().c_str());
		#endif
		}
	|	PIPSPRECISION ASSIGN float1:FLOAT					
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
		#else
			data->pipsPrecision_ = atof(float1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int4->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int4->getText().c_str());
		#endif
		}
	|	ENTRYATRBARS ASSIGN int14:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tENTRYATRBARS: " << int14->getText() << std::endl;
		#else
			data->entryATRBars_ = atoi(int14->getText().c_str());
		#endif
		}
	|	ATRMULT ASSIGN float7:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRMULT: " << float7->getText() << std::endl;
		#else
			data->ATRMult_ = atof(float7->getText().c_str());
		#endif
		}
	|	EMABARS ASSIGN int8:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tEMABARS: " << int8->getText() << std::endl;
		#else
			data->EMABars_ = atoi(int8->getText().c_str());
		#endif
		}
	|	TIMEEXIT ASSIGN int5:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
		#else
			data->timeExit_ = atoi(int5->getText().c_str());
		#endif
		}
	|	MMSTP ASSIGN float2:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tMMSTP: " << float2->getText() << std::endl;
		#else
			data->mmstp_ = atof(float2->getText().c_str());
		#endif
		}
	|	PTLIM ASSIGN float3:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTLIM: " << float3->getText() << std::endl;
		#else
			data->ptlim_ = atof(float3->getText().c_str());
		#endif
		}
	|	STPA ASSIGN float4:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPA: " << float4->getText() << std::endl;
		#else
			data->stpa_ = atof(float4->getText().c_str());
		#endif
		}
	|	STPB ASSIGN float5:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPB: " << float5->getText() << std::endl;
		#else
			data->stpb_ = atof(float5->getText().c_str());
		#endif
		}
	|	PTGA ASSIGN float6:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTGA: " << float6->getText() << std::endl;
		#else
			data->ptga_ = atof(float6->getText().c_str());
		#endif
		}
	|	DEFAULTLOTSIZE ASSIGN int6:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
		#else
			data->defaultLotSize_ = 0;
			data->defaultLotSize_ = atoi(int6->getText().c_str());
		#endif
		}
	|	msarules[data]
	|	maxddrules[data]
	;
	
trendlinewepairitemlist[TrendLineWImprovedExitData * data] returns [std::string symbol]
	{
		bool bVal=false;
		MyParser::TimeData timeData;
//		std::string symbol;
	}
	:	SYMBOL ASSIGN id1:ID								
		{
		#ifdef PARSERTEST
			std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
		#else
			symbol = id1->getText();
		#endif
		}
    |	INVERTTRADE ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "INVERTTRADE: " << bVal << std::endl;
		#else
			data->invertTrade_ = bVal;
		#endif
		}
	| 	STARTTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	ENDTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	PIPSTRAIL ASSIGN int9:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
		#else
			data->pipsTrail_ = atoi(int9->getText().c_str());
		#endif
		}
	|	PIPSPRECISION ASSIGN float1:FLOAT					
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
		#else
			data->pipsPrecision_ = atof(float1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int4->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int4->getText().c_str());
		#endif
		}
	|	TL1BARS ASSIGN int10:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTL1BARS: " << int10->getText() << std::endl;
		#else
			data->TL1Bars_ = atoi(int10->getText().c_str());
		#endif
		}
	|	TL2BARS ASSIGN int8:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTL2BARS: " << int8->getText() << std::endl;
		#else
			data->TL2Bars_ = atoi(int8->getText().c_str());
		#endif
		}
	|	RSIBARS ASSIGN int11:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tRSIBARS: " << int11->getText() << std::endl;
		#else
			data->RSIBars_ = atoi(int11->getText().c_str());
		#endif
		}
	|	STOCHBARS ASSIGN int12:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTOCHBARS: " << int12->getText() << std::endl;
		#else
			data->StochBars_ = atoi(int12->getText().c_str());
		#endif
		}
	|	TIMEEXIT ASSIGN int5:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
		#else
			data->timeExit_ = atoi(int5->getText().c_str());
		#endif
		}
	|	MMSTP ASSIGN float2:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tMMSTP: " << float2->getText() << std::endl;
		#else
			data->mmstp_ = atof(float2->getText().c_str());
		#endif
		}
	|	PTLIM ASSIGN float3:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTLIM: " << float3->getText() << std::endl;
		#else
			data->ptlim_ = atof(float3->getText().c_str());
		#endif
		}
	|	STPA ASSIGN float4:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPA: " << float4->getText() << std::endl;
		#else
			data->stpa_ = atof(float4->getText().c_str());
		#endif
		}
	|	STPB ASSIGN float5:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPB: " << float5->getText() << std::endl;
		#else
			data->stpb_ = atof(float5->getText().c_str());
		#endif
		}
	|	PTGA ASSIGN float6:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTGA: " << float6->getText() << std::endl;
		#else
			data->ptga_ = atof(float6->getText().c_str());
		#endif
		}
	|	DEFAULTLOTSIZE ASSIGN int6:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
		#else
			data->defaultLotSize_ = 0;
			data->defaultLotSize_ = atoi(int6->getText().c_str());
		#endif
		}
	|	msarules[data]
	|	maxddrules[data]
	;
	
	rocwepairitemlist[ROCWImprovedExitData * data] returns [std::string symbol]
	{
		bool bVal=false;
		MyParser::TimeData timeData;
//		std::string symbol;
	}
	:	SYMBOL ASSIGN id1:ID								
		{
		#ifdef PARSERTEST
			std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
		#else
			symbol = id1->getText();
		#endif
		}
    |	INVERTTRADE ASSIGN bVal=boolean_literal		
		{
		#ifdef PARSERTEST
			std::cout << "INVERTTRADE: " << bVal << std::endl;
		#else
			data->invertTrade_ = bVal;
		#endif
		}
	| 	STARTTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	ENDTRADETIME ASSIGN timeData=time						
		{
		#ifdef PARSERTEST
			std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
		#else
			long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
			data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
		#endif
		}
	|	PIPSTRAIL ASSIGN int9:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
		#else
			data->pipsTrail_ = atoi(int9->getText().c_str());
		#endif
		}
	|	PIPSPRECISION ASSIGN float1:FLOAT					
		{
		#ifdef PARSERTEST
			std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
		#else
			data->pipsPrecision_ = atof(float1->getText().c_str());
		#endif
		}
	|	ATRBARS ASSIGN int4:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tATRBARS: " << int4->getText() << std::endl;
		#else
			data->atrBars_ = atoi(int4->getText().c_str());
		#endif
		}
	|	ADXBARS ASSIGN int10:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tADXBARS: " << int10->getText() << std::endl;
		#else
			data->adxBars_ = atoi(int10->getText().c_str());
		#endif
		}
	|	ROCBARS ASSIGN int8:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tROCBARS: " << int8->getText() << std::endl;
		#else
			data->rocBars_ = atoi(int8->getText().c_str());
		#endif
		}
	|	ROCCOUNT ASSIGN int11:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tROCCOUNT: " << int11->getText() << std::endl;
		#else
			data->ROCCount_ = atoi(int11->getText().c_str());
		#endif
		}
	|	STDROCBARS ASSIGN int12:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTDROCBARS: " << int12->getText() << std::endl;
		#else
			data->stdROCBars_ = atoi(int12->getText().c_str());
		#endif
		}
	|	TIMEEXIT ASSIGN int5:INT			
		{
		#ifdef PARSERTEST
			std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
		#else
			data->timeExit_ = atoi(int5->getText().c_str());
		#endif
		}
	|	MMSTP ASSIGN float2:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tMMSTP: " << float2->getText() << std::endl;
		#else
			data->mmstp_ = atof(float2->getText().c_str());
		#endif
		}
	|	PTLIM ASSIGN float3:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTLIM: " << float3->getText() << std::endl;
		#else
			data->ptlim_ = atof(float3->getText().c_str());
		#endif
		}
	|	STPA ASSIGN float4:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPA: " << float4->getText() << std::endl;
		#else
			data->stpa_ = atof(float4->getText().c_str());
		#endif
		}
	|	STPB ASSIGN float5:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tSTPB: " << float5->getText() << std::endl;
		#else
			data->stpb_ = atof(float5->getText().c_str());
		#endif
		}
	|	PTGA ASSIGN float6:FLOAT			
		{
		#ifdef PARSERTEST
			std::cout << "\tPTGA: " << float6->getText() << std::endl;
		#else
			data->ptga_ = atof(float6->getText().c_str());
		#endif
		}
	|	DEFAULTLOTSIZE ASSIGN int6:INT					
		{
		#ifdef PARSERTEST
			std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
		#else
			data->defaultLotSize_ = 0;
			data->defaultLotSize_ = atoi(int6->getText().c_str());
		#endif
		}
	|	msarules[data]
	|	maxddrules[data]
	;
	
msarules[SymbolData * data]
	: MAXDRAWDOWNMSA LCURLY msarule[data](msarule[data])+ RCURLY
	;
	
msarule[SymbolData * data]
	 {
		if(0 == data->msaData_)
		{
			data->msaData_ = new MaxDDMSAData();
		}
	 }
	:	MAXHISTDRAWDOWN ASSIGN float1:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\n\tMax DD MSA Rule!\n\t\tMAXHISTDRAWDOWN: " << float1->getText() << std::endl;
		#else
			data->msaData_->maxHistDrawDown_ = atof(float1->getText().c_str());
		#endif
		}
	|	CURRENTEQUITY ASSIGN float3:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tCURRENTEQUITY: " << float3->getText() << std::endl;
		#else
			data->msaData_->currentEquity_ = atof(float3->getText().c_str());
		#endif
		}
    |	MARGINPERCENTAGE ASSIGN float4:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tMARGINPERCENTAGE: " << float4->getText() << std::endl;
		#else
			data->msaData_->marginPercentage_ = atof(float4->getText().c_str());
		#endif
		}
    |	MAXDDPERCENT ASSIGN float5:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tMAXDDPERCENT: " << float5->getText() << std::endl;
		#else
			data->msaData_->maxDDPercent_ = atof(float5->getText().c_str());
		#endif
		}
	;
maxddrules[SymbolData * data]
	: MAXDRAWDOWN LCURLY maxddrule[data](maxddrule[data])+ RCURLY
	;
	
maxddrule[SymbolData * data]
	 {
		if(0 == data->maxDDData_)
		{
			data->maxDDData_ = new MaxDDData();
		}
	 }
	:	PERCENTRISK ASSIGN float1:FLOAT
		{
		#ifdef PARSERTEST
			std::cout << "\n\tMax DD Rule!\n\t\tPERCENTRISK: " << float1->getText() << std::endl;
		#else
			data->maxDDData_->percentRisk_ = atof(float1->getText().c_str());
		#endif
		}
	|	MAXDRAWDOWNPIPS ASSIGN int1:INT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tMAXDRAWDOWNPIPS: " << int1->getText() << std::endl;
		#else
			data->maxDDData_->maxDDPips_ = atoi(int1->getText().c_str());
		#endif
		}
    |	NUMBERTRADES ASSIGN int2:INT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tNUMBERTRADES: " << int2->getText() << std::endl;
		#else
			data->maxDDData_->numTrades_ = atoi(int2->getText().c_str());
		#endif
		}
    |	NUMBERWINS ASSIGN int3:INT
		{
		#ifdef PARSERTEST
			std::cout << "\t\tNUMBERWINS: " << int3->getText() << std::endl;
		#else
			data->maxDDData_->numWins_ = atoi(int3->getText().c_str());
		#endif
		}
	;

time returns [MyParser::TimeData data]
	: int1:INT COLON int2:INT COLON int3:INT {data.hour=atoi(int1->getText().c_str());data.minutes=atoi(int2->getText().c_str());data.seconds=atoi(int3->getText().c_str());}
	;

boolean_literal returns [bool retVal=false]

	:   "TRUE" {retVal= true;}
	|   "FALSE" {retVal= false;}
	|	"True" {retVal =true;}
	|	"False" {retVal= false;}
	|	"true" {retVal= true;}
	|	"false" {retVal= false;}
	;


class MyLexer extends Lexer;
options {
	k=4;
	filter=true;
}

{
public:
	bool done;


	void uponEOF()
	{
		done = true;
	}
}

SEMI
options {
  paraphrase = ";";
}
	:	';'
	;

QUESTION
options {
  paraphrase = "?";
}
	:	'?'
	;

LPAREN
options {
  paraphrase = "(";
}
	:	'('
	;

RPAREN
options {
  paraphrase = ")";
}
	:	')'
	;

LBRACK
options {
  paraphrase = "[";
}
	:	'['
	;

RBRACK
options {
  paraphrase = "]";
}
	:	']'
	;

LCURLY
options {
  paraphrase = "{";
}
	:	'{'
	;

RCURLY
options {
  paraphrase = "}";
}
	:	'}'
	;

OR
options {
  paraphrase = "|";
}
	:	'|'
	;

XOR
options {
  paraphrase = "^";
}
	:	'^'
	;

AND
options {
  paraphrase = "&";
}
	:	'&'
	;

COLON
options {
  paraphrase = ":";
}
	:	':'
	;

COMMA
options {
  paraphrase = ",";
}
	:	','
	;

DOT
options {
  paraphrase = ".";
}
	:	'.'
	;

ASSIGN
options {
  paraphrase = "=";
}
	:	'='
	;

NOT
options {
  paraphrase = "!";
}
	:	'!'
	;

LT_
options {
  paraphrase = "<";
}
	:	'<'
	;

LSHIFT
options {
  paraphrase = "<<";
}
	: "<<"
	;

GT
options {
  paraphrase = ">";
}
	:	'>'
	;

RSHIFT
options {
  paraphrase = ">>";
}
	: ">>"
	;

DIV
options {
  paraphrase = "/";
}
	:	'/'
	;

PLUS
options {
  paraphrase = "+";
}
	:	'+'
	;

MINUS
options {
  paraphrase = "-";
}
	:	'-'
	;

TILDE
options {
  paraphrase = "~";
}
	:	'~'
	;

STAR
options {
  paraphrase = "*";
}
	:	'*'
	;

MOD
options {
  paraphrase = "%";
}
	:	'%'
	;

SCOPEOP
options {
  paraphrase = "::";
}
	:  	"::"
	;

WS_
options {
  paraphrase = "white space";
}
	:	(' '
	|	'\t'
	|	'\n'  { newline(); }
	|	'\r')
		{ $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
	;

PREPROC_DIRECTIVE
options {
  paraphrase = "a preprocessor directive";
}

	:
	'#'
	(~'\n')* '\n'
	{ $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
	;

SL_COMMENT
options {
  paraphrase = "a comment";
}

	:
	"//"
	(~'\n')* '\n'
	{ $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); newline(); }
	;

ML_COMMENT
options {
  paraphrase = "a comment";
}
	:
	"/*"
	(
			STRING_LITERAL
		|	CHAR_LITERAL
		|	'\n' { newline(); }
		|	'*' ~'/'
		|	~'*'
	)*
	"*/"
	{ $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP);  }
	;

CHAR_LITERAL
options {
  paraphrase = "a character literal";
}
	:
	'\''
	( ESC | ~'\'' )
	'\''
	;

STRING_LITERAL
options {
  paraphrase = "a string literal";
}
	:
	'"'
	(~'"')*
	'"'
	;

protected
ESC
options {
  paraphrase = "an escape sequence";
}
	:	'\\'
		(	'n'
		|	't'
		|	'v'
		|	'b'
		|	'r'
		|	'f'
		|	'a'
		|	'\\'
		|	'?'
		|	'\''
		|	'"')
	;

protected
VOCAB
options {
  paraphrase = "an escaped character value";
}
	:	'\3'..'\377'
	;

protected
DIGIT
options {
  paraphrase = "a digit";
}
	:	'0'..'9'
	;

INT
options {
  paraphrase = "an integer value";
}
	:    (DIGIT)+                  // base-10
             (  '.' (DIGIT)*                      	{$setType(FLOAT);}
	         (('e' | 'E') ('+' | '-')? (DIGIT)+)?
	     |   ('e' | 'E') ('+' | '-')? (DIGIT)+   	{$setType(FLOAT);}
             )?
	;

FLOAT
options {
  paraphrase = "a floating point value";
}

	:    '.' (DIGIT)+ (('e' | 'E') ('+' | '-')? (DIGIT)+)?
     	;

ID
options {
  testLiterals = true;
  paraphrase = "an identifer";
}

	:	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9'|':'|'\\'|'/'|'.')*
	;
