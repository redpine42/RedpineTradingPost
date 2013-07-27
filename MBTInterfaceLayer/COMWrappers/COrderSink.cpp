/***********************************************************
 By using this material you agree to comply with the terms
 governing the MBTI systems and with the MBTI Site Terms and
 Conditions available for view at http://www.mbtrading.com/
 Copyright 2003 MB Trading, Inc. ALL RIGHTS RESERVED.
************************************************************/

// COrderSink.cpp : implementation file

#include "stdafx.h"
#include "COrderSink.h"
#include "QuotesManager.h"
#include "TimeZone.h"
#include "MsgProducer.h"
#include "AccountData.h"
#include "PositionData.h"
#include "OpenOrderData.h"
#include "OrderHistoryData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VALUE_BUY 10000
#define VALUE_SELL 10001
#define VALUE_SELLSHT 10002
#define VALUE_LIMIT 10030
#define VALUE_MARKET 10031
#define VALUE_DAY 10011
#define VALUE_NORMAL 10042
/////////////////////////////////////////////////////////////////////////////
// COrderSink

IMPLEMENT_DYNAMIC(COrderSink, CCmdTarget)

COrderSink::COrderSink()
{
	EnableAutomation();
	m_bLogonSucceeded = FALSE; // Distinguish old events (pre-OnLogonSucceeded) from new ones
}

COrderSink::~COrderSink()
{
}

