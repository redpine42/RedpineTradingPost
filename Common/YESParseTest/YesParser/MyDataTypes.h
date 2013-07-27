#ifndef MyDataTypes_h
#define MyDataTypes_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

enum TradingSystem
{
	UndefinedStrategy,
	TLTrading,
	VolatilityBreakOutWImprovedExit,
	DynamicRulesTrading,
	TrendLineWImprovedExit,
	ROCWImprovedExit
};

	struct MaxDDMSAData
	{
	public:
		void printData(std::ofstream & ostrm);

		double maxHistDrawDown_;		// USD Maximum historical drawdown
		double currentEquity_;   		// USD Current equity amount available for trading this pair 
		double marginPercentage_;		// Percentage of required for margin
		double maxDDPercent_;			// Max allowable draw down. Express as a percentage 

	};

	struct MaxDDData
	{
	public:
		void printData(std::ofstream & ostrm);

		double percentRisk_;
		int maxDDPips_;
		int numTrades_;
		int numWins_;
	};

	class EntryRule
	{
	public:
		virtual ~EntryRule(){};
		virtual void printData(std::ofstream & ostrm){};
		virtual std::string getName()=0;

	};

	class TestEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TestEntry";}

	};

	class ADXEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "ADXEntry";}

		int adxBars_;
		int plusDIBars_;
		int minusDIBars_;
	};

	class GeneticProgramEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "GeneticProgramEntry";}

		std::string algorithm_;
	};

	class TLGeneticProgramEntry : public GeneticProgramEntry
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TLGeneticProgramEntry";}

		long TLStartTime_;
		long TLEndTime_;
	};


	class VolatilityBreakoutEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "VolatilityBreakoutEntry";}

		bool invertTrade_;
		int ATRBars_;
		int EMABars_;
		double ATRMult_;
	};

	class TurtleBreakoutEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TurtleBreakoutEntry";}

		int numBars_;
	};

	class TripleMVAEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TripleMVAEntry";}

		long fast_;
		long medium_;
		long slow_;
	};

	class EMAScalpEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "EMAScalpEntry";}

		int adxBars_;
		int atrBars_;
		int emaBars_;
	};

	class TLScalpEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TLScalpEntry";}

		int adxBars_;
		int atrBars_;
		int slopeBars_;
		int tlEndTime_;
	};
	class TLScalp2Entry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "TLScalp2Entry";}

		int adxBars_;
		int atrBars_;
		int slopeBars_;
	};

	class CandlePatternEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "CandlePatternEntry";}
	};

	class FiveMinuteEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "FiveMinute";}
	};

	class FXPrimeEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "FXPrime";}

		int rsiBars_;
		int cciSlowBars_;
		int cciFastBars_;
	};

	class ANNEntry : public EntryRule
	{
		void printData(std::ofstream & ostrm);
		std::string getName(){return "ANNEntry";}
	};

	class CommitteeVoteEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "CommitteeVoteEntry";}
		int ann1Lower_;
		int ann2Lower_;
		int ann3Lower_;
		int ann4Lower_;
		int ann5Lower_;
		int ann6Lower_;
		int ann7Lower_;
		int ann8Lower_;
		std::string ann1ScaleType_;
		std::string ann2ScaleType_;
		std::string ann3ScaleType_;
		std::string ann4ScaleType_;
		std::string ann5ScaleType_;
		std::string ann6ScaleType_;
		std::string ann7ScaleType_;
		std::string ann8ScaleType_;
	};

	class RLCandleEntry : public EntryRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "RLCandleEntry";}
		std::string entryAgent_;
	};

	class ExitRule
	{
	public:
		virtual ~ExitRule(){};
		virtual void printData(std::ofstream & ostrm){};

	};

	class RLCandleExit : public ExitRule
	{
	public:
		void printData(std::ofstream & ostrm);
		std::string getName(){return "RLCandleExit";}
		std::string exitAgent_;
	};

	class FixedExitRule : public ExitRule
	{
	public:
		~FixedExitRule(){};
		void printData(std::ofstream & ostrm);

		int takeProfit_;
		int stopLoss_;
		int timeExit_;
	};

	class TestExitRule : public ExitRule
	{
	public:
		~TestExitRule(){};
		void printData(std::ofstream & ostrm);
	};

	class HAExitRule : public ExitRule
	{
	public:
		~HAExitRule(){};
		void printData(std::ofstream & ostrm);

		double takeProfit_;
		double stopLoss_;
	};

	class ExitExitRule : public ExitRule
	{
	public:
		~ExitExitRule(){};
		void printData(std::ofstream & ostrm);
	};

	class FXPrimeExitRule : public ExitRule
	{
	public:
		~FXPrimeExitRule(){};
		void printData(std::ofstream & ostrm);
		int stopLoss_;
		int takeProfit_;
		int trailTrigger_;
		int trailStop_;
		int HAExitPips_;
	};

	class ImprovedExitRule : public ExitRule
	{
	public:
		~ImprovedExitRule(){};
		void printData(std::ofstream & ostrm);

		int pipsTrail_;
		int atrBars_;
		int timeExit_;
		double mmstp_;
		double ptlim_;
		double stpa_;
		double stpb_;
		double ptga_;
	};

	class OpenMonitor
	{
	public:
		virtual ~OpenMonitor(){};
		virtual void printData(std::ofstream & ostrm){};

	};
	class OpenChaseMonitor : public OpenMonitor
	{
	public:
		virtual ~OpenChaseMonitor(){};
		virtual void printData(std::ofstream & ostrm);

	};
	class CloseMonitor
	{
	public:
		virtual ~CloseMonitor(){};
		virtual void printData(std::ofstream & ostrm){};

	};
	class CloseChaseMonitor : public CloseMonitor
	{
	public:
		virtual ~CloseChaseMonitor(){};
		virtual void printData(std::ofstream & ostrm);

	};
	class TPSLCloseMonitor : public CloseMonitor
	{
	public:
		virtual ~TPSLCloseMonitor(){};
		virtual void printData(std::ofstream & ostrm);

		int stopLoss_;
	};


	class PriceRule
	{
	public:
		virtual ~PriceRule(){};
		virtual void printData(std::ofstream & ostrm){};

	};

	class MarketPricingRule : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

	};
	class MarketLimitPricingRule : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

	};
	class MarketTPLimitPricingRule : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

		int takeProfit_;
	};
	class HalfBarPricingRule : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

	};
	class MatchBidPricingRule : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

	};

	class SpreadPricing : public PriceRule
	{
	public:
		void printData(std::ofstream & ostrm);

		double pipsStopLoss_;
		double pipsTakeProfit_;
	};


	class SymbolData
	{
	public:
		virtual ~SymbolData(){};
		virtual std::string getName()=0;
		virtual TradingSystem getSystem()=0;
		virtual void printData(std::ofstream & ostrm, std::string & symbol){};

		double pipsPrecision_;
		long endTradeTime_;
		long startTradeTime_;

		int defaultLotSize_;
		MaxDDMSAData * msaData_;
		MaxDDData * maxDDData_;
	};

	class TLSymbolData : public SymbolData
	{
	public:
		void printData(std::ofstream & ostrm, std::string & symbol);
		std::string getName(){return "TLTrading";}
		TradingSystem getSystem(){return TLTrading;}

		long firstEntrySignalTime_;
		double trailOnceStopLossTrigger_;
		double trailOnceStopLoss_;
		long TLStartTime_;
		long TLEndTime_;
		double pipsStopLoss_;

	};



	class VolatilityBreakOutWImprovedExitData : public SymbolData
	{
	public:
		void printData(std::ofstream & ostrm, std::string & symbol);

		std::string getName(){return "VolatilityBreakOutWImprovedExit";}
		TradingSystem getSystem(){return VolatilityBreakOutWImprovedExit;}

		bool invertTrade_;
		int pipsTrail_;
		int atrBars_;
		int timeExit_;
		double mmstp_;
		double ptlim_;
		double stpa_;
		double stpb_;
		double ptga_;
		int entryATRBars_;
		int EMABars_;
		double ATRMult_;
	};

	class TrendLineWImprovedExitData : public SymbolData
	{
	public:
		void printData(std::ofstream & ostrm, std::string & symbol);

		std::string getName(){return "TrendLineWImprovedExit";}
		TradingSystem getSystem(){return TrendLineWImprovedExit;}

		bool invertTrade_;
		int pipsTrail_;
		int atrBars_;
		int timeExit_;
		double mmstp_;
		double ptlim_;
		double stpa_;
		double stpb_;
		double ptga_;
		int TL1Bars_;
		int TL2Bars_;
		int RSIBars_;
		int StochBars_;
	};

	class ROCWImprovedExitData : public SymbolData
	{
	public:
		void printData(std::ofstream & ostrm, std::string & symbol);

		std::string getName(){return "ROCWImprovedExit";}
		TradingSystem getSystem(){return ROCWImprovedExit;}

		bool invertTrade_;
		int pipsTrail_;
		int atrBars_;
		int timeExit_;
		double mmstp_;
		double ptlim_;
		double stpa_;
		double stpb_;
		double ptga_;
		int adxBars_;
		int rocBars_;
		int ROCCount_;
		int stdROCBars_;
	};

	class DynamicRulesData : public SymbolData
	{
	public:
		void printData(std::ofstream & ostrm, std::string & symbol);

		std::string getName(){return entryRule_->getName();}
		TradingSystem getSystem(){return DynamicRulesTrading;}

		PriceRule * priceRule_;
		EntryRule * entryRule_;
		ExitRule * exitRule_;
		OpenMonitor * openMonitor_;
		CloseMonitor * closeMonitor_;
	};

#endif
