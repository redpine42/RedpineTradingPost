#pragma once

struct PurchaseData;

class PriceAgent
{
public:
	static PriceAgent * instance();
	static void removeInstance();
	void newPurchaseRequest(PurchaseData * data);
	void closePurchaseRequest(PurchaseData * data);

private:
	static PriceAgent * instance_;
	PriceAgent(void);
	~PriceAgent(void);
};
