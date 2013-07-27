#ifndef TrendDesc_h
#define TrendDesc_h

struct CandleData;

enum TrendState
{
	Consolidation,
	TrendUp,
	TrendDown,
	Pullback,
	Reverse,
	Unknown
};

struct TrendDesc
{
	// current description
	double currentHH_;
	double currentLL_;
	double currentHL_;
	double currentLH_;
	TrendState currentState_;

};

TrendDesc * getTrendDescriptions(CandleData * data, long numSticks, unsigned int lookBack = 24);

#endif
