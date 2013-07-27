// FANNData.h: interface for the FANNData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FANNDATA_H__4EE79656_8E73_4199_A56F_DA0560D1F0DD__INCLUDED_)
#define AFX_FANNDATA_H__4EE79656_8E73_4199_A56F_DA0560D1F0DD__INCLUDED_

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef FANN_H
#include "fann.h"
#define FANN_H
#endif

class FANNData  
{
public:
	FANNData(std::string & symbol);
	virtual ~FANNData(void);

	fann_type * getCandleData();
	fann_type * getGMMAData();
	fann_type * getHilbertData();
	fann_type * getMishMashData();

	std::string symbol(){return symbol_;}
private:
	double * HIGH_;
	double * LOW_;
	double * CLOSE_;
	double * OPEN_;

	double precision_;

	std::string symbol_;
};

#endif // !defined(AFX_FANNDATA_H__4EE79656_8E73_4199_A56F_DA0560D1F0DD__INCLUDED_)
