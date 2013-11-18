#include "PurchaseData.h"
#include "TimeZone.h"

std::ostream & operator<<(std::ostream& ostrm, const PurchaseData& data)
{
	ostrm << std::endl;
	ostrm << "\t!!!!! Start PURCHASE DATA !!!!!" << std::endl;
    ostrm << "\tSymbol: " << data.symbol_ << std::endl;
    ostrm << "\tSize: " << data.size_<< std::endl;
	ostrm << "\tShares Filled: " << data.sharesFilled_<< std::endl;
    ostrm << "\tPrice: " << data.price_<< std::endl;
	ostrm << "\tStop Price: " << data.stopPrice_<< std::endl;
	ostrm << "\tStop Lower Price: " << data.stopLowerPrice_<< std::endl;
	ostrm << "\tStop Upper Price: " << data.stopUpperPrice_<< std::endl;

    ostrm << "\tTime Placed: " << TimeZone::instance()->formatTZ(data.timePlaced_)<< std::endl;
	ostrm << "\tTime Filled: " << data.timeFilled_<< std::endl;
	ostrm << "\tDate: " << data.date_<< std::endl;

    ostrm << "\tOrder Number: " << data.orderNumber_<< std::endl;
    ostrm << "\tError Message: " << data.errorMessage_<< std::endl;
	ostrm << "\tAdditional Reason: " << data.reason_<< std::endl;

	ostrm << "\tStatus: ";
    switch (data.status_)
	{
	case PurchaseData::None:
		ostrm << "None";
		break;
    case PurchaseData::SimulatedTrade:
		ostrm << "SimulatedTrade";
		break;
    case PurchaseData::Sent:
		ostrm << "Sent";
		break;
    case PurchaseData::Executed:
		ostrm << "Executed";
		break;
    case PurchaseData::Filled:
		ostrm << "Filled";
		break;
    case PurchaseData::PartialFill:
		ostrm << "PartialFill";
		break;
    case PurchaseData::Failed:
		ostrm << "Failed";
		break;
	case PurchaseData::Canceled:
		ostrm << "Canceled";
		break;
	}
	ostrm << std::endl;

    ostrm << "\tTrade Type: "; 
	switch (data.typeTrade_)
	{
	case PurchaseData::NoTrade:
		ostrm << "NoTrade";
		break;
	case PurchaseData::Buy:
		ostrm << "Buy";
		break;
	case PurchaseData::Sell:
		ostrm << "Sell";
		break;
	case PurchaseData::SellShort:
		ostrm << "SellShort";
		break;
	case PurchaseData::BuyToCover:
		ostrm << "BuyToCover";
		break;
	}

	ostrm << std::endl;

	ostrm << "\tExecution Type: ";
	switch (data.executionType_)
	{
	case PurchaseData::NotExecuted:
		ostrm << "NotExecuted";
		break;
	case PurchaseData::MARKET:
		ostrm << "Market";
		break;
	case PurchaseData::LIMIT:
		ostrm << "Limit";
		break;
	case PurchaseData::STOP_MARKET:
		ostrm << "StopLoss";
		break;
	case PurchaseData::STOP_LIMIT:
		ostrm << "StopLimit";
		break;
	case PurchaseData::MARKET_TTO:
		ostrm << "Market_TTO";
		break;

	}
	ostrm << "\n\t!!!!! END PURCHASE DATA !!!!!" << std::endl;
	ostrm << std::endl;
	return ostrm;
}
