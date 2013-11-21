#pragma once

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef set_h
#include <set>
#define set_h
#endif

struct OrderHistoryData;
struct OpenOrderData;
struct PositionData;
struct AccountData;
struct PurchaseData;
struct L1Data;

class PositionManager
{
public:
	static PositionManager * instance();

	void historyUpdate(OrderHistoryData * data);
	void orderUpdate(OpenOrderData *data);
	void positionUpdate(PositionData *data);
	void accountUpdate(AccountData * data);
	void purchaseUpdate(PurchaseData *data);
	void l1DataUpdate(L1Data * data);
	void updateOrderStatus(std::string & symbol, bool success, std::string & message);

	void positionClosed(const std::string & symbol);
	bool positionExists(std::string & symbol);

private:
	static PositionManager * instance_;
	PositionManager();
	~PositionManager(void);

	typedef std::set<std::string> PositionSet;
	typedef PositionSet::iterator PositionSetIter;

	PositionSet openPositions_;
};
