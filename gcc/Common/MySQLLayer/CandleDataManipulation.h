#ifndef CandleDataManipulation_h
#define CandleDataManipulation_h

#ifndef fstream_h
#include <fstream>
#define fstream_h
#endif

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef vector_h
#include <vector>
#define vector_h
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

#ifndef CandleData_h
#include "CandleData.h"
#endif

#ifndef DateTimeRange_h
#include "DateTimeRange.h"
#endif

class CandleDataManipulation
{
public:
	static CandleDataManipulation * instance();

	unsigned long getDateRange(std::string & symbol, CandleData::CandleTimeType timeType, DateTimeRange & dateData);
	void getCandleData(std::string & symbol, CandleData::CandleTimeType timeType, std::vector<CandleData*> & data, DateTimeRange & dateData);
	void getCandleData(std::string & symbol, CandleData::CandleTimeType timeType, std::vector<CandleData*> & data);
	void saveCandleData(const CandleData* data);

	void populateTables(std::vector<std::string> & fileNames);
	void bulkDataFlush();

	void bulkSave(const CandleData* data);
	~CandleDataManipulation();
private:
	static CandleDataManipulation * instance_;
	CandleDataManipulation();

	bool getFileRow(std::ifstream & istrm, CandleData *& data,int adj, std::string & symbol, CandleData::CandleTimeType candleType);
	bool bulkInsertCandleData(std::vector<CandleData*> & dataVec, std::string & tableName);

	typedef std::map<std::string, const CandleData*, std::less<std::string> > UpdateMap;
	typedef UpdateMap::iterator UpdateMapIter;

	UpdateMap updateMap_;
};

#endif
