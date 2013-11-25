//
//   Copyright (c) 2008 by Shalom Yariv
//
// HistSink.cpp : implementation file
//
#include <iostream>
#include <stdafx.h>
#include <iomanip>
#include "CHistSink.h"
#include "CandleManager.h"
#include "CandleData.h"
#include "TimeZone.h"

extern IMbtHistMinBarPtr g_mb;

// HistSink

IMPLEMENT_DYNAMIC(CHistSink, CCmdTarget)

 
CHistSink::CHistSink()
{
	EnableAutomation();
	::InitializeCriticalSection(&m_criticalSection);
}

CHistSink::~CHistSink()
{
}


void CHistSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CHistSink, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CHistSink, CCmdTarget)
	DISP_FUNCTION_ID(CHistSink, "OnDataEvent", 1, OnDataEvent, VT_EMPTY, VTS_I4 VTS_DISPATCH VTS_I4)
	DISP_FUNCTION_ID(CHistSink, "OnError"    , 2, OnError    , VT_EMPTY, VTS_I4 VTS_DISPATCH VTS_I4)
END_DISPATCH_MAP()

// Note: we add support for IID_IHistSink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {6F364FF3-2831-4E52-B045-287F6F284A68}
static const IID IID_IHistSink =
{ 0x6F364FF3, 0x2831, 0x4E52, { 0xB0, 0x45, 0x28, 0x7F, 0x6F, 0x28, 0x4A, 0x68 } };

BEGIN_INTERFACE_MAP(CHistSink, CCmdTarget)
	INTERFACE_PART(CHistSink, __uuidof(_IMbtHistEvents), Dispatch)
END_INTERFACE_MAP()



// Here we identify the originating object type interface and route the call accordingly
void CHistSink::OnDataEvent(long lRequestId,
		IDispatch * pHist,
		enum enumHistEventType evt )
{

	IMbtHistTickPtr t;
	IMbtHistMinBarPtr p;// = g_mb;
	IMbtHistDayBarPtr d;// = g_mb;
	HRESULT hMinBar = pHist->QueryInterface(__uuidof(IMbtHistMinBar), (void**) &p);
	HRESULT hTick   = pHist->QueryInterface(__uuidof(IMbtHistTick), (void**) &t);
	HRESULT hDayBar = pHist->QueryInterface(__uuidof(IMbtHistDayBar), (void**) &d);


	EnterCriticalSection(&this->m_criticalSection);

	if (S_OK == hDayBar)
		this->_OnDayBar(lRequestId, pHist, evt);
	if (S_OK == hMinBar)
		this->_OnMinBar(lRequestId, pHist, evt);
	if (S_OK == hTick)
		this->_OnTick(lRequestId, pHist, evt);

	LeaveCriticalSection(&this->m_criticalSection);

}


void CHistSink::_OnMinBar(long lRequestId, IDispatch * pHist, enumHistEventType evt )
{
	IMbtHistMinBarPtr p;// = g_mb;
	HRESULT hMinBar = pHist->QueryInterface(__uuidof(IMbtHistMinBar), (void**) &p);

	HRESULT r;
	long cnt = 0;
	long idx = 0;
	DATE d1 = 0.0;

	r = p->get_Index(&idx);
	r = p->get_Count(&cnt);

//	std::cout << "Response for " << lRequestId << ". cnt=" << cnt << std::endl;
	if(cnt < 1)
	{
		return;
	}

	CandleData::CandleUpdateType candleUpdateType = CandleData::RETRIEVAL;
	switch (evt)
	{
	case hetInitial:
	{
		candleUpdateType = CandleData::INITIAL;
		break;
	}
	case hetNew:
	{
		candleUpdateType = CandleData::NEW;
		cnt = 1;
		break;
	}
	case hetUpdate:
	{
		candleUpdateType = CandleData::UPDATE;
		cnt = 1;
		break;
	}
	}
	
	for(int i = 0; i < cnt; ++i) 
	{
		p->PutIndex(i);
		std::string symbolStr = (const char *)p->GetSymbol();
		d1 = p->GetUTCDateTime();

		CandleData data(symbolStr,
						p->GetTotalVolume(),
						p->GetOpen(),
						p->GetHigh(),
						p->GetLow(),
						p->GetClose(),
						TimeZone::instance()->getJDate(d1),
						TimeZone::instance()->getSecondsGMT(d1),
						CandleData::M1,
						candleUpdateType);
		r = p->get_Index(&idx);

		CandleManager::instance()->addCandle(data, lRequestId);
	}
	CandleManager::instance()->finishHist(lRequestId, d1, cnt);
}

