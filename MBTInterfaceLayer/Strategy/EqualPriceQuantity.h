// EqualPriceQuantity.h: interface for the EqualPriceQuantity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUALPRICEQUANTITY_H__0955A23C_014C_4FD7_A003_082798B2DF2C__INCLUDED_)
#define AFX_EQUALPRICEQUANTITY_H__0955A23C_014C_4FD7_A003_082798B2DF2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QuantityStrategy.h"

class EqualPriceQuantity : public QuantityStrategy  
{
public:
	EqualPriceQuantity();
	virtual ~EqualPriceQuantity();

	int buy(const std::string & symbol, const double price);
	int sellShort(const std::string & symbol, const double price);

private:
	int calculateSize(const std::string & symbol, const double price);
};

#endif // !defined(AFX_EQUALPRICEQUANTITY_H__0955A23C_014C_4FD7_A003_082798B2DF2C__INCLUDED_)
