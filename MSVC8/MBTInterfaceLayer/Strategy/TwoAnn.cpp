// TwoAnnEntry.cpp: implementation of the TwoAnnEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "TwoAnn.h"

#include "StockWatch.h"
#include "ConfigurationData.h"
#include "CandleStickManager.h"
#include <strstream>
#include "DataLogger.h"
#include "FANNData.h"

#include "CandleStickManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TwoAnn::TwoAnn(StockWatch * stock, 
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
			   long endTradeTime)
	: EntryStrategy(stock, "Two Ann Entry",startTradeTime, endTradeTime),
	  ann1Lower_(ann1Lower),
	  ann2Lower_(ann2Lower),
	  ann3Lower_(ann3Lower),
	  ann4Lower_(ann4Lower),
	  ann5Lower_(ann5Lower),
	  ann6Lower_(ann6Lower)
{
	precision_ = ConfigurationData::instance()->precision(stock->symbol());
	std::string name = stock->symbol();
	int pos = name.find("/");
	if( pos != std::string::npos)
	{
		name.replace(pos, 1, "");
	}
	std::string debugPath = ConfigurationData::instance()->logPath();
	debugPath += "\\";
	debugPath += name;
	debugPath += "TwoAnnData.csv";

	bool fileExists = false;
	std::fstream fin;
	fin.open(debugPath.c_str(),std::ios::in);
	if( fin.is_open() )
	{
		fileExists = true;
	}
	fin.close();

	debugLog_.open(debugPath.c_str(), std::ios_base::app);
	if(!fileExists)
	{
		debugLog_ <<"Symbol,Stick End Time, Open Price, High Price, Low Price, Close Price, Ann 1 Data, Ann 2 Data" << std::endl;
	}

	ann1_ = fann_create_from_file(ann1File.c_str());    
	ann2_ = fann_create_from_file(ann2File.c_str());    
	ann3_ = fann_create_from_file(ann3File.c_str());    
	ann4_ = fann_create_from_file(ann4File.c_str());    
	ann5_ = fann_create_from_file(ann5File.c_str());    
	ann6_ = fann_create_from_file(ann6File.c_str());    
	ann7_ = fann_create_from_file(ann7File.c_str());    
	ann8_ = fann_create_from_file(ann8File.c_str());    
	annChairman_ = fann_create_from_file(annChairmanFile.c_str());    
	data_ = new FANNData(stock_->symbol());
}

TwoAnn::~TwoAnn()
{

	fann_destroy(ann1_);
	fann_destroy(ann2_);
	fann_destroy(ann3_);
	fann_destroy(ann4_);
	fann_destroy(ann5_);
	fann_destroy(ann6_);
	fann_destroy(ann7_);
	fann_destroy(ann8_);
	fann_destroy(annChairman_);
	delete data_;
}

bool TwoAnn::sellShort()
{
	return false;
}

