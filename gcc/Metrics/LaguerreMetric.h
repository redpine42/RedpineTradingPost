#ifndef Laguerre_h
#define Laguerre_h

struct CandleData;

double getLaguerre(const double gamma, int unsigned & size, CandleData * data, long numSticks);

double * getAllLaguerre(const double gamma, int unsigned & size, CandleData * data, long numSticks);

#endif

