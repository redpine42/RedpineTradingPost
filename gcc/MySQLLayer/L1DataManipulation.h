#ifndef L1DataManipulation_h
#define L1DataManipulation_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#ifndef queue_h
#include <queue>
#define queue_h
#endif

struct L1Data;

#ifndef DateTimeRange_h
#include "DateTimeRange.h"
#endif

class L1DataManipulation
{
public:
	static L1DataManipulation * instance();

	void getL1Data(std::string & symbol, std::vector<L1Data*> & data, DateTimeRange & dateData);
	void getL1Data(std::string & symbol, std::vector<L1Data*> & data);
	void saveL1Data(const L1Data* data);

	void bulkSave(const L1Data* data);
	void bulkDataFlush();

	~L1DataManipulation();

	class L1Iter
	{
	public:
		L1Iter(std::string & symbol, unsigned int startSeq);
		L1Data * getNext();
		void getNextData(unsigned int size, std::vector<L1Data*>& data);
	private:
		unsigned long long lastSeq_;
		const unsigned int cacheSize_;
		std::queue<L1Data*> cachedData_;
		const std::string symbol_;
	};

private:
	static L1DataManipulation * instance_;
	L1DataManipulation();

	typedef std::vector<const L1Data*> L1DataVec;
	typedef L1DataVec::iterator L1DataVecIter;

	L1DataVec l1DataVec_;

	unsigned long long getL1Data(const std::string & symbol, std::queue<L1Data*> & data, unsigned long long seq, unsigned int size);
};

#endif