void COrderSink::OnFinalRelease()
{
	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(COrderSink, CCmdTarget)
	//{{AFX_MSG_MAP(COrderSink)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(COrderSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(COrderSink)
	DISP_FUNCTION_ID(COrderSink, "OnConnect", 0x1, OnConnect, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(COrderSink, "OnClose", 0x2, OnClose, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(COrderSink, "OnLogonSucceed", 0x3, OnLogonSucceed, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(COrderSink, "OnSubmit", 0x4, OnSubmit, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnAcknowledge", 0x5, OnAcknowledge, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnExecute", 0x6, OnExecute, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnRemove", 0xa, OnRemove, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnHistoryAdded", 0xb, OnHistoryAdded, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnPositionAdded",0xc, OnPositionAdded, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnPositionUpdated", 0xd, OnPositionUpdated, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnBalanceUpdate", 0xe, OnBalanceUpdate, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnDefaultAccountChanged", 0x10, OnDefaultAccountChanged, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnAccountLoading", 0x11, OnAccountLoading, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnAccountLoaded", 0x12, OnAccountLoaded, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnCancelPlaced", 0x13, OnCancelPlaced, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnReplacePlaced", 0x14, OnReplacePlaced, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnReplaceRejected", 0x15, OnReplaceRejected, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnCancelRejected", 0x16, OnCancelRejected, VT_EMPTY, VTS_DISPATCH)
	DISP_FUNCTION_ID(COrderSink, "OnAccountUnavailable", 0x17, OnAccountUnavailable, VT_EMPTY, VTS_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/*
Originally used the Class Wizard to create the above entries. It created them, plus the
macros (event handlers). The CW created them as DISP_FUNCTION (not DISP_FUNCTION_ID) and
there was a problem with MFC not assigning the right DISPID to each event handler
(e.g. OnHistoryAdded was being called when OnPositionUpdated event fired). Therefore,
manually changed them all to DISP_FUNCTION_ID as you see above, which requires the DISPID
as the 3rd parameter. The DISPIDs entered above are also listed below; copy/pasted for
your convenience (and mine...), and can also be found in the typedefs for MbtOrders.DLL.

[id(0x00000001), helpstring("Occurs upon successful connection to order server.")]
void OnConnect([in] long lErrorCode);
[id(0x00000002), helpstring("Occurs when connection to order server has been severed.")]
void OnClose([in] long lErrorCode);
[id(0x00000003), helpstring("Occurs when user has been authenticated and has successfully logged in.")]
void OnLogonSucceed();
[id(0x00000004), helpstring("Occurs upon order submission.")]
void OnSubmit([in] IMbtOpenOrder* pOrd);
[id(0x00000005), helpstring("Occurs when a submitted order has been accepted by server.")]
void OnAcknowledge([in] IMbtOpenOrder* pOrd);
[id(0x00000006), helpstring("Occurs in response to an execution against a pending order.")]
void OnExecute([in] IMbtOpenOrder* pOrd);
[id(0x00000009), helpstring("Occurs when an order submission has failed.")]
void OnReject([in] IMbtOpenOrder* pOrd);
[id(0x0000000a), helpstring("Occurs when an order is no longer pending and should be removed from user interface.")]
void OnRemove([in] IMbtOpenOrder* pOrd);
[id(0x0000000b), helpstring("Occurs when a new order event has been added to the history log.")]
void OnHistoryAdded([in] IMbtOrderHistory* pHist);
[id(0x0000000c), helpstring("Occurs when a new position has been added.")]
void OnPositionAdded([in] IMbtPosition* pPos);
[id(0x0000000d), helpstring("Occurs when there has been a change to a position.")]
void OnPositionUpdated([in] IMbtPosition* pPos);
[id(0x0000000e), helpstring("Occurs when account totals have changed.")]
void OnBalanceUpdate([in] IMbtAccount* pAcct);
[id(0x0000000f), helpstring("When SyncAccounts preference is True, occurs to request all controls to reset their account to match.")]
void OnSyncAccounts([in] IMbtAccount* pAcct);
[id(0x00000010), helpstring("Occurs when the MbtAccounts.DefaultAccount property has changed.")]
void OnDefaultAccountChanged([in] IMbtAccount* pAcct);
*/

//static const IID IID_ICOrderSink =
//{ 0x5a33b0a2, 0xd431, 0x484d, { 0x83, 0xd9, 0xf0, 0x8d, 0xd6, 0xd8, 0x10, 0x92 } };

BEGIN_INTERFACE_MAP(COrderSink, CCmdTarget)
//	INTERFACE_PART(COrderSink, IID_ICOrderSink, Dispatch) nope
//	INTERFACE_PART(COrderSink, DIID__IMbtOrderClientEvents, Dispatch) nope
// below, the __uuidof should use the dispinterface found in the .tlh file
	INTERFACE_PART(COrderSink, __uuidof(_IMbtOrderClientEvents), Dispatch)
END_INTERFACE_MAP()

/***************************************************************************
These five macros satisfy the event handlers (relocated to the .h file which
were originally put HERE by the Class Wizard). OnLogonSucceeded is handled in
the .h file, but the rest--pAct, pOrd, pPos, pHist, and lErrorCode--all call
one of these. OnClose only fires on loss of connection; not on shutdown.
***************************************************************************/

/* Process IMbtAccount events **********************************************
***************************************************************************/
void COrderSink::Log_pAcct(LPCTSTR sEventName, IMbtAccount* pAcct)
{
    DWORD dwWaitResult; 
	dwWaitResult = WaitForSingleObject(QuotesManager::hMutex,  // handle of mutex
                                       5000L);                 // five-second time-out interval

	AccountData accountData;

	accountData.eventType_ = sEventName;
	accountData.account_ = (LPCTSTR)pAcct->Account;
	accountData.accountType_ = pAcct->AcctType;
	accountData.bank_ = (LPCTSTR)pAcct->Bank;
	accountData.baseCurrency_= (LPCTSTR)pAcct->BaseCurrency;
	accountData.branch_ = (LPCTSTR)pAcct->Branch;
	accountData.cancelsToday_ = pAcct->CancelsToday[-1];
	accountData.credit_ = pAcct->Credit;
	accountData.currentEquity_ = pAcct->CurrentEquity;
	accountData.currentExcess_ = pAcct->CurrentExcess;
	accountData.customer_ = (LPCTSTR)pAcct->Customer;
	accountData.dailyRealizedPL_ = pAcct->DailyRealizedPL;
	accountData.MMRMultiplier_ = pAcct->MMRMultiplier;
	accountData.MMRUsed_ = pAcct->MMRUsed;
	accountData.morningCash_ = pAcct->MorningCash;
	accountData.morningEquity_ = pAcct->MorningEquity;
	accountData.morningExcess_ = pAcct->MorningExcess;
	accountData.overnightExcess_ = pAcct->OvernightExcess;
	if(0 == pAcct->PermedForCADEquities)
	{
		accountData.permedForCADEquities_ = false;
	}
	else
	{
		accountData.permedForCADEquities_ = true;
	}

	if(0 == pAcct->PermedForEquities)
	{
		accountData.permedForEquities_ = false;
	}
	else
	{
		accountData.permedForEquities_ = true;
	}

	if(0 == pAcct->PermedForForex)
	{
		accountData.permedForForex_ = false;
	}
	else
	{
		accountData.permedForForex_ = true;
	}

	if(0 == pAcct->PermedForFutures)
	{
		accountData.permedForFutures_ = false;
	}
	else
	{
		accountData.permedForFutures_ = true;
	}

	if(0 == pAcct->PermedForOptions)
	{
		accountData.permedForOptions_ = false;
	}
	else
	{
		accountData.permedForOptions_ = true;
	}
	accountData.routingId_ = (LPCTSTR)pAcct->RoutingID;
	accountData.semiDelimited_ = (LPCTSTR)pAcct->SemiDelimited;
	accountData.sharesToday_ = pAcct->SharesToday[-1];
	accountData.state_ = (AccountData::AccountState)pAcct->State;
	accountData.tradesToday_ = pAcct->TradesToday[-1];


	MsgProducer::instance()->sendAccountUpdateMessage(accountData);

	std::string msg =  accountData.getLogString();
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::ORDERSINK, msg);

	ReleaseMutex(QuotesManager::hMutex);
}

/* Process IMbtOpenOrder events ********************************************
***************************************************************************/
void COrderSink::Log_pOrd(LPCTSTR sEventName, IMbtOpenOrder* pOrd)
{
	OpenOrderData data;

	IMbtAccountPtr pAcct = pOrd->Account;
	data.account_ = (LPCTSTR)pAcct->Account;
	data.customer_ = (LPCTSTR)pAcct->Customer;
	if(0 == pOrd->Acknowledged)
	{
		data.acknowledged_ = false;
	}
	else
	{
		data.acknowledged_ = true;
	}


	long lBuySell = pOrd->BuySell;
	switch(lBuySell) {
		case VALUE_BUY:        data.buySell_ = "BUY";     break;
		case VALUE_SELL:       data.buySell_ = "SELL";    break;
		case VALUE_SELLSHT:    data.buySell_ = "SHORT";   break;
		default:               data.buySell_ = "?!?";
	};

	data.currentEvent_ = (LPCTSTR)pOrd->CurrentEvent;
	data.date_ = (LPCTSTR)pOrd->Date;
	data.eventType_ = sEventName;
	data.orderNumber_ = (LPCTSTR)pOrd->OrderNumber;
	data.orderType_ = pOrd->OrderType;
	data.prefMMID_ = (LPCTSTR)pOrd->PrefMMID;
	data.price_ = pOrd->Price;
	data.quantity_ = pOrd->Quantity;
	if(0 == pOrd->Replaceable)
	{
		data.replaceable_ = false;
	}
	else
	{
		data.replaceable_ = true;
	}
	data.route_ = (LPCTSTR)pOrd->Route;
	data.sharesFilled_ = pOrd->SharesFilled;
	data.stopLimit_ = pOrd->StopPrice;
	data.symbol_ = (LPCTSTR)pOrd->Symbol;
	data.timeInForce_ = pOrd->TimeInForce;
	data.token_ = (LPCTSTR)pOrd->Token;
	data.traderId_ = (LPCTSTR)pOrd->TraderID;
	data.trailingOffset_ = pOrd->TrailingOffset;
	data.volumeType_ = pOrd->VolumeType;

	long nTime = TimeZone::instance()->getSecondsGMT(pOrd->GetUTCDateTime());
	data.time_ = TimeZone::instance()->formatTZ(nTime).c_str();

	MsgProducer::instance()->sendOpenOrderUpdateMessage(data);
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::ORDERSINK, data.getLogString());
}

/* Process IMbtPosition events *********************************************
***************************************************************************/
void COrderSink::Log_pPos(LPCTSTR sEventName, IMbtPosition* pPos)
{
	PositionData data;
	IMbtAccountPtr pAcct = pPos->Account;
	data.account_ = (LPCTSTR)pAcct->Account;
	data.aggregatePosition_ = pPos->AggregatePosition;
	data.closableShares_ = pPos->CloseableShares;
	data.commission_ = pPos->Commission;
	data.customer_ = (LPCTSTR)pAcct->Customer;
	data.eventType_ = sEventName;
	data.intradayPosition_ = pPos->IntradayPosition;
	data.intradayPrice_ = pPos->IntradayPrice;
	data.MMRPct_ = pPos->MMRPct;
	data.MMRUsed_ = pPos->MMRUsed;
	data.overnightPosition_ = pPos->OvernightPosition;
	data.overnightPrice_ = pPos->OvernightPrice;
	data.pendingBuyShares_ = pPos->PendingBuyShares;
	data.pendingSellShares_ = pPos->PendingSellShares;
	data.realizedPNL_ = pPos->RealizedPNL;
	data.symbol_ = (LPCTSTR)pPos->Symbol;

	MsgProducer::instance()->sendPositionUpdateMessage(data);

	std::string msg = data.getLogString();
	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::ORDERSINK, msg);
}

/* Process IMbtOrderHistory events *****************************************
***************************************************************************/
void COrderSink::Log_pHist(LPCTSTR sEventName, IMbtOrderHistory* pHist)
{
	IMbtAccountPtr pAcct = pHist->Account;

	OrderHistoryData data;
	data.eventType_ = sEventName;
	data.account_ = (LPCTSTR)pAcct->Account;
	data.customer_ = (LPCTSTR)pAcct->Customer;

	switch(pHist->BuySell) {
		case VALUE_BUY:        data.buySell_ = "BUY";     break;
		case VALUE_SELL:       data.buySell_ = "SELL";    break;
		case VALUE_SELLSHT:    data.buySell_ = "SHORT";   break;
		default:               data.buySell_ = "?!?";
	};
	data.capacity_ = pHist->Capacity;
	data.contractsAhead_ = pHist->ContractsAhead;
	data.date_ = (LPCTSTR)pHist->Date;
	data.discPrice_ = pHist->DiscPrice;
	data.displayQuantity_ = pHist->DisplayQuantity;
	data.event_ = (LPCTSTR)pHist->Event;
	data.execId_ = pHist->ExecId;
	data.message_ = (LPCTSTR)pHist->Message;
	data.orderNumber_ = (LPCTSTR)pHist->OrderNumber;
	data.orderType_ = pHist->OrderType;
	data.origTraderId_ = (LPCTSTR)pHist->OrigTraderID;
	data.prefMMID_ = (LPCTSTR)pHist->PrefMMID;
	data.price_ = pHist->Price;
	data.quantity_ = pHist->Quantity;
	data.remoteId_ = (LPCTSTR)pHist->RemoteID;
	data.route_ = (LPCTSTR)pHist->Route;
	data.sharesFilled_ = pHist->SharesFilled;
	data.stopLimit_ = pHist->StopPrice;
	data.symbol_ = (LPCTSTR)pHist->Symbol;

	long nTime = TimeZone::instance()->getSecondsGMT(pHist->GetUTCDateTime());
	data.time_ = TimeZone::instance()->formatTZ(nTime).c_str();;
	data.timeInForce_ = pHist->TimeInForce;
	data.token_ = (LPCTSTR)pHist->Token;
	data.traderId_ = (LPCTSTR)pHist->TraderID;
	data.volumeType_ = pHist->VolumeType;
	data.execType_ = pHist->GetOrderType();

	MsgProducer::instance()->sendOrderHistoryUpdateMessage(data);

	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::ORDERSINK, data.getLogString());
}


/* Process events with lErrorCode ******************************************
***************************************************************************/
void COrderSink::Log_ErrorCode(LPCTSTR sEventName, long lErrorCode)
{
	CString sOut;
	sOut.Format("----  %s ------- error code: %d --------------------\n", sEventName, lErrorCode);

	std::string msg = sOut;

	MsgProducer::instance()->sendTextMessage(CornerTurnConst::Debug, CornerTurnConst::ORDERSINK, msg);
}

