/* $ANTLR 2.7.7 (20060930): "Yes.g" -> "MyParser.cpp"$ */
#include "MyParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "Yes.g"
#line 8 "MyParser.cpp"
MyParser::MyParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

MyParser::MyParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,1)
{
}

MyParser::MyParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

MyParser::MyParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,1)
{
}

MyParser::MyParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,1)
{
}

void MyParser::fileparser() {
	
	{
	configfile();
	}
}

void MyParser::configfile() {
	
	switch ( LA(1)) {
	case MBDEMOTRADING:
	case FOREXACCT:
	case EQUITYACCT:
	case SIMULATETRADING:
	case TIMEZONE:
	case MAXTRADES:
	case NUMCANDLEMINUTES:
	case LOGPATH:
	case LOGL1DATA:
	case CANDLESTICKVALUE:
	case TRENDLINEOPENPOSITION:
	case TLCROSSTRADING:
	case REVERSETRADING:
	{
		systemconfigitem();
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == NEWLINE)) {
				match(NEWLINE);
				systemconfigitem();
			}
			else {
				goto _loop5;
			}
			
		}
		_loop5:;
		} // ( ... )*
		break;
	}
	case CURRENCYPAIR:
	case VOLATILITYBREAKOUTWITHIMPROVEDEXIT:
	case TRENDLINEWITHIMPROVEDEXIT:
	case DYNAMICDEFINITION:
	case ROCWITHIMPROVEDEXIT:
	{
		pairconfigitem();
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == NEWLINE)) {
				match(NEWLINE);
				pairconfigitem();
			}
			else {
				goto _loop7;
			}
			
		}
		_loop7:;
		} // ( ... )*
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::systemconfigitem() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  id2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  id3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 168 "Yes.g"
	bool bVal=false;
