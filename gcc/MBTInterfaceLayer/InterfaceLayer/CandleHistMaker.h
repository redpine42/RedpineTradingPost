#ifndef CandleHistMaker_h
#define CandleHistMaker_h

#ifndef HistoryObserver_h
#include "HistoryObserver.h"
#endif

#ifndef HistoryQuery_h
#include "HistQuery.h"
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

class CandleHistMaker : public HistoryObserver
{
public:
	static CandleHistMaker * instance();

	void getCandleHistory(std::vector<std::string> & symbols);
	void update(HistQuery * data);
private:
	static CandleHistMaker * instance_;
	CandleHistMaker();

};

#endif