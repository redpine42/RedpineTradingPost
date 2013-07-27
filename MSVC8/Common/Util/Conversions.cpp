#include "Conversions.h"
#include <strstream>

std::string Conversions::getStrFromInt(int val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}
std::string Conversions::getStrFromUInt(int val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}

std::string Conversions::getStrFromLong(long val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}

std::string Conversions::getStrFromULong(unsigned long val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}

std::string Conversions::getStrFromULongLong(unsigned long long val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}

std::string Conversions::getStrFromDouble(double val)
{
	std::strstream strstr;
	strstr << val << std::ends;
	std::string str = strstr.str();
	strstr.clear();
	strstr.rdbuf()->freeze(0);

	return str;
}