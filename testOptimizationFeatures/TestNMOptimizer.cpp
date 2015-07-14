/*
 * TestNMOptimizer.cpp
 *
 *  Created on: 25 maj 2015
 *      Author: Przemyslaw Jablonski
 */

#include "TestNMOptimizer.h"

#include <cmath>

void Parameters::setVect(const std::vector<double> &v) {
	this->v = v;
}
void Parameters::getVect(std::vector<double> &v) {
	v = this->v;
}
Poco::SharedPtr<nrs::geometry::nmoptimizer::NMOptimizerParams> Parameters::copy() const {
	nrs::geometry::nmoptimizer::NMOptimizerParams *p;
	p = new Parameters();
	p->setVect(v);
	return p;
}

AcleyTestFunction::AcleyTestFunction() {
	a = 20;
	b = 0.2;
	c = 2 * M_PI;
}
AcleyTestFunction::AcleyTestFunction(double a, double b, double c) :
		a(a), b(b), c(c) {
}
;

double AcleyTestFunction::value(
		nrs::geometry::nmoptimizer::NMOptimizerParams &par) {
	double sumX = 0;
	double sumCos = 0;
	std::vector<double> x;
	par.getVect(x);
	int dim = x.size();

	for (int i = 0; i < dim; ++i) {
		sumX += x[i] * x[i];
		sumCos += std::cos(c * x[i]);
	}

	return -a * exp(-b * sqrt(sumX / dim)) - exp(sumCos / dim) + exp(1) + a;
}

double SphereTestFunction::value(
		nrs::geometry::nmoptimizer::NMOptimizerParams &par) {
	std::vector<double> x;
	par.getVect(x);
	int dim = x.size();
	double result = 0;

	for (int i = 0; i < dim; ++i) {
		result += x[i] * x[i];
	}
	return result;
}

double TridTestFunction::value(
		nrs::geometry::nmoptimizer::NMOptimizerParams &par) {
	std::vector<double> x;
	par.getVect(x);
	int dim = x.size();
	double left = 0;
	double right = 0;

	for (int i = 0; i < dim; ++i) {
		left += (x[i] - 1) * (x[i] - 1);
		if (i == 0)
			right = 0;
		right += x[i] * x[i - 1];
	}
	return left - right;
}

double RastriginTestFunction::value(
		nrs::geometry::nmoptimizer::NMOptimizerParams &par) {
	std::vector<double> x;
	par.getVect(x);
	unsigned int dim = x.size();
	double resultR = 0;
	for (unsigned int i = 0; i < dim; ++i) {
		resultR += x[i] * x[i] - 10 * cos(2 * M_PI * x[i]);
	}
	return 10 * dim + resultR;
}
