// TwoAnnEntry.h: interface for the TwoAnnEntry class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TWOANN_H
#define TWOANN_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CandleStick;
class FANNData;
#include <fstream>

#include "EntryStrategy.h"
#include "fann.h"

class TwoAnn : public EntryStrategy  
{
public:
	TwoAnn(StockWatch * stock, 
		   std::string & ann1File, 
		   std::string & ann2File, 
		   std::string & ann3File, 
		   std::string & ann4File, 
		   std::string & ann5File, 
		   std::string & ann6File, 
		   std::string & ann7File, 
		   std::string & ann8File, 
		   std::string & annChairmanFile, 
		   int ann1Lower,
		   int ann2Lower, 
		   int ann3Lower,
		   int ann4Lower, 
		   int ann5Lower,
		   int ann6Lower, 
		   long startTradeTime, 
		   long endTradeTime);
	virtual ~TwoAnn();

	bool buy(CandleStick * stick);
	bool sellShort(CandleStick * stick);

	bool buy();
	bool sellShort();

	void reset(){};
	void newTradeDay(){};

private:
	double precision_;
	std::ofstream debugLog_;

	int ann1Lower_;
	int ann2Lower_;
	int ann3Lower_;
	int ann4Lower_;
	int ann5Lower_;
	int ann6Lower_;

	fann * ann1_;    
	fann * ann2_;
	fann * ann3_;    
	fann * ann4_;
	fann * ann5_;    
	fann * ann6_;
	fann * ann7_;
	fann * ann8_;
	fann * annChairman_;
	FANNData * data_;

};

#endif 

