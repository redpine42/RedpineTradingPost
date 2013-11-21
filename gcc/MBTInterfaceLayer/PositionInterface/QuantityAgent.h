#pragma once

struct PurchaseData;

class QuantityAgent
{
public:
	static QuantityAgent * instance();
	static void removeInstance();
	void newPurchaseRequest(PurchaseData * data);

private:
	static QuantityAgent * instance_;
	QuantityAgent(void);
	~QuantityAgent(void);


};
