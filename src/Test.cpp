/*
 * Test.cpp
 *
 *  Created on: 25 maj 2015
 *      Author: Przemyslaw Jablonski
 */

#include "Test.h"

#include <iostream>
#include <vector>

#include "../optimizationFeatures/NMOptimizer.h"

Test::Test(nrs::geometry::nmoptimizer::Optimizer &opt,
		nrs::geometry::nmoptimizer::NMOptimizerObject &obj) {
	this->opt = &opt;
	this->obj = &obj;
	bestValue = 0;
}

void Test::doTest() {
	opt->optimize(*obj, startPar, bestPar, bestValue);

}
double Test::getBestValue() {
	return bestValue;
}
void Test::displayInfo() {
	std::vector<double> param;
	std::vector<double> best;

	startPar.getVect(param);
	std::cout << "startParam ";
	for (unsigned int i = 0; i < param.size(); ++i) {
		std::cout << param[i] << " , ";
	}
	std::cout << "startValue -> " << obj->value(startPar);

	bestPar.getVect(best);
	std::cout << " :: bestParam ";
	for (unsigned int i = 0; i < best.size(); ++i) {
		std::cout << best[i] << " , ";
	}
	std::cout << " bestValue -> " << bestValue << " <- " << std::endl;

}

void Test::run(){
	Test::doTest();
	Test::displayInfo();
}
