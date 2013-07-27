#pragma once

struct PurchaseData;
class SymbolData;

class PurchaseManager
{
public:
	static PurchaseManager * instance();
	static void removeInstance();
	void trade(PurchaseData * data);
	void closeTrade(PurchaseData * data);

private:
	static PurchaseManager * instance_;

	PurchaseManager(void);
	~PurchaseManager(void);

};
