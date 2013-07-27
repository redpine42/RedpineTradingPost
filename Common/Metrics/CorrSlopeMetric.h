#pragma warning(disable:4786) 
#ifndef CorrSlopeMetric_h
#define CorrSlopeMetric_h

#ifndef string_h
#include <string>
#define string_h
#endif

struct CorrSlope
{
	double corr_;
	double stddev_;
	double slope_;
};

CorrSlope getCorrSlope(const std::string & symbol1, const std::string & symbol2, const int unsigned slopeBars, const int unsigned corrSize);

CorrSlope * getAllCorrSlope(const std::string & symbol1, const std::string & symbol2, const int unsigned slopeBars, const int unsigned corrSize);

#endif