void CHistSink::_OnDayBar(		long lRequestId,		IDispatch * pHist, enumHistEventType evt )
{
/*	IMbtHistDayBarPtr p;// = g_mb;
	HRESULT hMinBar = pHist->QueryInterface(__uuidof(IMbtHistDayBar), (void**) &p);

	HRESULT r;
	long cnt=0, vol=0 ;
	long idx = 0;
	r = p->get_Index(&idx);
	r = p->get_Count(&cnt);

	char ln[128];
	std::cout << "Response for " << lRequestId << ". cnt=" << cnt << std::endl;

	if (this->m_RecsSoFar == 0 || evt == hetInitial)
    	r = p->First();

	double hig = 0.0, low = 0.0, opn = 0.0, cls = 0.0;
	DATE d1;

	TIME_ZONE_INFORMATION tz;
	::GetTimeZoneInformation(&tz);
	long bias = tz.Bias;
	long biasFromEST = 5 - (bias/60);

	double _bias = ((double) biasFromEST) / 24.0;
	r = p->get_Count(&cnt);
	while (!p->Eof) {
	//	r = p->get_Count(&cnt);
		r = p->get_TotalVolume(&vol);
		r = p->get_High(&hig);
		r = p->get_Low(&low);
		r = p->get_Open(&opn);
		r = p->get_Close(&cls);
		r = p->get_CloseDate(&d1);
		r = p->get_Index(&idx);

		SYSTEMTIME st;
		::VariantTimeToSystemTime(d1+0.5, &st);
		sprintf_s(ln, "%04d%02d%02d, %02d%02d,%.2f,%.2f,%.2f,%.2f,%d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, opn, hig, low,cls, vol);
		std::cout << ln;
		RecordSetRecord _r(d1+0.5, vol, opn, cls, hig, low);
		_r.s_recordType = 3;
		this->m_recset->AddRecord(_r);

		r = p->Next();
		
		this->m_RecsSoFar++;
	}

	if (idx < cnt) { // MISTERY: Eof is true one record before the last
		r = p->get_TotalVolume(&vol);
		r = p->get_High(&hig);
		r = p->get_Low(&low);
		r = p->get_Open(&opn);
		r = p->get_Close(&cls);
		r = p->get_CloseDate(&d1);
		r = p->get_Index(&idx);

		SYSTEMTIME st;
		::VariantTimeToSystemTime(d1+0.5, &st);
		sprintf_s(ln, "%04d%02d%02d, %02d%02d,%.2f,%.2f,%.2f,%.2f,%d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, opn, hig, low,cls, vol);
		std::cout << ln;
		RecordSetRecord _r(d1+0.5, vol, opn, cls, hig, low);
		_r.s_recordType = 3;
		this->m_recset->AddRecord(_r);


	}

	m_recset->NotifyResponse(lRequestId);

*/
}

