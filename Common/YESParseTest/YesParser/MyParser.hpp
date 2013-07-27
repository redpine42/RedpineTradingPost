#ifndef INC_MyParser_hpp_
#define INC_MyParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20060930): "Yes.g" -> "MyParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "MyParserTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 2 "Yes.g"

#include <iostream>
#include <strstream>
#include <iomanip>

#include "MyDataTypes.h"

#ifndef PARSERTEST
#include "ConfigurationData.h"
#include "TimeZone.h"
#endif

#line 25 "MyParser.hpp"
class CUSTOM_API MyParser : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public MyParserTokenTypes
{
#line 140 "Yes.g"


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
#line 29 "MyParser.hpp"
public:
	void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
protected:
	MyParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	MyParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	MyParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	MyParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	MyParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return MyParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return MyParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return MyParser::tokenNames;
	}
	public: void fileparser();
	public: void configfile();
	public: void systemconfigitem();
	public: void pairconfigitem();
	public: bool  boolean_literal();
	public: std::string  pairitemlist(
		TLSymbolData * data
	);
	public: std::string  volbreakoutwepairitemlist(
		VolatilityBreakOutWImprovedExitData * data
	);
	public: std::string  trendlinewepairitemlist(
		TrendLineWImprovedExitData * data
	);
	public: std::string  rocwepairitemlist(
		ROCWImprovedExitData * data
	);
	public: std::string  dynamicpairs(
		DynamicRulesData * rulesdata
	);
	public: MyParser::TimeData  time();
	public: void msarules(
		SymbolData * data
	);
	public: void maxddrules(
		SymbolData * data
	);
	public: void pricing(
		DynamicRulesData * rulesdata
	);
	public: void entryrules(
		DynamicRulesData * rulesdata
	);
	public: void exitrules(
		DynamicRulesData * rulesdata
	);
	public: void openmonitor(
		DynamicRulesData * rulesdata
	);
	public: void closemonitor(
		DynamicRulesData * rulesdata
	);
	public: void spreadPricing(
		DynamicRulesData * rulesdata
	);
	public: void marketTPLimitPricing(
		DynamicRulesData * rulesdata
	);
	public: void volatiltiyEntry(
		DynamicRulesData * rulesdata
	);
	public: void turtleEntry(
		DynamicRulesData * rulesdata
	);
	public: void trippleMVAEntry(
		DynamicRulesData * rulesdata
	);
	public: void adxEntry(
		DynamicRulesData * rulesdata
	);
	public: void emaScalpEntry(
		DynamicRulesData * rulesdata
	);
	public: void tlScalpEntry(
		DynamicRulesData * rulesdata
	);
	public: void tlScalp2Entry(
		DynamicRulesData * rulesdata
	);
	public: void improvedExit(
		DynamicRulesData * rulesdata
	);
	public: void fixedExit(
		DynamicRulesData * rulesdata
	);
	public: void tpslCloseMonitor(
		DynamicRulesData * rulesdata
	);
	public: void msarule(
		SymbolData * data
	);
	public: void maxddrule(
		SymbolData * data
	);
public:
	ANTLR_USE_NAMESPACE(antlr)RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	ANTLR_USE_NAMESPACE(antlr)RefAST returnAST;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 140;
#else
	enum {
		NUM_TOKENS = 140
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_5;
	static const unsigned long _tokenSet_6_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_6;
	static const unsigned long _tokenSet_7_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_7;
};

#endif /*INC_MyParser_hpp_*/
