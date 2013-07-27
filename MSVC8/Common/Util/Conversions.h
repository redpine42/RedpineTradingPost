#ifndef Conversions_h
#define Conversions_h

#ifndef string_h
#include <string>
#define string_h
#endif

class Conversions
{
public:

static std::string getStrFromInt(int val);
static std::string getStrFromUInt(int val);
static std::string getStrFromLong(long val);
static std::string getStrFromULong(unsigned long val);
static std::string getStrFromULongLong(unsigned long long val);
static std::string getStrFromDouble(double val);

};
#endif

