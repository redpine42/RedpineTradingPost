#ifndef Hilbert_h
#define Hilbert_h

struct CandleData;

enum Phase
{
	PhaseOne,
	PhaseTwo,
	PhaseThree,
	PhaseFour,
};
Phase getPhaseEnum(double val);

int isTrendMode(CandleData * data, long numSticks);
int * isTrendModeAll(CandleData * data, long numSticks);

double getPeriod(CandleData * data, long numSticks);
double * getPeriodAll(CandleData * data, long numSticks);

void getPhasor(double outInPhase, double outQuadrature, CandleData * data, long numSticks);
void getPhasorAll(double *& outInPhase, double *& outQuadrature, CandleData * data, long numSticks);

void getSine(double outSine, double outLeadSine, CandleData * data, long numSticks);
void getSineAll(double *& outSine, double *& outLeadSine, CandleData * data, long numSticks);

double getTrend(CandleData * data, long numSticks);
double * getTrendAll(CandleData * data, long numSticks);

double getPhase(CandleData * data, long numSticks);
double * getPhaseAll(CandleData * data, long numSticks);
Phase getPhaseEnum(CandleData * data, long numSticks);

#endif
