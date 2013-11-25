#ifndef HistoryObserver_h
#define HistoryObserver_h

struct HistQuery;

class HistoryObserver
{
public:
	virtual void update(HistQuery * data) = 0;
};

#endif
