#include "TrendDesc.h"
#include "CandleData.h"
#include <string.h>

TrendDesc * getTrendDescriptions(long numSticks, unsigned int lookBack, CandleData * data)
{
	TrendDesc* desc = new TrendDesc[numSticks];
	bool lastHH = true;

	double * highData = CandleData::getData(data, CandleData::HIGH, numSticks);
	double * lowData = CandleData::getData(data, CandleData::LOW, numSticks);

	double currentHH = highData[0];
	double currentLL = lowData[0];
	double currentHL = highData[0];
	double currentLH = lowData[0];

	for(int i = 0; i < numSticks; ++i)
	{
		if(highData[i] > currentHH)
		{
			currentHH = highData[i];
			lastHH = true;
		}
		if(lowData[i] < currentLL)
		{
			currentLL = lowData[i];
			lastHH = false;
		}

		desc = new TrendDesc();
		desc[i].currentHH_ = currentHH;
		desc[i].currentHL_ = currentHL;
		desc[i].currentLH_ = currentLH;
		desc[i].currentLL_ = currentLL;

		desc[i].currentState_ = Unknown;
	}

	return desc;
}