#line 111 "MyParser.cpp"
	
	switch ( LA(1)) {
	case MBDEMOTRADING:
	{
		match(MBDEMOTRADING);
		match(ASSIGN);
		bVal=boolean_literal();
#line 170 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "MBDEMOTRADING: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->MBDemoTrading(bVal);
				#endif
				
#line 127 "MyParser.cpp"
		break;
	}
	case FOREXACCT:
	{
		match(FOREXACCT);
		match(ASSIGN);
		bVal=boolean_literal();
#line 178 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "FOREXACCT: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->forexAcct(bVal);
				#endif
				
#line 143 "MyParser.cpp"
		break;
	}
	case EQUITYACCT:
	{
		match(EQUITYACCT);
		match(ASSIGN);
		bVal=boolean_literal();
#line 186 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "EQUITYACCT: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->equityAcct(bVal);
				#endif
				
#line 159 "MyParser.cpp"
		break;
	}
	case SIMULATETRADING:
	{
		match(SIMULATETRADING);
		match(ASSIGN);
		bVal=boolean_literal();
#line 194 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "SIMULATETRADING: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->simulationTrades(bVal);
				#endif
				
#line 175 "MyParser.cpp"
		break;
	}
	case LOGL1DATA:
	{
		match(LOGL1DATA);
		match(ASSIGN);
		bVal=boolean_literal();
#line 202 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "LOGL1DATA: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->logL1Data(bVal);
				#endif
				
#line 191 "MyParser.cpp"
		break;
	}
	case TIMEZONE:
	{
		match(TIMEZONE);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 210 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "TIMEZONE: " << id1->getText() << std::endl;
				#else
					ConfigurationData::instance()->timeZone(id1->getText());
				#endif
				
#line 208 "MyParser.cpp"
		break;
	}
	case MAXTRADES:
	{
		match(MAXTRADES);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 218 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "MAXTRADES: " << int1->getText() << std::endl;
				#else
					ConfigurationData::instance()->maxTrades(atoi(int1->getText().c_str()));
				#endif
				
#line 225 "MyParser.cpp"
		break;
	}
	case NUMCANDLEMINUTES:
	{
		match(NUMCANDLEMINUTES);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 226 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "NUMCANDLEMINUTES: " << float1->getText() << std::endl;
				#else
					ConfigurationData::instance()->numCandleMinutes(atof(float1->getText().c_str()));
				#endif
				
#line 242 "MyParser.cpp"
		break;
	}
	case CANDLESTICKVALUE:
	{
		match(CANDLESTICKVALUE);
		match(ASSIGN);
		id2 = LT(1);
		match(ID);
#line 234 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "CANDLESTICKVALUES: " << id2->getText() << std::endl;
				#else
					ConfigurationData::instance()->candleStickVal(id2->getText());
				#endif
				
#line 259 "MyParser.cpp"
		break;
	}
	case LOGPATH:
	{
		match(LOGPATH);
		match(ASSIGN);
		id3 = LT(1);
		match(STRING_LITERAL);
#line 242 "Yes.g"
		
					std::string newString = id3->getText();
					newString.erase(newString.length()-1,1);
					newString.erase(0,1);
				#ifdef PARSERTEST
					std::cout << "LOGPATH: " << newString << std::endl;
				#else
					ConfigurationData::instance()->logPath(newString);
				#endif
				
#line 279 "MyParser.cpp"
		break;
	}
	case TRENDLINEOPENPOSITION:
	{
		match(TRENDLINEOPENPOSITION);
		match(ASSIGN);
		bVal=boolean_literal();
#line 253 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "TRENDLINEOPENPOSITION: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->trendLineOpenPosition(bVal);
				#endif
				
#line 295 "MyParser.cpp"
		break;
	}
	case TLCROSSTRADING:
	{
		match(TLCROSSTRADING);
		match(ASSIGN);
		bVal=boolean_literal();
#line 261 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "TLCROSSTRADING: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->TLCrossTrading(bVal);
				#endif
				
#line 311 "MyParser.cpp"
		break;
	}
	case REVERSETRADING:
	{
		match(REVERSETRADING);
		match(ASSIGN);
		bVal=boolean_literal();
#line 269 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "REVERSETRADING: " << bVal << std::endl;
				#else
					ConfigurationData::instance()->reverseTrading(bVal);
				#endif
				
#line 327 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::pairconfigitem() {
#line 278 "Yes.g"
	
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
		
#line 386 "MyParser.cpp"
	
	switch ( LA(1)) {
	case CURRENCYPAIR:
	{
		match(CURRENCYPAIR);
		match(LCURLY);
		symbol=pairitemlist(data);
		{ // ( ... )+
		int _cnt11=0;
		for (;;) {
			if ((_tokenSet_0.member(LA(1)))) {
				dummyS=pairitemlist(data);
			}
			else {
				if ( _cnt11>=1 ) { goto _loop11; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt11++;
		}
		_loop11:;
		}  // ( ... )+
		match(RCURLY);
#line 327 "Yes.g"
		
					delete vbedata;
					delete rulesdata;
					delete tledata;
					delete rocdata;
				#ifndef PARSERTEST
					ConfigurationData::instance()->symbolData(symbol, data);
					data = 0;
				#endif
				
#line 420 "MyParser.cpp"
		break;
	}
	case VOLATILITYBREAKOUTWITHIMPROVEDEXIT:
	{
		match(VOLATILITYBREAKOUTWITHIMPROVEDEXIT);
		match(LCURLY);
		symbol=volbreakoutwepairitemlist(vbedata);
		{ // ( ... )+
		int _cnt13=0;
		for (;;) {
			if ((_tokenSet_1.member(LA(1)))) {
				dummyS=volbreakoutwepairitemlist(vbedata);
			}
			else {
				if ( _cnt13>=1 ) { goto _loop13; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt13++;
		}
		_loop13:;
		}  // ( ... )+
		match(RCURLY);
#line 338 "Yes.g"
		
					delete data;
					delete rulesdata;
					delete tledata;
					delete rocdata;
				#ifndef PARSERTEST
					ConfigurationData::instance()->symbolData(symbol, vbedata);
				#endif
				
#line 453 "MyParser.cpp"
		break;
	}
	case TRENDLINEWITHIMPROVEDEXIT:
	{
		match(TRENDLINEWITHIMPROVEDEXIT);
		match(LCURLY);
		symbol=trendlinewepairitemlist(tledata);
		{ // ( ... )+
		int _cnt15=0;
		for (;;) {
			if ((_tokenSet_2.member(LA(1)))) {
				dummyS=trendlinewepairitemlist(tledata);
			}
			else {
				if ( _cnt15>=1 ) { goto _loop15; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt15++;
		}
		_loop15:;
		}  // ( ... )+
		match(RCURLY);
#line 348 "Yes.g"
		
					delete data;
					delete rulesdata;
					delete vbedata;
					delete rocdata;
				#ifndef PARSERTEST
					ConfigurationData::instance()->symbolData(symbol, tledata);
				#endif
				
#line 486 "MyParser.cpp"
		break;
	}
	case ROCWITHIMPROVEDEXIT:
	{
		match(ROCWITHIMPROVEDEXIT);
		match(LCURLY);
		symbol=rocwepairitemlist(rocdata);
		{ // ( ... )+
		int _cnt17=0;
		for (;;) {
			if ((_tokenSet_3.member(LA(1)))) {
				dummyS=rocwepairitemlist(rocdata);
			}
			else {
				if ( _cnt17>=1 ) { goto _loop17; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt17++;
		}
		_loop17:;
		}  // ( ... )+
		match(RCURLY);
#line 358 "Yes.g"
		
					delete data;
					delete rulesdata;
					delete vbedata;
					delete tledata;
				#ifndef PARSERTEST
					ConfigurationData::instance()->symbolData(symbol, rocdata);
				#endif
				
#line 519 "MyParser.cpp"
		break;
	}
	case DYNAMICDEFINITION:
	{
		match(DYNAMICDEFINITION);
		match(LCURLY);
		symbol=dynamicpairs(rulesdata);
		{ // ( ... )+
		int _cnt19=0;
		for (;;) {
			if ((_tokenSet_4.member(LA(1)))) {
				dummyS=dynamicpairs(rulesdata);
			}
			else {
				if ( _cnt19>=1 ) { goto _loop19; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt19++;
		}
		_loop19:;
		}  // ( ... )+
		match(RCURLY);
#line 368 "Yes.g"
		
					delete data;
					delete vbedata;
					delete tledata;
					delete rocdata;
				#ifndef PARSERTEST
					ConfigurationData::instance()->symbolData(symbol, rulesdata);
				#endif
				
#line 552 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

bool  MyParser::boolean_literal() {
#line 1590 "Yes.g"
	bool retVal=false;
#line 565 "MyParser.cpp"
	
	switch ( LA(1)) {
	case LITERAL_TRUE:
	{
		match(LITERAL_TRUE);
#line 1592 "Yes.g"
		retVal= true;
#line 573 "MyParser.cpp"
		break;
	}
	case LITERAL_FALSE:
	{
		match(LITERAL_FALSE);
#line 1593 "Yes.g"
		retVal= false;
#line 581 "MyParser.cpp"
		break;
	}
	case LITERAL_True:
	{
		match(LITERAL_True);
#line 1594 "Yes.g"
		retVal =true;
#line 589 "MyParser.cpp"
		break;
	}
	case LITERAL_False:
	{
		match(LITERAL_False);
#line 1595 "Yes.g"
		retVal= false;
#line 597 "MyParser.cpp"
		break;
	}
	case LITERAL_true:
	{
		match(LITERAL_true);
#line 1596 "Yes.g"
		retVal= true;
#line 605 "MyParser.cpp"
		break;
	}
	case LITERAL_false:
	{
		match(LITERAL_false);
#line 1597 "Yes.g"
		retVal= false;
#line 613 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return retVal;
}

std::string  MyParser::pairitemlist(
	TLSymbolData * data
) {
#line 379 "Yes.g"
	std::string symbol;
#line 629 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 379 "Yes.g"
	
			MyParser::TimeData timeData;
		
#line 640 "MyParser.cpp"
	
	switch ( LA(1)) {
	case SYMBOL:
	{
		match(SYMBOL);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 384 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
				#else
					symbol = id1->getText();
				#endif
				
#line 657 "MyParser.cpp"
		match(STARTTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 392 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 670 "MyParser.cpp"
		break;
	}
	case ENDTRADETIME:
	{
		match(ENDTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 401 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 687 "MyParser.cpp"
		break;
	}
	case FIRSTENTRYSIGNALTIME:
	{
		match(FIRSTENTRYSIGNALTIME);
		match(ASSIGN);
		timeData=time();
#line 410 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tFIRSTENTRYSIGNALTIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->firstEntrySignalTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 704 "MyParser.cpp"
		break;
	}
	case FIRSTTRENDLINETIME:
	{
		match(FIRSTTRENDLINETIME);
		match(ASSIGN);
		timeData=time();
#line 419 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tFIRSTTRENDLINETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->TLStartTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 721 "MyParser.cpp"
		break;
	}
	case SECONDTRENDLINETIME:
	{
		match(SECONDTRENDLINETIME);
		match(ASSIGN);
		timeData=time();
#line 428 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSECONDTRENDLINETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->TLEndTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 738 "MyParser.cpp"
		break;
	}
	case PIPSTOPLOSS:
	{
		match(PIPSTOPLOSS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 437 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSTOPLOSS: " << int1->getText() << std::endl;
				#else
					data->pipsStopLoss_ = double(atoi(int1->getText().c_str()));
				#endif
				
#line 755 "MyParser.cpp"
		break;
	}
	case TRAILONECESTOPLOSSTRIGGER:
	{
		match(TRAILONECESTOPLOSSTRIGGER);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 445 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTRAILONECESTOPLOSSTRIGGER: " << int2->getText() << std::endl;
				#else
					data->trailOnceStopLossTrigger_ = double(atoi(int2->getText().c_str()));
				#endif
				
#line 772 "MyParser.cpp"
		break;
	}
	case TRAILONCESTOPLOSS:
	{
		match(TRAILONCESTOPLOSS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 453 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTRAILONCESTOPLOSS: " << int3->getText() << std::endl;
				#else
					data->trailOnceStopLoss_ = double(atoi(int3->getText().c_str()));
				#endif
				
#line 789 "MyParser.cpp"
		break;
	}
	case PIPSPRECISION:
	{
		match(PIPSPRECISION);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 461 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
				#else
					data->pipsPrecision_ = atof(float1->getText().c_str());
				#endif
				
#line 806 "MyParser.cpp"
		break;
	}
	case DEFAULTLOTSIZE:
	{
		match(DEFAULTLOTSIZE);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 469 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tDEFAULTLOTSIZE: " << int4->getText() << std::endl;
				#else
					data->defaultLotSize_ = 0;
					data->defaultLotSize_ = atoi(int4->getText().c_str());
				#endif
				
#line 824 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNMSA:
	{
		msarules(data);
		break;
	}
	case MAXDRAWDOWN:
	{
		maxddrules(data);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return symbol;
}

std::string  MyParser::volbreakoutwepairitemlist(
	VolatilityBreakOutWImprovedExitData * data
) {
#line 1034 "Yes.g"
	std::string symbol;
#line 850 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int9 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int14 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float7 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1034 "Yes.g"
	
			bool bVal=false;
			MyParser::TimeData timeData;
	//		std::string symbol;
		
#line 871 "MyParser.cpp"
	
	switch ( LA(1)) {
	case SYMBOL:
	{
		match(SYMBOL);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 1041 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
				#else
					symbol = id1->getText();
				#endif
				
#line 888 "MyParser.cpp"
		break;
	}
	case INVERTTRADE:
	{
		match(INVERTTRADE);
		match(ASSIGN);
		bVal=boolean_literal();
#line 1049 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "INVERTTRADE: " << bVal << std::endl;
				#else
					data->invertTrade_ = bVal;
				#endif
				
#line 904 "MyParser.cpp"
		break;
	}
	case STARTTRADETIME:
	{
		match(STARTTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1057 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 921 "MyParser.cpp"
		break;
	}
	case ENDTRADETIME:
	{
		match(ENDTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1066 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 938 "MyParser.cpp"
		break;
	}
	case PIPSTRAIL:
	{
		match(PIPSTRAIL);
		match(ASSIGN);
		int9 = LT(1);
		match(INT);
#line 1075 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
				#else
					data->pipsTrail_ = atoi(int9->getText().c_str());
				#endif
				
#line 955 "MyParser.cpp"
		break;
	}
	case PIPSPRECISION:
	{
		match(PIPSPRECISION);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1083 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
				#else
					data->pipsPrecision_ = atof(float1->getText().c_str());
				#endif
				
#line 972 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 1091 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int4->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int4->getText().c_str());
				#endif
				
#line 989 "MyParser.cpp"
		break;
	}
	case ENTRYATRBARS:
	{
		match(ENTRYATRBARS);
		match(ASSIGN);
		int14 = LT(1);
		match(INT);
#line 1099 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENTRYATRBARS: " << int14->getText() << std::endl;
				#else
					data->entryATRBars_ = atoi(int14->getText().c_str());
				#endif
				
#line 1006 "MyParser.cpp"
		break;
	}
	case ATRMULT:
	{
		match(ATRMULT);
		match(ASSIGN);
		float7 = LT(1);
		match(FLOAT);
#line 1107 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRMULT: " << float7->getText() << std::endl;
				#else
					data->ATRMult_ = atof(float7->getText().c_str());
				#endif
				
#line 1023 "MyParser.cpp"
		break;
	}
	case EMABARS:
	{
		match(EMABARS);
		match(ASSIGN);
		int8 = LT(1);
		match(INT);
#line 1115 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tEMABARS: " << int8->getText() << std::endl;
				#else
					data->EMABars_ = atoi(int8->getText().c_str());
				#endif
				
#line 1040 "MyParser.cpp"
		break;
	}
	case TIMEEXIT:
	{
		match(TIMEEXIT);
		match(ASSIGN);
		int5 = LT(1);
		match(INT);
#line 1123 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
				#else
					data->timeExit_ = atoi(int5->getText().c_str());
				#endif
				
#line 1057 "MyParser.cpp"
		break;
	}
	case MMSTP:
	{
		match(MMSTP);
		match(ASSIGN);
		float2 = LT(1);
		match(FLOAT);
#line 1131 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tMMSTP: " << float2->getText() << std::endl;
				#else
					data->mmstp_ = atof(float2->getText().c_str());
				#endif
				
#line 1074 "MyParser.cpp"
		break;
	}
	case PTLIM:
	{
		match(PTLIM);
		match(ASSIGN);
		float3 = LT(1);
		match(FLOAT);
#line 1139 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTLIM: " << float3->getText() << std::endl;
				#else
					data->ptlim_ = atof(float3->getText().c_str());
				#endif
				
#line 1091 "MyParser.cpp"
		break;
	}
	case STPA:
	{
		match(STPA);
		match(ASSIGN);
		float4 = LT(1);
		match(FLOAT);
#line 1147 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPA: " << float4->getText() << std::endl;
				#else
					data->stpa_ = atof(float4->getText().c_str());
				#endif
				
#line 1108 "MyParser.cpp"
		break;
	}
	case STPB:
	{
		match(STPB);
		match(ASSIGN);
		float5 = LT(1);
		match(FLOAT);
#line 1155 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPB: " << float5->getText() << std::endl;
				#else
					data->stpb_ = atof(float5->getText().c_str());
				#endif
				
#line 1125 "MyParser.cpp"
		break;
	}
	case PTGA:
	{
		match(PTGA);
		match(ASSIGN);
		float6 = LT(1);
		match(FLOAT);
#line 1163 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTGA: " << float6->getText() << std::endl;
				#else
					data->ptga_ = atof(float6->getText().c_str());
				#endif
				
#line 1142 "MyParser.cpp"
		break;
	}
	case DEFAULTLOTSIZE:
	{
		match(DEFAULTLOTSIZE);
		match(ASSIGN);
		int6 = LT(1);
		match(INT);
#line 1171 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
				#else
					data->defaultLotSize_ = 0;
					data->defaultLotSize_ = atoi(int6->getText().c_str());
				#endif
				
#line 1160 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNMSA:
	{
		msarules(data);
		break;
	}
	case MAXDRAWDOWN:
	{
		maxddrules(data);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return symbol;
}

std::string  MyParser::trendlinewepairitemlist(
	TrendLineWImprovedExitData * data
) {
#line 1183 "Yes.g"
	std::string symbol;
#line 1186 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int9 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int10 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int11 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int12 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1183 "Yes.g"
	
			bool bVal=false;
			MyParser::TimeData timeData;
	//		std::string symbol;
		
#line 1208 "MyParser.cpp"
	
	switch ( LA(1)) {
	case SYMBOL:
	{
		match(SYMBOL);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 1190 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
				#else
					symbol = id1->getText();
				#endif
				
#line 1225 "MyParser.cpp"
		break;
	}
	case INVERTTRADE:
	{
		match(INVERTTRADE);
		match(ASSIGN);
		bVal=boolean_literal();
#line 1198 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "INVERTTRADE: " << bVal << std::endl;
				#else
					data->invertTrade_ = bVal;
				#endif
				
#line 1241 "MyParser.cpp"
		break;
	}
	case STARTTRADETIME:
	{
		match(STARTTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1206 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1258 "MyParser.cpp"
		break;
	}
	case ENDTRADETIME:
	{
		match(ENDTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1215 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1275 "MyParser.cpp"
		break;
	}
	case PIPSTRAIL:
	{
		match(PIPSTRAIL);
		match(ASSIGN);
		int9 = LT(1);
		match(INT);
#line 1224 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
				#else
					data->pipsTrail_ = atoi(int9->getText().c_str());
				#endif
				
#line 1292 "MyParser.cpp"
		break;
	}
	case PIPSPRECISION:
	{
		match(PIPSPRECISION);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1232 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
				#else
					data->pipsPrecision_ = atof(float1->getText().c_str());
				#endif
				
#line 1309 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 1240 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int4->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int4->getText().c_str());
				#endif
				
#line 1326 "MyParser.cpp"
		break;
	}
	case TL1BARS:
	{
		match(TL1BARS);
		match(ASSIGN);
		int10 = LT(1);
		match(INT);
#line 1248 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTL1BARS: " << int10->getText() << std::endl;
				#else
					data->TL1Bars_ = atoi(int10->getText().c_str());
				#endif
				
#line 1343 "MyParser.cpp"
		break;
	}
	case TL2BARS:
	{
		match(TL2BARS);
		match(ASSIGN);
		int8 = LT(1);
		match(INT);
#line 1256 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTL2BARS: " << int8->getText() << std::endl;
				#else
					data->TL2Bars_ = atoi(int8->getText().c_str());
				#endif
				
#line 1360 "MyParser.cpp"
		break;
	}
	case RSIBARS:
	{
		match(RSIBARS);
		match(ASSIGN);
		int11 = LT(1);
		match(INT);
#line 1264 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tRSIBARS: " << int11->getText() << std::endl;
				#else
					data->RSIBars_ = atoi(int11->getText().c_str());
				#endif
				
#line 1377 "MyParser.cpp"
		break;
	}
	case STOCHBARS:
	{
		match(STOCHBARS);
		match(ASSIGN);
		int12 = LT(1);
		match(INT);
#line 1272 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTOCHBARS: " << int12->getText() << std::endl;
				#else
					data->StochBars_ = atoi(int12->getText().c_str());
				#endif
				
#line 1394 "MyParser.cpp"
		break;
	}
	case TIMEEXIT:
	{
		match(TIMEEXIT);
		match(ASSIGN);
		int5 = LT(1);
		match(INT);
#line 1280 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
				#else
					data->timeExit_ = atoi(int5->getText().c_str());
				#endif
				
#line 1411 "MyParser.cpp"
		break;
	}
	case MMSTP:
	{
		match(MMSTP);
		match(ASSIGN);
		float2 = LT(1);
		match(FLOAT);
#line 1288 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tMMSTP: " << float2->getText() << std::endl;
				#else
					data->mmstp_ = atof(float2->getText().c_str());
				#endif
				
#line 1428 "MyParser.cpp"
		break;
	}
	case PTLIM:
	{
		match(PTLIM);
		match(ASSIGN);
		float3 = LT(1);
		match(FLOAT);
#line 1296 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTLIM: " << float3->getText() << std::endl;
				#else
					data->ptlim_ = atof(float3->getText().c_str());
				#endif
				
#line 1445 "MyParser.cpp"
		break;
	}
	case STPA:
	{
		match(STPA);
		match(ASSIGN);
		float4 = LT(1);
		match(FLOAT);
#line 1304 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPA: " << float4->getText() << std::endl;
				#else
					data->stpa_ = atof(float4->getText().c_str());
				#endif
				
#line 1462 "MyParser.cpp"
		break;
	}
	case STPB:
	{
		match(STPB);
		match(ASSIGN);
		float5 = LT(1);
		match(FLOAT);
#line 1312 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPB: " << float5->getText() << std::endl;
				#else
					data->stpb_ = atof(float5->getText().c_str());
				#endif
				
#line 1479 "MyParser.cpp"
		break;
	}
	case PTGA:
	{
		match(PTGA);
		match(ASSIGN);
		float6 = LT(1);
		match(FLOAT);
#line 1320 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTGA: " << float6->getText() << std::endl;
				#else
					data->ptga_ = atof(float6->getText().c_str());
				#endif
				
#line 1496 "MyParser.cpp"
		break;
	}
	case DEFAULTLOTSIZE:
	{
		match(DEFAULTLOTSIZE);
		match(ASSIGN);
		int6 = LT(1);
		match(INT);
#line 1328 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
				#else
					data->defaultLotSize_ = 0;
					data->defaultLotSize_ = atoi(int6->getText().c_str());
				#endif
				
#line 1514 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNMSA:
	{
		msarules(data);
		break;
	}
	case MAXDRAWDOWN:
	{
		maxddrules(data);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return symbol;
}

std::string  MyParser::rocwepairitemlist(
	ROCWImprovedExitData * data
) {
#line 1340 "Yes.g"
	std::string symbol;
#line 1540 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int9 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int10 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int11 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int12 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1340 "Yes.g"
	
			bool bVal=false;
			MyParser::TimeData timeData;
	//		std::string symbol;
		
#line 1562 "MyParser.cpp"
	
	switch ( LA(1)) {
	case SYMBOL:
	{
		match(SYMBOL);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 1347 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
				#else
					symbol = id1->getText();
				#endif
				
#line 1579 "MyParser.cpp"
		break;
	}
	case INVERTTRADE:
	{
		match(INVERTTRADE);
		match(ASSIGN);
		bVal=boolean_literal();
#line 1355 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "INVERTTRADE: " << bVal << std::endl;
				#else
					data->invertTrade_ = bVal;
				#endif
				
#line 1595 "MyParser.cpp"
		break;
	}
	case STARTTRADETIME:
	{
		match(STARTTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1363 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1612 "MyParser.cpp"
		break;
	}
	case ENDTRADETIME:
	{
		match(ENDTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 1372 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1629 "MyParser.cpp"
		break;
	}
	case PIPSTRAIL:
	{
		match(PIPSTRAIL);
		match(ASSIGN);
		int9 = LT(1);
		match(INT);
#line 1381 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSTRAIL: " << int9->getText() << std::endl;
				#else
					data->pipsTrail_ = atoi(int9->getText().c_str());
				#endif
				
#line 1646 "MyParser.cpp"
		break;
	}
	case PIPSPRECISION:
	{
		match(PIPSPRECISION);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1389 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
				#else
					data->pipsPrecision_ = atof(float1->getText().c_str());
				#endif
				
#line 1663 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 1397 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int4->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int4->getText().c_str());
				#endif
				
#line 1680 "MyParser.cpp"
		break;
	}
	case ADXBARS:
	{
		match(ADXBARS);
		match(ASSIGN);
		int10 = LT(1);
		match(INT);
#line 1405 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tADXBARS: " << int10->getText() << std::endl;
				#else
					data->adxBars_ = atoi(int10->getText().c_str());
				#endif
				
#line 1697 "MyParser.cpp"
		break;
	}
	case ROCBARS:
	{
		match(ROCBARS);
		match(ASSIGN);
		int8 = LT(1);
		match(INT);
#line 1413 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tROCBARS: " << int8->getText() << std::endl;
				#else
					data->rocBars_ = atoi(int8->getText().c_str());
				#endif
				
#line 1714 "MyParser.cpp"
		break;
	}
	case ROCCOUNT:
	{
		match(ROCCOUNT);
		match(ASSIGN);
		int11 = LT(1);
		match(INT);
#line 1421 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tROCCOUNT: " << int11->getText() << std::endl;
				#else
					data->ROCCount_ = atoi(int11->getText().c_str());
				#endif
				
#line 1731 "MyParser.cpp"
		break;
	}
	case STDROCBARS:
	{
		match(STDROCBARS);
		match(ASSIGN);
		int12 = LT(1);
		match(INT);
#line 1429 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTDROCBARS: " << int12->getText() << std::endl;
				#else
					data->stdROCBars_ = atoi(int12->getText().c_str());
				#endif
				
#line 1748 "MyParser.cpp"
		break;
	}
	case TIMEEXIT:
	{
		match(TIMEEXIT);
		match(ASSIGN);
		int5 = LT(1);
		match(INT);
#line 1437 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
				#else
					data->timeExit_ = atoi(int5->getText().c_str());
				#endif
				
#line 1765 "MyParser.cpp"
		break;
	}
	case MMSTP:
	{
		match(MMSTP);
		match(ASSIGN);
		float2 = LT(1);
		match(FLOAT);
#line 1445 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tMMSTP: " << float2->getText() << std::endl;
				#else
					data->mmstp_ = atof(float2->getText().c_str());
				#endif
				
#line 1782 "MyParser.cpp"
		break;
	}
	case PTLIM:
	{
		match(PTLIM);
		match(ASSIGN);
		float3 = LT(1);
		match(FLOAT);
#line 1453 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTLIM: " << float3->getText() << std::endl;
				#else
					data->ptlim_ = atof(float3->getText().c_str());
				#endif
				
#line 1799 "MyParser.cpp"
		break;
	}
	case STPA:
	{
		match(STPA);
		match(ASSIGN);
		float4 = LT(1);
		match(FLOAT);
#line 1461 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPA: " << float4->getText() << std::endl;
				#else
					data->stpa_ = atof(float4->getText().c_str());
				#endif
				
#line 1816 "MyParser.cpp"
		break;
	}
	case STPB:
	{
		match(STPB);
		match(ASSIGN);
		float5 = LT(1);
		match(FLOAT);
#line 1469 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPB: " << float5->getText() << std::endl;
				#else
					data->stpb_ = atof(float5->getText().c_str());
				#endif
				
#line 1833 "MyParser.cpp"
		break;
	}
	case PTGA:
	{
		match(PTGA);
		match(ASSIGN);
		float6 = LT(1);
		match(FLOAT);
#line 1477 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTGA: " << float6->getText() << std::endl;
				#else
					data->ptga_ = atof(float6->getText().c_str());
				#endif
				
#line 1850 "MyParser.cpp"
		break;
	}
	case DEFAULTLOTSIZE:
	{
		match(DEFAULTLOTSIZE);
		match(ASSIGN);
		int6 = LT(1);
		match(INT);
#line 1485 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tDEFAULTLOTSIZE: " << int6->getText() << std::endl;
				#else
					data->defaultLotSize_ = 0;
					data->defaultLotSize_ = atoi(int6->getText().c_str());
				#endif
				
#line 1868 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNMSA:
	{
		msarules(data);
		break;
	}
	case MAXDRAWDOWN:
	{
		maxddrules(data);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return symbol;
}

std::string  MyParser::dynamicpairs(
	DynamicRulesData * rulesdata
) {
#line 482 "Yes.g"
	std::string symbol;
#line 1894 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  id1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 482 "Yes.g"
	
			MyParser::TimeData timeData;
		
#line 1902 "MyParser.cpp"
	
	switch ( LA(1)) {
	case SYMBOL:
	{
		match(SYMBOL);
		match(ASSIGN);
		id1 = LT(1);
		match(ID);
#line 487 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\nNEW Currency Pair!\n\tSYMBOL: " << id1->getText() << std::endl;
				#else
					symbol = id1->getText();
				#endif
				
#line 1919 "MyParser.cpp"
		match(STARTTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 495 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTARTTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					rulesdata->startTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1932 "MyParser.cpp"
		break;
	}
	case ENDTRADETIME:
	{
		match(ENDTRADETIME);
		match(ASSIGN);
		timeData=time();
#line 504 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tENDTRADETIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					rulesdata->endTradeTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 1949 "MyParser.cpp"
		break;
	}
	case PIPSPRECISION:
	{
		match(PIPSPRECISION);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 513 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSPRECISION: " << float1 << std::endl;
				#else
					rulesdata->pipsPrecision_ = atof(float1->getText().c_str());
				#endif
				
#line 1966 "MyParser.cpp"
		break;
	}
	case DEFAULTLOTSIZE:
	{
		match(DEFAULTLOTSIZE);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 521 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tDEFAULTLOTSIZE: " << int4->getText() << std::endl;
				#else
					rulesdata->defaultLotSize_ = 0;
					rulesdata->defaultLotSize_ = atoi(int4->getText().c_str());
				#endif
				
#line 1984 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNMSA:
	{
		msarules(rulesdata);
		break;
	}
	case MAXDRAWDOWN:
	{
		maxddrules(rulesdata);
		break;
	}
	case SPREADPRICING:
	case MARKETPRICING:
	case MARKETTPLIMITPRICING:
	case HALFBARPRICING:
	case MATCHBIDPRICING:
	{
		pricing(rulesdata);
		break;
	}
	case VOLATILITYBREAKOUTENTRYRULE:
	case TURTLEBREAKOUTENTRYRULE:
	case TRIPPLEMVAENTRYRULE:
	case EMASCALPENTRYRULE:
	case TLSCALPENTRYRULE:
	case TLSCALP2ENTRYRULE:
	case ADXENTRYRULE:
	case FIVMINUTEENTRYRULE:
	{
		entryrules(rulesdata);
		break;
	}
	case IMPROVEDEXITRULE:
	case FIXEDEXITRULE:
	case EXITEXITRULE:
	{
		exitrules(rulesdata);
		break;
	}
	case OPENORDERCHASE:
	{
		openmonitor(rulesdata);
		break;
	}
	case CLOSEORDERCHASE:
	case TPSLCLOSEMONITOR:
	{
		closemonitor(rulesdata);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	return symbol;
}

MyParser::TimeData  MyParser::time() {
#line 1586 "Yes.g"
	MyParser::TimeData data;
#line 2047 "MyParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	int1 = LT(1);
	match(INT);
	match(COLON);
	int2 = LT(1);
	match(INT);
	match(COLON);
	int3 = LT(1);
	match(INT);
#line 1587 "Yes.g"
	data.hour=atoi(int1->getText().c_str());data.minutes=atoi(int2->getText().c_str());data.seconds=atoi(int3->getText().c_str());
#line 2062 "MyParser.cpp"
	return data;
}

void MyParser::msarules(
	SymbolData * data
) {
	
	match(MAXDRAWDOWNMSA);
	match(LCURLY);
	msarule(data);
	{ // ( ... )+
	int _cnt64=0;
	for (;;) {
		if (((LA(1) >= MAXHISTDRAWDOWN && LA(1) <= MAXDDPERCENT))) {
			msarule(data);
		}
		else {
			if ( _cnt64>=1 ) { goto _loop64; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
		}
		
		_cnt64++;
	}
	_loop64:;
	}  // ( ... )+
	match(RCURLY);
}

void MyParser::maxddrules(
	SymbolData * data
) {
	
	match(MAXDRAWDOWN);
	match(LCURLY);
	maxddrule(data);
	{ // ( ... )+
	int _cnt68=0;
	for (;;) {
		if (((LA(1) >= PERCENTRISK && LA(1) <= NUMBERWINS))) {
			maxddrule(data);
		}
		else {
			if ( _cnt68>=1 ) { goto _loop68; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
		}
		
		_cnt68++;
	}
	_loop68:;
	}  // ( ... )+
	match(RCURLY);
}

void MyParser::pricing(
	DynamicRulesData * rulesdata
) {
	
	switch ( LA(1)) {
	case SPREADPRICING:
	{
		match(SPREADPRICING);
		match(LCURLY);
		spreadPricing(rulesdata);
		{ // ( ... )+
		int _cnt24=0;
		for (;;) {
			if ((LA(1) == PIPSTOPLOSS || LA(1) == PIPSTAKEPROFIT)) {
				spreadPricing(rulesdata);
			}
			else {
				if ( _cnt24>=1 ) { goto _loop24; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt24++;
		}
		_loop24:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case MARKETPRICING:
	{
		match(MARKETPRICING);
		match(LCURLY);
		match(RCURLY);
#line 541 "Yes.g"
		rulesdata->priceRule_ = new MarketPricingRule();
#line 2148 "MyParser.cpp"
		break;
	}
	case HALFBARPRICING:
	{
		match(HALFBARPRICING);
		match(LCURLY);
		match(RCURLY);
#line 542 "Yes.g"
		rulesdata->priceRule_ = new HalfBarPricingRule();
#line 2158 "MyParser.cpp"
		break;
	}
	case MATCHBIDPRICING:
	{
		match(MATCHBIDPRICING);
		match(LCURLY);
		match(RCURLY);
#line 543 "Yes.g"
		rulesdata->priceRule_ = new MatchBidPricingRule();
#line 2168 "MyParser.cpp"
		break;
	}
	case MARKETTPLIMITPRICING:
	{
		match(MARKETTPLIMITPRICING);
		match(LCURLY);
		marketTPLimitPricing(rulesdata);
		match(RCURLY);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::entryrules(
	DynamicRulesData * rulesdata
) {
	
	switch ( LA(1)) {
	case VOLATILITYBREAKOUTENTRYRULE:
	{
		match(VOLATILITYBREAKOUTENTRYRULE);
		match(LCURLY);
		volatiltiyEntry(rulesdata);
		{ // ( ... )+
		int _cnt27=0;
		for (;;) {
			if ((_tokenSet_5.member(LA(1)))) {
				volatiltiyEntry(rulesdata);
			}
			else {
				if ( _cnt27>=1 ) { goto _loop27; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt27++;
		}
		_loop27:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case TURTLEBREAKOUTENTRYRULE:
	{
		match(TURTLEBREAKOUTENTRYRULE);
		match(LCURLY);
		turtleEntry(rulesdata);
		{ // ( ... )+
		int _cnt29=0;
		for (;;) {
			if ((LA(1) == NUMBARS)) {
				turtleEntry(rulesdata);
			}
			else {
				if ( _cnt29>=1 ) { goto _loop29; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt29++;
		}
		_loop29:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case TRIPPLEMVAENTRYRULE:
	{
		match(TRIPPLEMVAENTRYRULE);
		match(LCURLY);
		trippleMVAEntry(rulesdata);
		{ // ( ... )+
		int _cnt31=0;
		for (;;) {
			if (((LA(1) >= BARSFAST && LA(1) <= BARSSLOW))) {
				trippleMVAEntry(rulesdata);
			}
			else {
				if ( _cnt31>=1 ) { goto _loop31; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt31++;
		}
		_loop31:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case ADXENTRYRULE:
	{
		match(ADXENTRYRULE);
		match(LCURLY);
		adxEntry(rulesdata);
		{ // ( ... )+
		int _cnt33=0;
		for (;;) {
			if (((LA(1) >= ADXBARS && LA(1) <= MINUSDIBARS))) {
				adxEntry(rulesdata);
			}
			else {
				if ( _cnt33>=1 ) { goto _loop33; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt33++;
		}
		_loop33:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case EMASCALPENTRYRULE:
	{
		match(EMASCALPENTRYRULE);
		match(LCURLY);
		emaScalpEntry(rulesdata);
		{ // ( ... )+
		int _cnt35=0;
		for (;;) {
			if ((LA(1) == EMABARS || LA(1) == ATRBARS || LA(1) == ADXBARS)) {
				emaScalpEntry(rulesdata);
			}
			else {
				if ( _cnt35>=1 ) { goto _loop35; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt35++;
		}
		_loop35:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case TLSCALPENTRYRULE:
	{
		match(TLSCALPENTRYRULE);
		match(LCURLY);
		tlScalpEntry(rulesdata);
		{ // ( ... )+
		int _cnt37=0;
		for (;;) {
			if ((_tokenSet_6.member(LA(1)))) {
				tlScalpEntry(rulesdata);
			}
			else {
				if ( _cnt37>=1 ) { goto _loop37; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt37++;
		}
		_loop37:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case TLSCALP2ENTRYRULE:
	{
		match(TLSCALP2ENTRYRULE);
		match(LCURLY);
		tlScalp2Entry(rulesdata);
		{ // ( ... )+
		int _cnt39=0;
		for (;;) {
			if ((LA(1) == ATRBARS || LA(1) == ADXBARS || LA(1) == SLOPEBARS)) {
				tlScalp2Entry(rulesdata);
			}
			else {
				if ( _cnt39>=1 ) { goto _loop39; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt39++;
		}
		_loop39:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case FIVMINUTEENTRYRULE:
	{
		match(FIVMINUTEENTRYRULE);
		match(LCURLY);
		match(RCURLY);
#line 555 "Yes.g"
		if(0 == rulesdata->entryRule_){rulesdata->entryRule_ = new FiveMinuteEntry();}
#line 2352 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::exitrules(
	DynamicRulesData * rulesdata
) {
	
	switch ( LA(1)) {
	case IMPROVEDEXITRULE:
	{
		match(IMPROVEDEXITRULE);
		match(LCURLY);
		improvedExit(rulesdata);
		{ // ( ... )+
		int _cnt42=0;
		for (;;) {
			if ((_tokenSet_7.member(LA(1)))) {
				improvedExit(rulesdata);
			}
			else {
				if ( _cnt42>=1 ) { goto _loop42; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt42++;
		}
		_loop42:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case FIXEDEXITRULE:
	{
		match(FIXEDEXITRULE);
		match(LCURLY);
		fixedExit(rulesdata);
		{ // ( ... )+
		int _cnt44=0;
		for (;;) {
			if ((LA(1) == STOPLOSS || LA(1) == TAKEPROFIT)) {
				fixedExit(rulesdata);
			}
			else {
				if ( _cnt44>=1 ) { goto _loop44; } else {throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());}
			}
			
			_cnt44++;
		}
		_loop44:;
		}  // ( ... )+
		match(RCURLY);
		break;
	}
	case EXITEXITRULE:
	{
		match(EXITEXITRULE);
		match(LCURLY);
		match(RCURLY);
#line 560 "Yes.g"
		rulesdata->exitRule_ = new ExitExitRule();
#line 2418 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::openmonitor(
	DynamicRulesData * rulesdata
) {
	
	match(OPENORDERCHASE);
	match(LCURLY);
	match(RCURLY);
#line 563 "Yes.g"
	rulesdata->openMonitor_ = new OpenChaseMonitor();
#line 2437 "MyParser.cpp"
}

void MyParser::closemonitor(
	DynamicRulesData * rulesdata
) {
	
	switch ( LA(1)) {
	case CLOSEORDERCHASE:
	{
		match(CLOSEORDERCHASE);
		match(LCURLY);
		match(RCURLY);
#line 567 "Yes.g"
		rulesdata->closeMonitor_ = new CloseChaseMonitor();
#line 2452 "MyParser.cpp"
		break;
	}
	case TPSLCLOSEMONITOR:
	{
		match(TPSLCLOSEMONITOR);
		match(LCURLY);
		tpslCloseMonitor(rulesdata);
		match(RCURLY);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::spreadPricing(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1003 "Yes.g"
	
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
		
#line 2488 "MyParser.cpp"
	
	switch ( LA(1)) {
	case PIPSTOPLOSS:
	{
		match(PIPSTOPLOSS);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1017 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\n\tSpread Pricing rules!\n\t\tPIPSTOPLOSS: " << float1->getText() << std::endl;
				#else
					data->pipsStopLoss_ = atof(float1->getText().c_str());
				#endif
				
#line 2505 "MyParser.cpp"
		break;
	}
	case PIPSTAKEPROFIT:
	{
		match(PIPSTAKEPROFIT);
		match(ASSIGN);
		float2 = LT(1);
		match(FLOAT);
#line 1025 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tPIPSTAKEPROFIT: " << float2->getText() << std::endl;
				#else
					data->pipsTakeProfit_ = atof(float2->getText().c_str());
				#endif
				
#line 2522 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::marketTPLimitPricing(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 674 "Yes.g"
	
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
		
#line 2549 "MyParser.cpp"
	
	match(TAKEPROFIT);
	match(ASSIGN);
	int3 = LT(1);
	match(INT);
#line 688 "Yes.g"
	
			#ifdef PARSERTEST
				std::cout << "\tTAKEPROFIT: " << int3->getText() << std::endl;
			#else
				data->takeProfit_ = atoi(int3->getText().c_str());
			#endif
			
#line 2563 "MyParser.cpp"
}

void MyParser::volatiltiyEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float7 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 731 "Yes.g"
	
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
		
#line 2587 "MyParser.cpp"
	
	switch ( LA(1)) {
	case INVERTTRADE:
	{
		match(INVERTTRADE);
		match(ASSIGN);
		bVal=boolean_literal();
#line 747 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "INVERTTRADE: " << bVal << std::endl;
				#else
					data->invertTrade_ = bVal;
				#endif
				
#line 2603 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 755 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int4->getText() << std::endl;
				#else
					data->ATRBars_ = atoi(int4->getText().c_str());
				#endif
				
#line 2620 "MyParser.cpp"
		break;
	}
	case ATRMULT:
	{
		match(ATRMULT);
		match(ASSIGN);
		float7 = LT(1);
		match(FLOAT);
#line 763 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRMULT: " << float7->getText() << std::endl;
				#else
					data->ATRMult_ = atof(float7->getText().c_str());
				#endif
				
#line 2637 "MyParser.cpp"
		break;
	}
	case EMABARS:
	{
		match(EMABARS);
		match(ASSIGN);
		int8 = LT(1);
		match(INT);
#line 771 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tEMABARS: " << int8->getText() << std::endl;
				#else
					data->EMABars_ = atoi(int8->getText().c_str());
				#endif
				
#line 2654 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::turtleEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 780 "Yes.g"
	
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
		
#line 2681 "MyParser.cpp"
	
	match(NUMBARS);
	match(ASSIGN);
	int4 = LT(1);
	match(INT);
#line 794 "Yes.g"
	
			#ifdef PARSERTEST
				std::cout << "\tNUMBARS: " << int4->getText() << std::endl;
			#else
				data->numBars_ = atoi(int4->getText().c_str());
			#endif
			
#line 2695 "MyParser.cpp"
}

void MyParser::trippleMVAEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float7 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 803 "Yes.g"
	
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
		
#line 2717 "MyParser.cpp"
	
	switch ( LA(1)) {
	case BARSFAST:
	{
		match(BARSFAST);
		match(ASSIGN);
		float1 = LT(1);
		match(INT);
#line 817 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tBARSFAST: " << float1->getText() << std::endl;
				#else
					data->fast_ = atoi(float1->getText().c_str());
				#endif
				
#line 2734 "MyParser.cpp"
		break;
	}
	case BARSMEDIUM:
	{
		match(BARSMEDIUM);
		match(ASSIGN);
		float2 = LT(1);
		match(INT);
#line 825 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tBARSMEDIUM: " << float2->getText() << std::endl;
				#else
					data->medium_ = atoi(float2->getText().c_str());
				#endif
				
#line 2751 "MyParser.cpp"
		break;
	}
	case BARSSLOW:
	{
		match(BARSSLOW);
		match(ASSIGN);
		float7 = LT(1);
		match(INT);
#line 833 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tBARSSLOW: " << float7->getText() << std::endl;
				#else
					data->slow_ = atoi(float7->getText().c_str());
				#endif
				
#line 2768 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::adxEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 841 "Yes.g"
	
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
		
#line 2797 "MyParser.cpp"
	
	switch ( LA(1)) {
	case ADXBARS:
	{
		match(ADXBARS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 855 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tADXBARS: " << int1->getText() << std::endl;
				#else
					data->adxBars_ = atoi(int1->getText().c_str());
				#endif
				
#line 2814 "MyParser.cpp"
		break;
	}
	case PLUSDIBARS:
	{
		match(PLUSDIBARS);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 863 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPLUSDIBARS: " << int2->getText() << std::endl;
				#else
					data->plusDIBars_ = atoi(int2->getText().c_str());
				#endif
				
#line 2831 "MyParser.cpp"
		break;
	}
	case MINUSDIBARS:
	{
		match(MINUSDIBARS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 871 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tMINUSDIBARS: " << int3->getText() << std::endl;
				#else
					data->minusDIBars_ = atoi(int3->getText().c_str());
				#endif
				
#line 2848 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::emaScalpEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 879 "Yes.g"
	
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
		
#line 2877 "MyParser.cpp"
	
	switch ( LA(1)) {
	case ADXBARS:
	{
		match(ADXBARS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 893 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tADXBARS: " << int1->getText() << std::endl;
				#else
					data->adxBars_ = atoi(int1->getText().c_str());
				#endif
				
#line 2894 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 901 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int2->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int2->getText().c_str());
				#endif
				
#line 2911 "MyParser.cpp"
		break;
	}
	case EMABARS:
	{
		match(EMABARS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 909 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tEMABARS: " << int3->getText() << std::endl;
				#else
					data->emaBars_ = atoi(int3->getText().c_str());
				#endif
				
#line 2928 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::tlScalpEntry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 917 "Yes.g"
	
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
		
#line 2958 "MyParser.cpp"
	
	switch ( LA(1)) {
	case ADXBARS:
	{
		match(ADXBARS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 932 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tADXBARS: " << int1->getText() << std::endl;
				#else
					data->adxBars_ = atoi(int1->getText().c_str());
				#endif
				
#line 2975 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 940 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int2->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int2->getText().c_str());
				#endif
				
#line 2992 "MyParser.cpp"
		break;
	}
	case SLOPEBARS:
	{
		match(SLOPEBARS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 948 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSLOPEBARS: " << int3->getText() << std::endl;
				#else
					data->slopeBars_ = atoi(int3->getText().c_str());
				#endif
				
#line 3009 "MyParser.cpp"
		break;
	}
	case TLENDTIME:
	{
		match(TLENDTIME);
		match(ASSIGN);
		timeData=time();
#line 956 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTLENDTIME: " << timeData.str() << std::endl;
				#else
					long seconds = (timeData.hour * 3600) + (timeData.minutes * 60) + timeData.seconds;
					data->tlEndTime_ = TimeZone::instance()->convertToSecondsGMT(seconds);
				#endif
				
#line 3026 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::tlScalp2Entry(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 965 "Yes.g"
	
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
		
#line 3055 "MyParser.cpp"
	
	switch ( LA(1)) {
	case ADXBARS:
	{
		match(ADXBARS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 979 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tADXBARS: " << int1->getText() << std::endl;
				#else
					data->adxBars_ = atoi(int1->getText().c_str());
				#endif
				
#line 3072 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 987 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int2->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int2->getText().c_str());
				#endif
				
#line 3089 "MyParser.cpp"
		break;
	}
	case SLOPEBARS:
	{
		match(SLOPEBARS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 995 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSLOPEBARS: " << int3->getText() << std::endl;
				#else
					data->slopeBars_ = atoi(int3->getText().c_str());
				#endif
				
#line 3106 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::improvedExit(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 571 "Yes.g"
	
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
		
#line 3141 "MyParser.cpp"
	
	switch ( LA(1)) {
	case PIPSTRAIL:
	{
		match(PIPSTRAIL);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 586 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPIPSTRAIL: " << int3->getText() << std::endl;
				#else
					data->pipsTrail_ = atoi(int3->getText().c_str());
				#endif
				
#line 3158 "MyParser.cpp"
		break;
	}
	case ATRBARS:
	{
		match(ATRBARS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 594 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tATRBARS: " << int4->getText() << std::endl;
				#else
					data->atrBars_ = atoi(int4->getText().c_str());
				#endif
				
#line 3175 "MyParser.cpp"
		break;
	}
	case TIMEEXIT:
	{
		match(TIMEEXIT);
		match(ASSIGN);
		int5 = LT(1);
		match(INT);
#line 602 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTIMEEXIT: " << int5->getText() << std::endl;
				#else
					data->timeExit_ = atoi(int5->getText().c_str());
				#endif
				
#line 3192 "MyParser.cpp"
		break;
	}
	case MMSTP:
	{
		match(MMSTP);
		match(ASSIGN);
		float2 = LT(1);
		match(FLOAT);
#line 610 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tMMSTP: " << float2->getText() << std::endl;
				#else
					data->mmstp_ = atof(float2->getText().c_str());
				#endif
				
#line 3209 "MyParser.cpp"
		break;
	}
	case PTLIM:
	{
		match(PTLIM);
		match(ASSIGN);
		float3 = LT(1);
		match(FLOAT);
#line 618 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTLIM: " << float3->getText() << std::endl;
				#else
					data->ptlim_ = atof(float3->getText().c_str());
				#endif
				
#line 3226 "MyParser.cpp"
		break;
	}
	case STPA:
	{
		match(STPA);
		match(ASSIGN);
		float4 = LT(1);
		match(FLOAT);
#line 626 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPA: " << float4->getText() << std::endl;
				#else
					data->stpa_ = atof(float4->getText().c_str());
				#endif
				
#line 3243 "MyParser.cpp"
		break;
	}
	case STPB:
	{
		match(STPB);
		match(ASSIGN);
		float5 = LT(1);
		match(FLOAT);
#line 634 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTPB: " << float5->getText() << std::endl;
				#else
					data->stpb_ = atof(float5->getText().c_str());
				#endif
				
#line 3260 "MyParser.cpp"
		break;
	}
	case PTGA:
	{
		match(PTGA);
		match(ASSIGN);
		float6 = LT(1);
		match(FLOAT);
#line 642 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tPTGA: " << float6->getText() << std::endl;
				#else
					data->ptga_ = atof(float6->getText().c_str());
				#endif
				
#line 3277 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::fixedExit(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 699 "Yes.g"
	
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
		
#line 3305 "MyParser.cpp"
	
	switch ( LA(1)) {
	case TAKEPROFIT:
	{
		match(TAKEPROFIT);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 713 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tTAKEPROFIT: " << int3->getText() << std::endl;
				#else
					data->takeProfit_ = atoi(int3->getText().c_str());
				#endif
				
#line 3322 "MyParser.cpp"
		break;
	}
	case STOPLOSS:
	{
		match(STOPLOSS);
		match(ASSIGN);
		int4 = LT(1);
		match(INT);
#line 721 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\tSTOPLOSS: " << int4->getText() << std::endl;
				#else
					data->stopLoss_ = atoi(int4->getText().c_str());
				#endif
				
#line 3339 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::tpslCloseMonitor(
	DynamicRulesData * rulesdata
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  int4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 651 "Yes.g"
	
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
		
#line 3366 "MyParser.cpp"
	
	match(STOPLOSS);
	match(ASSIGN);
	int4 = LT(1);
	match(INT);
#line 665 "Yes.g"
	
			#ifdef PARSERTEST
				std::cout << "\tSTOPLOSS: " << int4->getText() << std::endl;
			#else
				data->stopLoss_ = atoi(int4->getText().c_str());
			#endif
			
#line 3380 "MyParser.cpp"
}

void MyParser::msarule(
	SymbolData * data
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  float5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1501 "Yes.g"
	
			if(0 == data->msaData_)
			{
				data->msaData_ = new MaxDDMSAData();
			}
		
#line 3397 "MyParser.cpp"
	
	switch ( LA(1)) {
	case MAXHISTDRAWDOWN:
	{
		match(MAXHISTDRAWDOWN);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1509 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\n\tMax DD MSA Rule!\n\t\tMAXHISTDRAWDOWN: " << float1->getText() << std::endl;
				#else
					data->msaData_->maxHistDrawDown_ = atof(float1->getText().c_str());
				#endif
				
#line 3414 "MyParser.cpp"
		break;
	}
	case CURRENTEQUITY:
	{
		match(CURRENTEQUITY);
		match(ASSIGN);
		float3 = LT(1);
		match(FLOAT);
#line 1517 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tCURRENTEQUITY: " << float3->getText() << std::endl;
				#else
					data->msaData_->currentEquity_ = atof(float3->getText().c_str());
				#endif
				
#line 3431 "MyParser.cpp"
		break;
	}
	case MARGINPERCENTAGE:
	{
		match(MARGINPERCENTAGE);
		match(ASSIGN);
		float4 = LT(1);
		match(FLOAT);
#line 1525 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tMARGINPERCENTAGE: " << float4->getText() << std::endl;
				#else
					data->msaData_->marginPercentage_ = atof(float4->getText().c_str());
				#endif
				
#line 3448 "MyParser.cpp"
		break;
	}
	case MAXDDPERCENT:
	{
		match(MAXDDPERCENT);
		match(ASSIGN);
		float5 = LT(1);
		match(FLOAT);
#line 1533 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tMAXDDPERCENT: " << float5->getText() << std::endl;
				#else
					data->msaData_->maxDDPercent_ = atof(float5->getText().c_str());
				#endif
				
#line 3465 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::maxddrule(
	SymbolData * data
) {
	ANTLR_USE_NAMESPACE(antlr)RefToken  float1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  int3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 1545 "Yes.g"
	
			if(0 == data->maxDDData_)
			{
				data->maxDDData_ = new MaxDDData();
			}
		
#line 3489 "MyParser.cpp"
	
	switch ( LA(1)) {
	case PERCENTRISK:
	{
		match(PERCENTRISK);
		match(ASSIGN);
		float1 = LT(1);
		match(FLOAT);
#line 1553 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\n\tMax DD Rule!\n\t\tPERCENTRISK: " << float1->getText() << std::endl;
				#else
					data->maxDDData_->percentRisk_ = atof(float1->getText().c_str());
				#endif
				
#line 3506 "MyParser.cpp"
		break;
	}
	case MAXDRAWDOWNPIPS:
	{
		match(MAXDRAWDOWNPIPS);
		match(ASSIGN);
		int1 = LT(1);
		match(INT);
#line 1561 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tMAXDRAWDOWNPIPS: " << int1->getText() << std::endl;
				#else
					data->maxDDData_->maxDDPips_ = atoi(int1->getText().c_str());
				#endif
				
#line 3523 "MyParser.cpp"
		break;
	}
	case NUMBERTRADES:
	{
		match(NUMBERTRADES);
		match(ASSIGN);
		int2 = LT(1);
		match(INT);
#line 1569 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tNUMBERTRADES: " << int2->getText() << std::endl;
				#else
					data->maxDDData_->numTrades_ = atoi(int2->getText().c_str());
				#endif
				
#line 3540 "MyParser.cpp"
		break;
	}
	case NUMBERWINS:
	{
		match(NUMBERWINS);
		match(ASSIGN);
		int3 = LT(1);
		match(INT);
#line 1577 "Yes.g"
		
				#ifdef PARSERTEST
					std::cout << "\t\tNUMBERWINS: " << int3->getText() << std::endl;
				#else
					data->maxDDData_->numWins_ = atoi(int3->getText().c_str());
				#endif
				
#line 3557 "MyParser.cpp"
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
}

void MyParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* MyParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\"MBDemoTrading\"",
	"\"ForexAcct\"",
	"\"EquityAcct\"",
	"\"SimulateTrading\"",
	"\"TimeZone\"",
	"\"MaxTrades\"",
	"\"NumCandleMinutes\"",
	"\"LogPath\"",
	"\"LogL1Data\"",
	"\"YesTLPair\"",
	"\"VolatilityBreakOutWImprovedExit\"",
	"\"TrendLineWImprovedExit\"",
	"\"DynamicDefinition\"",
	"\"ROCWImprovedExit\"",
	"\"Symbol\"",
	"\"StartTradeTime\"",
	"\"EndTradeTime\"",
	"\"FirstEntrySignalTime\"",
	"\"CandleSickValue\"",
	"\"FirstTrendLineTime\"",
	"\"SecondTrendLineTime\"",
	"\"PipsStopLoss\"",
	"\"StopLoss\"",
	"\"TrailOnceStopLossTrigger\"",
	"\"TrailOnceStopLoss\"",
	"\"TakeProfit\"",
	"\"PIPSPrecision\"",
	"\"PIPSTrail\"",
	"\"NumBarsEvaluate\"",
	"\"BackFillDataFile\"",
	"\"DefaultLotSize\"",
	"\"TrendLineOpenPosition\"",
	"\"MaxDrawDown\"",
	"\"PercentRisk\"",
	"\"MaxDrawdownPips\"",
	"\"NumberTrades\"",
	"\"NumberWins\"",
	"\"MaxDrawDownMSA\"",
	"\"MaxHistDrawDown\"",
	"\"CurrentEquity\"",
	"\"MarginPercentage\"",
	"\"MaxDDPercent\"",
	"\"TLCrossTrading\"",
	"\"ReverseTrading\"",
	"\"TL1Bars\"",
	"\"TL2Bars\"",
	"\"StochBars\"",
	"\"RSIBars\"",
	"\"EMABars\"",
	"\"ATRMult\"",
	"\"ATRBars\"",
	"\"EntryATRBars\"",
	"\"ADXBars\"",
	"\"PlusDIBars\"",
	"\"MinusDIBars\"",
	"\"TimeExit\"",
	"\"mmstp\"",
	"\"ptlim\"",
	"\"stpa\"",
	"\"stpb\"",
	"\"ptga\"",
	"\"ROCBars\"",
	"\"ROCCount\"",
	"\"StdROCBars\"",
	"\"SlopeBars\"",
	"\"TLEndTime\"",
	"\"SpreadPricing\"",
	"\"MarketPricing\"",
	"\"MarketTPLimitPricing\"",
	"\"PipsTakeProfit\"",
	"\"HalfBarLimitPrice\"",
	"\"MatchBidLimitPricing\"",
	"\"VolatilityBreakoutEntryRule\"",
	"\"TurtleBreakoutEntryRule\"",
	"\"TrippleMVAEntryRule\"",
	"\"EMAScalpEntryRule\"",
	"\"TLScalpEntryRule\"",
	"\"TLScalp2EntryRule\"",
	"\"ADXEntry\"",
	"\"FiveMinuteEntryRule\"",
	"\"InvertTrade\"",
	"\"BarsFast\"",
	"\"BarsMedium\"",
	"\"BarsSlow\"",
	"\"ImprovedExitRule\"",
	"\"FixedExitRule\"",
	"\"ExitExitRule\"",
	"\"OpenOrderChase\"",
	"\"CloseOrderChase\"",
	"\"TPSLCloseMonitor\"",
	"NEWLINE",
	"=",
	"an identifer",
	"an integer value",
	"a floating point value",
	"a string literal",
	"{",
	"}",
	":",
	"\"TRUE\"",
	"\"FALSE\"",
	"\"True\"",
	"\"False\"",
	"\"true\"",
	"\"false\"",
	";",
	"?",
	"(",
	")",
	"[",
	"]",
	"|",
	"^",
	"&",
	",",
	".",
	"!",
	"<",
	"<<",
	">",
	">>",
	"/",
	"+",
	"-",
	"~",
	"*",
	"%",
	"::",
	"white space",
	"a preprocessor directive",
	"a comment",
	"a comment",
	"a character literal",
	"an escape sequence",
	"an escaped character value",
	"a digit",
	0
};

const unsigned long MyParser::_tokenSet_0_data_[] = { 1538523136UL, 532UL, 0UL, 0UL, 0UL, 0UL };
// "Symbol" "EndTradeTime" "FirstEntrySignalTime" "FirstTrendLineTime" 
// "SecondTrendLineTime" "PipsStopLoss" "TrailOnceStopLossTrigger" "TrailOnceStopLoss" 
// "PIPSPrecision" "DefaultLotSize" "MaxDrawDown" "MaxDrawDownMSA" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_0(_tokenSet_0_data_,6);
const unsigned long MyParser::_tokenSet_1_data_[] = { 3223060480UL, 4176478740UL, 1048577UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "Symbol" "StartTradeTime" "EndTradeTime" "PIPSPrecision" "PIPSTrail" 
// "DefaultLotSize" "MaxDrawDown" "MaxDrawDownMSA" "EMABars" "ATRMult" 
// "ATRBars" "EntryATRBars" "TimeExit" "mmstp" "ptlim" "stpa" "stpb" "ptga" 
// "InvertTrade" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_1(_tokenSet_1_data_,8);
const unsigned long MyParser::_tokenSet_2_data_[] = { 3223060480UL, 4165927444UL, 1048577UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "Symbol" "StartTradeTime" "EndTradeTime" "PIPSPrecision" "PIPSTrail" 
// "DefaultLotSize" "MaxDrawDown" "MaxDrawDownMSA" "TL1Bars" "TL2Bars" 
// "StochBars" "RSIBars" "ATRBars" "TimeExit" "mmstp" "ptlim" "stpa" "stpb" 
// "ptga" "InvertTrade" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long MyParser::_tokenSet_3_data_[] = { 3223060480UL, 4181721620UL, 1048591UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "Symbol" "StartTradeTime" "EndTradeTime" "PIPSPrecision" "PIPSTrail" 
// "DefaultLotSize" "MaxDrawDown" "MaxDrawDownMSA" "ATRBars" "ADXBars" 
// "TimeExit" "mmstp" "ptlim" "stpa" "stpb" "ptga" "ROCBars" "ROCCount" 
// "StdROCBars" "InvertTrade" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_3(_tokenSet_3_data_,8);
const unsigned long MyParser::_tokenSet_4_data_[] = { 1075052544UL, 532UL, 1058012608UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "Symbol" "EndTradeTime" "PIPSPrecision" "DefaultLotSize" "MaxDrawDown" 
// "MaxDrawDownMSA" "SpreadPricing" "MarketPricing" "MarketTPLimitPricing" 
// "HalfBarLimitPrice" "MatchBidLimitPricing" "VolatilityBreakoutEntryRule" 
// "TurtleBreakoutEntryRule" "TrippleMVAEntryRule" "EMAScalpEntryRule" 
// "TLScalpEntryRule" "TLScalp2EntryRule" "ADXEntry" "FiveMinuteEntryRule" 
// "ImprovedExitRule" "FixedExitRule" "ExitExitRule" "OpenOrderChase" "CloseOrderChase" 
// "TPSLCloseMonitor" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_4(_tokenSet_4_data_,8);
const unsigned long MyParser::_tokenSet_5_data_[] = { 0UL, 7340032UL, 1048576UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "EMABars" "ATRMult" "ATRBars" "InvertTrade" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_5(_tokenSet_5_data_,8);
const unsigned long MyParser::_tokenSet_6_data_[] = { 0UL, 20971520UL, 48UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "ATRBars" "ADXBars" "SlopeBars" "TLEndTime" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_6(_tokenSet_6_data_,8);
const unsigned long MyParser::_tokenSet_7_data_[] = { 2147483648UL, 4164943872UL, 1UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "PIPSTrail" "ATRBars" "TimeExit" "mmstp" "ptlim" "stpa" "stpb" "ptga" 
const ANTLR_USE_NAMESPACE(antlr)BitSet MyParser::_tokenSet_7(_tokenSet_7_data_,8);


