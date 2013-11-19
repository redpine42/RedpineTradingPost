#pragma warning(disable:4786) 

#ifndef BBandsHA_h
#define BBandsHA_h

#ifndef string_h
#include <string>
#define string_h
#endif

void getBBandsHA(const std::string & symbol, 
				   const int unsigned size, 
				   const double stdHigh, 
				   const double stdLow,
				   double & high,
				   double & low,
				   double & medium);

void getAllBBandsHA(const std::string & symbol, 
						const int unsigned size, 
						const double stdHigh, 
						const double stdLow,
						double *& high,
						double *& low,
						double *& medium);

#endif