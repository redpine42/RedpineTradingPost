#ifndef CandlePatternMetric_h
#define CandlePatternMetric_h

struct CandleData;

enum CandlePatterns
{
	CDL2CROWS,			//0
	CDL3BLACKCROWS,		//1
	CDL3INSIDE,			//2
	CDL3LINESTRIKE,		//3
	CDL3OUTSIDE,		//4
	CDL3STARSINSOUTH,	//5
	CDL3WHITESOLDIERS,	//6
	CDLABANDONEDBABY,	//7
	CDLADVANCEBLOCK,	//8
	CDLBELTHOLD,		//9
	CDLBREAKAWAY,		//10
	CDLCLOSINGMARUBOZU,	//11
	CDLCONCEALBABYSWALL,//12
	CDLCOUNTERATTACK,	//13
	CDLDARKCLOUDCOVER,	//14
	CDLDOJI,			//15
	CDLDOJISTAR,		//16
	CDLDRAGONFLYDOJI,	//17
	CDLENGULFING,		//18
	CDLEVENINGDOJISTAR,	//19
	CDLEVENINGSTAR,		//20
	CDLGAPSIDESIDEWHITE,//21
	CDLGRAVESTONEDOJI,	//22
	CDLHAMMER,			//23
	CDLHANGINGMAN,		//24
	CDLHARAMI,			//25
	CDLHARAMICROSS,		//26
	CDLHIGHWAVE,		//27
	CDLHIKKAKE,			//28
	CDLHIKKAKEMOD,		//29
	CDLHOMINGPIGEON,	//30
	CDLIDENTICAL3CROWS,	//31
	CDLINNECK,			//32
	CDLINVERTEDHAMMER,	//33
	CDLKICKING,			//34
	CDLKICKINGBYLENGTH,	//35
	CDLLADDERBOTTOM,	//36
	CDLLONGLEGGEDDOJI,	//37
	CDLLONGLINE,		//38
	CDLMARUBOZU,		//39
	CDLMATCHINGLOW,		//40
	CDLMATHOLD,			//41
	CDLMORNINGDOJISTAR,	//42
	CDLMORNINGSTAR,		//43
	CDLONNECK,			//44
	CDLPIERCING,		//45
	CDLRICKSHAWMAN,		//46
	CDLRISEFALL3METHODS,//47
	CDLSEPARATINGLINES,	//48
	CDLSHOOTINGSTAR,	//49
	CDLSHORTLINE,		//50
	CDLSPINNINGTOP,		//51
	CDLSTALLEDPATTERN,	//52
	CDLSTICKSANDWICH,	//53
	CDLTAKURI,			//54
	CDLTASUKIGAP,		//55
	CDLTHRUSTING,		//56
	CDLTRISTAR,			//57
	CDLUNIQUE3RIVER,	//58
	CDLUPSIDEGAP2CROWS,	//59
	CDLXSIDEGAP3METHODS //60
};

static int numPatternTypes(){return 61;}

int getPattern(CandlePatterns pattern, CandleData * data, long numSticks);
int * getAllPattern(CandlePatterns pattern, CandleData * data, long numSticks);


#endif

