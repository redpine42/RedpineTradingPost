#include "ConsitentMove.h"
#include "CandleStickManager.h"

bool movesUp(const std::string & symbol, const int num)
{
	bool upward = 0;
	if(CandleStickManager::instance()->enoughSticks(symbol, num + 1) && num > 1)
	{
		double * closeData = CandleStickManager::instance()->getData(symbol, CandleStick::CLOSE, num + 1);
		double previousPrice = closeData[0];

		for(int i = 1; i < num + 1; ++i)
		{
			if(closeData[i] > previousPrice)
			{
				++upward;
				previousPrice = closeData[i];
			}
			else
			{
				break;
			}
		}
	}
	return upward;
}


bool movesDown(const std::string & symbol, const int num)
{
	bool downward = 0;
	if(CandleStickManager::instance()->enoughSticks(symbol, num + 1) && num > 1)
	{
		double * closeData = CandleStickManager::instance()->getData(symbol, CandleStick::CLOSE, num + 1);
		double previousPrice = closeData[0];

		for(int i = 1; i < num + 1; ++i)
		{
			if(closeData[i] < previousPrice)
			{
				++downward;
				previousPrice = closeData[i];
			}
			else
			{
				break;
			}
		}
	}
	return downward;
}

