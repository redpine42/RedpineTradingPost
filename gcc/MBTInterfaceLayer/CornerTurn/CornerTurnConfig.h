#ifndef CornerTurnConfig_h
#define CornerTurnConfig_h

#ifndef string_h
#include <string>
#define string_h
#endif

class CornerTurnConfig
{
public:
	static CornerTurnConfig * instance();
	std::string getURI(){return brokerURI_;}
	std::string getLogPath(){return logPath_;}
private:
	static CornerTurnConfig * instance_;
	CornerTurnConfig();

	std::string brokerURI_;
	std::string logPath_;
};

#endif