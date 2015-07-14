/*
 * Test.h
 *
 *  Created on: 25 maj 2015
 *      Author: Przemyslaw Jablonski
 */

#ifndef TEST_H_
#define TEST_H_

#include "../testOptimizationFeatures/TestNMOptimizer.h"
#include "Poco/Thread.h"

using namespace nrs::geometry::nmoptimizer;

class Test: public Poco::Runnable{
	Optimizer *opt;
	NMOptimizerObject *obj;
	double bestValue;

public:
	Parameters startPar;
	Parameters bestPar;

	Test(nrs::geometry::nmoptimizer::Optimizer &opt,
			nrs::geometry::nmoptimizer::NMOptimizerObject &obj);

	void doTest(void);
	double getBestValue(void);
	void displayInfo(void);

	virtual void run();
};

#endif /* TEST_H_ */
