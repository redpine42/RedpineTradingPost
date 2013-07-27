#pragma warning(disable:4786) 

#ifndef HAMaxMin_h
#define HAMaxMin_h

#ifndef string_h
#include <string>
#define string_h
#endif

double getMaxHA(const std::string & symbol, const int unsigned size);
double getMinHA(const std::string & symbol, const int unsigned size);

double * getAllMaxHA(const std::string & symbol, const int unsigned size);
double * getAllMinHA(const std::string & symbol, const int unsigned size);

#endif