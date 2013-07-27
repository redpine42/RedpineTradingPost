#pragma warning(disable:4786)

#ifndef ConsistentMove_h
#define ConsistentMove_h

#ifndef string_h
#include <string>
#define string_h
#endif

bool movesUp(const std::string & symbol, const int unsigned num);
bool movesDown(const std::string & symbol, const int unsigned num);

#endif