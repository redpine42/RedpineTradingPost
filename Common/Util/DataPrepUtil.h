#pragma once

#ifndef string_h
#include <string>
#define string_h
#endif

#ifndef NormData_h
#include "NormData.h"
#endif

class DataPrepUtil
{
public:
	static DataPrepUtil * instance();
	static void removeInstance();

	void normalizeData(double *data, unsigned long length, std::string id);
	void denormalizeData(double data, std::string & id);
	void fannNormalize(double * data, unsigned long dataSize, double maxVal, double minVal);
private:
	static DataPrepUtil * instance_;

	DataPrepUtil(void);
	virtual ~DataPrepUtil(void);

	double SoftMaxUnScale(double SquashedVal,
						  double Mean,
						  double StdDev,
						  double ConfNZ);
	double SoftMaxScale(double Val,
		                double Mean,
						double StdDev,
						double ConfNZ);

	double NZ(double YPR);
	double StdDev(double pN,     // Number
				  double pSx,    // Sum
				  double pSxSq); // Sum of Squares

	NormMap normMap_;
};
