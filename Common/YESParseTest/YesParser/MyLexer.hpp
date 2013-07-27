#ifndef INC_MyLexer_hpp_
#define INC_MyLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.7 (20060930): "Yes.g" -> "MyLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "MyParserTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 2 "Yes.g"

#include <iostream>
#include <strstream>
#include <iomanip>

#include "MyDataTypes.h"

#ifndef PARSERTEST
#include "ConfigurationData.h"
#include "TimeZone.h"
#endif

#line 25 "MyLexer.hpp"
class CUSTOM_API MyLexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public MyParserTokenTypes
{
#line 1607 "Yes.g"

public:
	bool done;


	void uponEOF()
	{
		done = true;
	}
#line 29 "MyLexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	MyLexer(ANTLR_USE_NAMESPACE(std)istream& in);
	MyLexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	MyLexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mSEMI(bool _createToken);
	public: void mQUESTION(bool _createToken);
	public: void mLPAREN(bool _createToken);
	public: void mRPAREN(bool _createToken);
	public: void mLBRACK(bool _createToken);
	public: void mRBRACK(bool _createToken);
	public: void mLCURLY(bool _createToken);
	public: void mRCURLY(bool _createToken);
	public: void mOR(bool _createToken);
	public: void mXOR(bool _createToken);
	public: void mAND(bool _createToken);
	public: void mCOLON(bool _createToken);
	public: void mCOMMA(bool _createToken);
	public: void mDOT(bool _createToken);
	public: void mASSIGN(bool _createToken);
	public: void mNOT(bool _createToken);
	public: void mLT_(bool _createToken);
	public: void mLSHIFT(bool _createToken);
	public: void mGT(bool _createToken);
	public: void mRSHIFT(bool _createToken);
	public: void mDIV(bool _createToken);
	public: void mPLUS(bool _createToken);
	public: void mMINUS(bool _createToken);
	public: void mTILDE(bool _createToken);
	public: void mSTAR(bool _createToken);
	public: void mMOD(bool _createToken);
	public: void mSCOPEOP(bool _createToken);
	public: void mWS_(bool _createToken);
	public: void mPREPROC_DIRECTIVE(bool _createToken);
	public: void mSL_COMMENT(bool _createToken);
	public: void mML_COMMENT(bool _createToken);
	public: void mSTRING_LITERAL(bool _createToken);
	public: void mCHAR_LITERAL(bool _createToken);
	protected: void mESC(bool _createToken);
	protected: void mVOCAB(bool _createToken);
	protected: void mDIGIT(bool _createToken);
	public: void mINT(bool _createToken);
	public: void mFLOAT(bool _createToken);
	public: void mID(bool _createToken);
private:
	
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
};

#endif /*INC_MyLexer_hpp_*/