void CHistSink::_OnTick  (		long lRequestId,		IDispatch * pHist, enumHistEventType evt )
{
/*	IMbtHistTickPtr t;
	HRESULT hTick   = pHist->QueryInterface(__uuidof(IMbtHistTick), (void**) &t);

//	enumTickType tickType;
	long tickType;
	long tickStatus;
	HRESULT r;
	long cnt=0, vol=0 ;
	long idx = 0;
	r = t->get_Index(&idx);
	r = t->get_Count(&cnt);

	std::cout << "Response for " << lRequestId << ". cnt=" << cnt << std::endl;

	if (this->m_RecsSoFar == 0 || evt == hetInitial)
    	r = t->First();
	r = t->get_Index(&idx);

	long tickCondition;
	double hig = 0.0, low = 0.0, opn = 0.0, price = 0.0;
	DATE d0;
	DATE d1;
	// last record
	r = t->get_UTCDateTime(&d1);

	TIME_ZONE_INFORMATION tz;
	::GetTimeZoneInformation(&tz);
	long bias = tz.Bias;
	long biasFromEST = 5 - (bias/60);

	this->m_recsCount = 0;
	t->Index = 0;

	double _bias = ((double) biasFromEST) / 24.0;
	r = t->get_Count(&cnt);
	while (!t->Eof) {
		// first record
		r = t->get_UTCDateTime(&d0);
		r = t->get_Index(&idx);
		r = t->get_Price(&price);
		r = t->get_Volume(&vol);
		t->get_TickType(&tickType);
		t->get_TickStatus(&tickStatus);
		t->get_TickCondition(&tickCondition);

		RecordSetRecord _r(d0, vol, tickType, tickStatus, tickCondition, price);
		this->m_recset->AddRecord(_r);


    	r = t->Next();
		
		this->m_RecsSoFar++;
		++this->m_recsCount;
	}
	if (idx < cnt) { // MISTERY: Eof is true one record before the last.....
		r = t->get_UTCDateTime(&d0);
		r = t->get_Index(&idx);
		r = t->get_Price(&price);
		r = t->get_Volume(&vol);
		t->get_TickType(&tickType);
		t->get_TickStatus(&tickStatus);
		t->get_TickCondition(&tickCondition);
		RecordSetRecord _r(d0, vol, tickType, tickStatus, tickCondition, price);
		this->m_recset->AddRecord(_r);
		this->m_RecsSoFar++;
		++this->m_recsCount;


	}

	r = t->get_Index(&idx);
	if (d0 < this->m_startTime)
		m_startTime = d0;
	if (d1 > this->m_endTime)
		m_endTime = d1;


	// if the last record is the start time:
	// if (m_RecsSoFar == this->m_recsCount)
    	m_recset->NotifyResponse(lRequestId);
*/
}



void CHistSink::OnError( long requestId,
		IDispatch * pHist,
		enum enumHistErrorType err )
{

	std::string msg;
	switch(err)
	{
	case errNoError:
		msg = "errNoError";
		break;
	case errClientSideConnect:
		msg = "errClientSideConnect";
		break;
	case errClientSideTimeout:
		msg = "errClientSideTimeout";
		break;
	case errClientSideSend:
		msg = "errClientSideSend";
		break;
	case errClientSideRecv:
		msg = "errClientSideRecv";
		break;
	case errClientSideMemoryAlloc:
		msg = "errClientSideMemoryAlloc"; break;
	case errClientSideDecompress:
		msg = "errClientSideDecompress";
		break;
	case errClientSideParsing:
		msg = "errClientSideParsing";
		break;
	case errServerSideMaintInProgress:
		msg = "errServerSideMaintInProgress"; break;
	case errServerSideInvalidRequest:
		msg = "errServerSideInvalidRequest"; break;
	case errServerSideDataLoad:
		msg = "errServerSideDataLoad";
		break;
	case errServerSideMemoryAlloc:
		msg = "errServerSideMemoryAlloc";
		break;
	case errServerSideNoRequestData:
		msg = "errServerSideNoRequestData";
		break;
//	case errServerSideCompress:
//		msg = "errServerSideCompress";
//		break;
//	case errServerSideFormatting:
//		msg = "errServerSideFormatting"; break;
//	case errServerSideInvalidUserOrPwd:
//		msg = "errServerSideInvalidUserOrPwd"; break;
	case errServerSideLockedOut:
		msg = "errServerSideLockedOut"; break;
	case errServerSideInternalDatabaseError: 
		msg = "errServerSideInternalDatabaseError"; break;
	case errServerSideNotEntitled :
		msg = "errServerSideNotEntitled"; break;
	default:
		msg = "Unkown Error";
		break;
	};
//	CandleStickManager::instance()->historyError(requestId,msg);
}

