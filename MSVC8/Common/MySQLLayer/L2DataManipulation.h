#ifndef L2DataManipulation_h
#define L2DataManipulation_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

struct L2Data;
#ifndef DateTimeRange_h
#include "DateTimeRange.h"
#endif

class L2DataManipulation
{
public:
	static L2DataManipulation * instance();

	void getL2Data(std::string & symbol, std::vector<L2Data*> & data, DateTimeRange & dateData);
	void getL2Data(std::string & symbol, std::vector<L2Data*> & data);
	void saveL2Data(const L2Data* data);

	void bulkSave(const L2Data* data);
	void bulkDataFlush();

	~L2DataManipulation();
private:
	static L2DataManipulation * instance_;
	L2DataManipulation();

	typedef std::vector<const L2Data*> L2DataVec;
	typedef L2DataVec::iterator L2DataVecIter;

	L2DataVec l2DataVec_;
};

#endif
