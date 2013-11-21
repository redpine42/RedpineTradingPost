#ifndef StrategyTypes_h
#define StrategyTypes_h


enum StrategyParameterEnum
{
	Default,
	Optimized
};

enum PositionStatus
{
    NoPosition,
	OpenOrderWaiting,
	OpenOrderPartialFill,
    OpenFilled,
    CloseOrderWaiting,
	CloseOrderPartialFill,
    CloseFilled,
    Canceled,
	Rejected
};


enum QuantityStrategiesEnum
{
	DefaultQuantityStrategy,
	MaxDDStrategy,
	TurtleSizingStrategy
};

#endif