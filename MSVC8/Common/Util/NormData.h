#ifndef NormData_h
#define NormData_h

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef map_h
#include <map>
#define map_h
#endif

struct NormData
{
	double mean_;
	double stdDev_;
	double confNZ_;
	NormData(double mean, double stdDev, double confNZ)
		: mean_(mean), stdDev_(stdDev), confNZ_(confNZ){};
	NormData()
		: mean_(0.0), stdDev_(0.0), confNZ_(0.0){};
};

typedef std::map<std::string, NormData, std::less<std::string> > NormMap;
typedef NormMap::iterator NormMapIter;

#endif

