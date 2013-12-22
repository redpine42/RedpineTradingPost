#ifndef MACDMetric_h
#define MACDMetric_h

class CandleStick;
class StockWatch;

struct CandleData;

double getMACDHist(const int unsigned fast, const int unsigned slow, const int unsigned period, CandleData * data, long numSticks);
double * getAllMACDHist(const int unsigned fast, const int unsigned slow, const int unsigned period, CandleData * data, long numSticks);

bool MACD3DropExit(CandleData * data, long numSticks);
bool MACD3RiseExit(CandleData * data, long numSticks);

#endif

