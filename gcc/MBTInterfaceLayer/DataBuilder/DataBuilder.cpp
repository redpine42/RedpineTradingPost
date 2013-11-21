#include "MySQLLayer.h"
#include "CandleDataManipulation.h"

//#include "stdafx.h"
#include "MySQLLayer.h"
#include "Direct.h"
#include <string>
#include <vector>
#include <windows.h>

int main(int argc, const char* argv[])
{
	std::vector<std::string> fileNames;

	std::string directory("c:\\TradeLogs\\MinuteData");

	_chdir(directory.c_str());
	std::string buffer;

	WIN32_FIND_DATA myCSVFile;
	HANDLE myHandle=FindFirstFile("*.csv",&myCSVFile);

	if(myHandle!=INVALID_HANDLE_VALUE)
	{
		buffer = myCSVFile.cFileName;
		fileNames.push_back(buffer);

		while(true)
		{
			FindNextFile(myHandle,&myCSVFile);
            if(myCSVFile.cFileName!=buffer)
            {
				buffer=myCSVFile.cFileName;
				fileNames.push_back(buffer);
            }
            else
            {
				break;
            }
		}
	}

	std::string host = "Dan-PC";
	std::string user = "dan";
	std::string password = "lostcode";
	std::string database = "backtest";
	if(MySQLLayer::instance()->connectDB(host, user, password, database))
	{
		CandleDataManipulation::instance()->populateTables(fileNames);
		MySQLLayer::instance()->commit();
	}
	return 0;
}


