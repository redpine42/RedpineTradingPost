#ifndef DateTimeRange_h
#define DateTimeRange_h


struct DateTimeRange
{
	unsigned long startJDate_;
	unsigned long startTime_;
	unsigned long endJDate_;
	unsigned long endTime_;

	DateTimeRange()
		: startJDate_(0),
		  startTime_(0),
		  endJDate_(9999999),
		  endTime_(86400)
	{
	}
};

#endif
