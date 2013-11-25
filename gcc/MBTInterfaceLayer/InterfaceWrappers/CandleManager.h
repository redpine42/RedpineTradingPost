#ifndef CandleManager_h
#define CandleManager_h

class HistoryObserver;

#ifndef stdafx_h
#include "stdafx.h"
#define stdafx_h
#endif

class CHistSink;
struct HistQuery;

#ifndef CandleData_h
#include "CandleData.h"
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif


class CandleManager
{
public:
	static CandleManager * createInstance(IMbtComMgrPtr pComMgr);
	static CandleManager * instance();

	void getCandleData(std::vector<std::string> & symbols);
	unsigned long getHist(HistQuery * request);
	void finishHist(unsigned long requestId, DATE lastDate, int numCandles);

	void addCandle(CandleData & data, long requestId);


private:
	static CandleManager * instance_;
	CandleManager(IMbtComMgrPtr pComMgr);

	CHistSink* histSink_;
	IMbtHistMgrPtr histMgr_;

	typedef std::map<int, HistQuery*> HistMap;
	typedef HistMap::iterator HistIter;

	HistMap histMap_;

	unsigned long histCnt_;

	void add(std::string & symbol, long time);
	void add(std::vector<std::string> & symbols, long time);
};

#endif
