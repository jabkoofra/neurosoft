/*
 * TestNMOptimizer.h
 *
 *  Created on: 25 maj 2015
 *      Author: Przemyslaw Jablonski
 */

#ifndef TESTNMOPTIMIZER_H_
#define TESTNMOPTIMIZER_H_

#include <Poco/SharedPtr.h>
#include <vector>

#include "../optimizationFeatures/NMOptimizer.h"


class Parameters: public nrs::geometry::nmoptimizer::NMOptimizerParams {
	std::vector<double> v;
public:
	void getVect(std::vector<double>& res);
	void setVect(const std::vector<double>& v);
	Poco::SharedPtr<nrs::geometry::nmoptimizer::NMOptimizerParams> copy() const;
};

class AcleyTestFunction: public nrs::geometry::nmoptimizer::NMOptimizerObject {
	double a, b, c;
public:
	AcleyTestFunction();
	AcleyTestFunction(double, double, double);
	double value(nrs::geometry::nmoptimizer::NMOptimizerParams& par);
};

class SphereTestFunction: public nrs::geometry::nmoptimizer::NMOptimizerObject {
public:
	double value(nrs::geometry::nmoptimizer::NMOptimizerParams& par);
};

class TridTestFunction: public nrs::geometry::nmoptimizer::NMOptimizerObject {
public:
	double value(nrs::geometry::nmoptimizer::NMOptimizerParams& par);
};

class RastriginTestFunction: public nrs::geometry::nmoptimizer::NMOptimizerObject {
public:
	double value(nrs::geometry::nmoptimizer::NMOptimizerParams& par);
};

#endif /* TESTNMOPTIMIZER_H_ */
