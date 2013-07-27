#include "CandlePatternMetric.h"
#include "CandleData.h"
#include "ta_libc.h"


int getPattern(CandlePatterns pattern, CandleData * data, long numSticks)
{
	int ret = 0;
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);
	double * openData = CandleData::getData(data, CandleData::OPEN, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int * patternDataOut = new int[numSticks];
	TA_RetCode retCode;
	switch(pattern)
	{
	case CDL2CROWS:
		retCode = TA_CDL2CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3BLACKCROWS:
		retCode = TA_CDL3BLACKCROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3INSIDE:
		retCode = TA_CDL3INSIDE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3LINESTRIKE:
		retCode = TA_CDL3LINESTRIKE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3OUTSIDE:
		retCode = TA_CDL3OUTSIDE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3STARSINSOUTH:
		retCode = TA_CDL3WHITESOLDIERS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3WHITESOLDIERS:
		retCode = TA_CDL3WHITESOLDIERS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLABANDONEDBABY:
		retCode = TA_CDLABANDONEDBABY(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLADVANCEBLOCK:
		retCode = TA_CDLADVANCEBLOCK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLBELTHOLD:
		retCode = TA_CDLBELTHOLD(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLBREAKAWAY:
		retCode = TA_CDLBREAKAWAY(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCLOSINGMARUBOZU:
		retCode = TA_CDLCLOSINGMARUBOZU(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCONCEALBABYSWALL:
		retCode = TA_CDLCONCEALBABYSWALL(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCOUNTERATTACK:
		retCode = TA_CDLCOUNTERATTACK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDARKCLOUDCOVER:
		retCode = TA_CDLDARKCLOUDCOVER(0,numSticks-1,openData,highData,lowData,closeData,0.5,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDOJI:
		retCode = TA_CDLDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDOJISTAR:
		retCode = TA_CDLDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDRAGONFLYDOJI:
		retCode = TA_CDLDRAGONFLYDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLENGULFING:
		retCode = TA_CDLENGULFING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLEVENINGDOJISTAR:
		retCode = TA_CDLEVENINGDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLEVENINGSTAR:
		retCode = TA_CDLEVENINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLGAPSIDESIDEWHITE:
		retCode = TA_CDLGAPSIDESIDEWHITE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLGRAVESTONEDOJI:
		retCode = TA_CDLGRAVESTONEDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHAMMER:
		retCode = TA_CDLHAMMER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHANGINGMAN:
		retCode = TA_CDLHANGINGMAN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHARAMI:
		retCode = TA_CDLHARAMI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHARAMICROSS:
		retCode = TA_CDLHARAMICROSS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIGHWAVE:
		retCode = TA_CDLHIGHWAVE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIKKAKE:
		retCode = TA_CDLHIKKAKE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIKKAKEMOD:
		retCode = TA_CDLHIKKAKEMOD(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHOMINGPIGEON:
		retCode = TA_CDLHOMINGPIGEON(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLIDENTICAL3CROWS:
		retCode = TA_CDLIDENTICAL3CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLINNECK:
		retCode = TA_CDLINNECK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLINVERTEDHAMMER:
		retCode = TA_CDLINVERTEDHAMMER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLKICKING:
		retCode = TA_CDLKICKING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLKICKINGBYLENGTH:
		retCode = TA_CDLKICKINGBYLENGTH(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLADDERBOTTOM:
		retCode = TA_CDLLADDERBOTTOM(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLONGLEGGEDDOJI:
		retCode = TA_CDLLONGLEGGEDDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLONGLINE:
		retCode = TA_CDLLONGLINE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMARUBOZU:
		retCode = TA_CDLMARUBOZU(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMATCHINGLOW:
		retCode = TA_CDLMATCHINGLOW(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMATHOLD:
		retCode = TA_CDLMATHOLD(0,numSticks-1,openData,highData,lowData,closeData,0.5,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMORNINGDOJISTAR:
		retCode = TA_CDLMORNINGDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMORNINGSTAR:
		retCode = TA_CDLMORNINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLONNECK:
		retCode = TA_CDLONNECK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLPIERCING:
		retCode = TA_CDLPIERCING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLRICKSHAWMAN:
		retCode = TA_CDLRICKSHAWMAN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLRISEFALL3METHODS:
		retCode = TA_CDLRISEFALL3METHODS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSEPARATINGLINES:
		retCode = TA_CDLSEPARATINGLINES(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSHOOTINGSTAR:
		retCode = TA_CDLSHOOTINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSHORTLINE:
		retCode = TA_CDLSHORTLINE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSPINNINGTOP:
		retCode = TA_CDLSPINNINGTOP(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSTALLEDPATTERN:
		retCode = TA_CDLSTALLEDPATTERN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSTICKSANDWICH:
		retCode = TA_CDLSTICKSANDWICH(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTAKURI:
		retCode = TA_CDLTAKURI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTASUKIGAP:
		retCode = TA_CDLTASUKIGAP(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTHRUSTING:
		retCode = TA_CDLTHRUSTING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTRISTAR:
		retCode = TA_CDLTRISTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLUNIQUE3RIVER:
		retCode = TA_CDLUNIQUE3RIVER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLUPSIDEGAP2CROWS:
		retCode = TA_CDLUPSIDEGAP2CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLXSIDEGAP3METHODS:
		retCode = TA_CDLXSIDEGAP3METHODS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	default:
		break;
	}

	if(outNbElement == 0)
	{
		ret = 0;
	}
	else
	{
		ret = patternDataOut[outNbElement - 1];
	}


	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] openData;
	delete [] patternDataOut;

	return ret;
}

int * getAllPattern(CandlePatterns pattern, CandleData * data, long numSticks)
{
	double * openData = CandleData::getData(data, CandleData::OPEN, numSticks);
	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);
	double * closeData = CandleData::getData(data, CandleData::CLOSE, numSticks);

	int outNbElement = 0;
	int outBeg = 0;

	int * patternDataOut = new int[numSticks];
	memset(patternDataOut,0,numSticks * sizeof(int));


	TA_RetCode retCode;
	switch(pattern)
	{
	case CDL2CROWS:
		retCode = TA_CDL2CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3BLACKCROWS:
		retCode = TA_CDL3BLACKCROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3INSIDE:
		retCode = TA_CDL3INSIDE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3LINESTRIKE:
		retCode = TA_CDL3LINESTRIKE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3OUTSIDE:
		retCode = TA_CDL3OUTSIDE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3STARSINSOUTH:
		retCode = TA_CDL3WHITESOLDIERS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDL3WHITESOLDIERS:
		retCode = TA_CDL3WHITESOLDIERS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLABANDONEDBABY:
		retCode = TA_CDLABANDONEDBABY(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLADVANCEBLOCK:
		retCode = TA_CDLADVANCEBLOCK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLBELTHOLD:
		retCode = TA_CDLBELTHOLD(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLBREAKAWAY:
		retCode = TA_CDLBREAKAWAY(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCLOSINGMARUBOZU:
		retCode = TA_CDLCLOSINGMARUBOZU(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCONCEALBABYSWALL:
		retCode = TA_CDLCONCEALBABYSWALL(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLCOUNTERATTACK:
		retCode = TA_CDLCOUNTERATTACK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDARKCLOUDCOVER:
		retCode = TA_CDLDARKCLOUDCOVER(0,numSticks-1,openData,highData,lowData,closeData,0.5,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDOJI:
		retCode = TA_CDLDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDOJISTAR:
		retCode = TA_CDLDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLDRAGONFLYDOJI:
		retCode = TA_CDLDRAGONFLYDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLENGULFING:
		retCode = TA_CDLENGULFING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLEVENINGDOJISTAR:
		retCode = TA_CDLEVENINGDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLEVENINGSTAR:
		retCode = TA_CDLEVENINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLGAPSIDESIDEWHITE:
		retCode = TA_CDLGAPSIDESIDEWHITE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLGRAVESTONEDOJI:
		retCode = TA_CDLGRAVESTONEDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHAMMER:
		retCode = TA_CDLHAMMER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHANGINGMAN:
		retCode = TA_CDLHANGINGMAN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHARAMI:
		retCode = TA_CDLHARAMI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHARAMICROSS:
		retCode = TA_CDLHARAMICROSS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIGHWAVE:
		retCode = TA_CDLHIGHWAVE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIKKAKE:
		retCode = TA_CDLHIKKAKE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHIKKAKEMOD:
		retCode = TA_CDLHIKKAKEMOD(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLHOMINGPIGEON:
		retCode = TA_CDLHOMINGPIGEON(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLIDENTICAL3CROWS:
		retCode = TA_CDLIDENTICAL3CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLINNECK:
		retCode = TA_CDLINNECK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLINVERTEDHAMMER:
		retCode = TA_CDLINVERTEDHAMMER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLKICKING:
		retCode = TA_CDLKICKING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLKICKINGBYLENGTH:
		retCode = TA_CDLKICKINGBYLENGTH(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLADDERBOTTOM:
		retCode = TA_CDLLADDERBOTTOM(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLONGLEGGEDDOJI:
		retCode = TA_CDLLONGLEGGEDDOJI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLLONGLINE:
		retCode = TA_CDLLONGLINE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMARUBOZU:
		retCode = TA_CDLMARUBOZU(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMATCHINGLOW:
		retCode = TA_CDLMATCHINGLOW(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMATHOLD:
		retCode = TA_CDLMATHOLD(0,numSticks-1,openData,highData,lowData,closeData,0.5,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMORNINGDOJISTAR:
		retCode = TA_CDLMORNINGDOJISTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLMORNINGSTAR:
		retCode = TA_CDLMORNINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,0.3,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLONNECK:
		retCode = TA_CDLONNECK(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLPIERCING:
		retCode = TA_CDLPIERCING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLRICKSHAWMAN:
		retCode = TA_CDLRICKSHAWMAN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLRISEFALL3METHODS:
		retCode = TA_CDLRISEFALL3METHODS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSEPARATINGLINES:
		retCode = TA_CDLSEPARATINGLINES(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSHOOTINGSTAR:
		retCode = TA_CDLSHOOTINGSTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSHORTLINE:
		retCode = TA_CDLSHORTLINE(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSPINNINGTOP:
		retCode = TA_CDLSPINNINGTOP(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSTALLEDPATTERN:
		retCode = TA_CDLSTALLEDPATTERN(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLSTICKSANDWICH:
		retCode = TA_CDLSTICKSANDWICH(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTAKURI:
		retCode = TA_CDLTAKURI(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTASUKIGAP:
		retCode = TA_CDLTASUKIGAP(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTHRUSTING:
		retCode = TA_CDLTHRUSTING(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLTRISTAR:
		retCode = TA_CDLTRISTAR(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLUNIQUE3RIVER:
		retCode = TA_CDLUNIQUE3RIVER(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLUPSIDEGAP2CROWS:
		retCode = TA_CDLUPSIDEGAP2CROWS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	case CDLXSIDEGAP3METHODS:
		retCode = TA_CDLXSIDEGAP3METHODS(0,numSticks-1,openData,highData,lowData,closeData,&outBeg,&outNbElement,patternDataOut);
		break;
	default:
		break;
	}

	int * ret = new int[outNbElement + outBeg];
	memset(ret,0,(outNbElement + outBeg) * sizeof(int));
	memcpy(&ret[outBeg],patternDataOut,outNbElement*sizeof(int));

	delete [] highData;
	delete [] lowData;
	delete [] closeData;
	delete [] openData;
	delete [] patternDataOut;

	return ret;
}