bool TwoAnn::buy(CandleStick * stick)
{
	int numSticks = CandleStickManager::instance()->numSticks(stock_->symbol());
	if(!isTradingTime(stock_->time()) || numSticks < 12)
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		fann_type *annData = new fann_type[8];

		fann_type * ann1Data = data_->getCandleData();
		fann_scale_input( ann1_, ann1Data );
		fann_type * ann1Out = fann_run( ann1_, ann1Data );
		annData[0] = ann1Out[0];
		delete [] ann1Data;

		fann_type * ann2Data = data_->getCandleData();
		fann_scale_input( ann2_, ann2Data );
		fann_type * ann2Out = fann_run( ann2_, ann2Data );
		annData[1] = ann2Out[0];
		delete [] ann2Data;

		fann_type * ann3Data = data_->getGMMAData();
		fann_scale_input( ann3_, ann3Data );
		fann_type * ann3Out = fann_run( ann3_, ann3Data );
		annData[2] = ann3Out[0];
		delete [] ann3Data;

		fann_type * ann4Data = data_->getGMMAData();
		fann_scale_input( ann4_, ann4Data );
		fann_type * ann4Out = fann_run( ann4_, ann4Data );
		annData[3] = ann4Out[0];
		delete [] ann4Data;

		fann_type * ann5Data = data_->getHilbertData();
		fann_scale_input( ann5_, ann5Data );
		fann_type * ann5Out = fann_run( ann5_, ann5Data );
		annData[4] = ann5Out[0];
		delete [] ann5Data;

		fann_type * ann6Data = data_->getHilbertData();
		fann_scale_input( ann6_, ann6Data );
		fann_type * ann6Out = fann_run( ann6_, ann6Data );
		annData[5] = ann6Out[0];
		delete [] ann6Data;

		fann_type * ann7Data = data_->getMishMashData();
		fann_scale_input( ann7_, ann7Data );
		fann_type * ann7Out = fann_run( ann7_, ann7Data );
		annData[6] = ann7Out[0];
		delete [] ann7Data;

		fann_type * ann8Data = data_->getMishMashData();
		fann_scale_input( ann8_, ann8Data );
		fann_type * ann8Out = fann_run( ann8_, ann8Data );
		annData[7] = ann8Out[0];
		delete [] ann8Data;

		fann_scale_input( annChairman_, annData );
		fann_type * annChairmanOut = fann_run( annChairman_, annData );
		fann_descale_output(annChairman_, annChairmanOut);
		double result = annChairmanOut[0];
		delete [] annData;

		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << result << std::endl;

		double vote = 0.0;

		if(result < -ann1Lower_)
		{
			std::strstream strstr;
			strstr << "\n\tTwo Ann Entry (Long)\nClose Price: " << closePrice 
				   << "\nChairman Data: " << result << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}

bool TwoAnn::buy()
{
	return false;
}

bool TwoAnn::sellShort(CandleStick * stick)
{
	int numSticks = CandleStickManager::instance()->numSticks(stock_->symbol());
	if(!isTradingTime(stock_->time()) || numSticks < 12)
	{
		return false;
	}
	
	if(0 != stick)
	{
		double closePrice = stick->closePrice();
		double openPrice = stick->openPrice();

		fann_type *annData = new fann_type[8];

		fann_type * ann1Data = data_->getCandleData();
		fann_scale_input( ann1_, ann1Data );
		fann_type * ann1Out = fann_run( ann1_, ann1Data );
		annData[0] = ann1Out[0];
		delete [] ann1Data;

		fann_type * ann2Data = data_->getCandleData();
		fann_scale_input( ann2_, ann2Data );
		fann_type * ann2Out = fann_run( ann2_, ann2Data );
		annData[1] = ann2Out[0];
		delete [] ann2Data;

		fann_type * ann3Data = data_->getGMMAData();
		fann_scale_input( ann3_, ann3Data );
		fann_type * ann3Out = fann_run( ann3_, ann3Data );
		annData[2] = ann3Out[0];
		delete [] ann3Data;

		fann_type * ann4Data = data_->getGMMAData();
		fann_scale_input( ann4_, ann4Data );
		fann_type * ann4Out = fann_run( ann4_, ann4Data );
		annData[3] = ann4Out[0];
		delete [] ann4Data;

		fann_type * ann5Data = data_->getHilbertData();
		fann_scale_input( ann5_, ann5Data );
		fann_type * ann5Out = fann_run( ann5_, ann5Data );
		annData[4] = ann5Out[0];
		delete [] ann5Data;

		fann_type * ann6Data = data_->getHilbertData();
		fann_scale_input( ann6_, ann6Data );
		fann_type * ann6Out = fann_run( ann6_, ann6Data );
		annData[5] = ann6Out[0];
		delete [] ann6Data;

		fann_type * ann7Data = data_->getMishMashData();
		fann_scale_input( ann7_, ann7Data );
		fann_type * ann7Out = fann_run( ann7_, ann7Data );
		annData[6] = ann7Out[0];
		delete [] ann7Data;

		fann_type * ann8Data = data_->getMishMashData();
		fann_scale_input( ann8_, ann8Data );
		fann_type * ann8Out = fann_run( ann8_, ann8Data );
		annData[7] = ann8Out[0];
		delete [] ann8Data;

		fann_scale_input( annChairman_, annData );
		fann_type * annChairmanOut = fann_run( annChairman_, annData );
		fann_descale_output(annChairman_, annChairmanOut);
		double result = annChairmanOut[0];
		delete [] annData;

		debugLog_ << stock_->symbol() << ","
			   << TimeZone::instance()->formatDateTZ(stick->date(), stick->endTime()) << " " << TimeZone::instance()->formatTZ(stick->endTime()) << ","
			   << openPrice << ","
			   << stick->highPrice() << ","
			   << stick->lowPrice() << ","
			   << closePrice << ","
			   << result << std::endl;

		double vote = 0.0;

		if(result > ann2Lower_)
		{
			std::strstream strstr;
			strstr << "\n\tTwo Ann Entry (Short)\nClose Price: " << closePrice 
				   << "\nChairman Data: " << result << std::ends;
			std::string  msg = strstr.str();
			strstr.clear();
			strstr.rdbuf()->freeze(0);

			DataLogger::instance()->recordDebug(msg, stock_->symbol());

			return true;
		}
	}
	return false;
}
