#ifndef SymbolHelper_h
#define SymbolHelper_h

#ifndef string_h
#define string_h
#include <string>
#endif

static std::string parseSymbolName(std::string & fileName)
{
	return fileName.substr(0,6);
}

static std::string parseTimeFrame(std::string &fileName)
{
	size_t pos = fileName.find(".csv");
	return fileName.substr(6, pos - 6);
}

static std::string symbolToTableSymbol(std::string & symbol)
{
	std::string ret = symbol;
	size_t pos = ret.find('/');
	if(pos >= 0)
	{
		ret.erase(pos, 1);
	}
	return ret;
}
#endif
