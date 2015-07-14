/**
 * @file NMOptimizer.h
 *
 * @date 2014-10-14 (mrv) module creation
 *
 * @author Paweł Mrówka
 * @author (C) Neurosoft Sp. z o.o. 1992-2014, Wrocław
 */

// $Id:$
#pragma once

#include <vector>
#include "Poco/SharedPtr.h"
#include "Poco/Random.h"

namespace nrs {
namespace geometry {
namespace nmoptimizer {

class NMOptimizerParams {
public:
	virtual ~NMOptimizerParams() {
	}
	virtual void getVect(std::vector<double>& res) = 0;
	virtual void setVect(const std::vector<double>& v) = 0;
	virtual Poco::SharedPtr<NMOptimizerParams> copy() const = 0;
};

class NMOptimizerObject {
public:
	virtual ~NMOptimizerObject() {
	}
	virtual double value(NMOptimizerParams& x) = 0;
};

struct OptimizerProgressCallback {
	virtual void onProgress(int iter, NMOptimizerParams& bestParams,
			double& bestValue) = 0;
};

class Optimizer {
public:
	virtual bool optimize(NMOptimizerObject& object,
			NMOptimizerParams& startParams, NMOptimizerParams& bestParams,
			double& bestValue) = 0;

	void setProgressCallback(
			Poco::SharedPtr<OptimizerProgressCallback> _callback) {
		callback = _callback;
	}

protected:
	Poco::SharedPtr<OptimizerProgressCallback> callback;
};

class NMOptimizer: public Optimizer {
	double alph;
	double gam;
	double rho;
	double sigm;
	double fTol;
	size_t maxIter;

	bool done(
			const std::vector<std::pair<std::vector<double>, double> >& vecsAndVals);
public:
	NMOptimizer() :
			alph(1.0), gam(2.0), rho(0.5), sigm(0.5), fTol(1e-8), maxIter(600) {
	}
	virtual bool optimize(NMOptimizerObject& object,
			NMOptimizerParams& startParams, NMOptimizerParams& bestParams,
			double& bestValue);

	void setAlpha(double alpha);
	void setGam(double gam);
	void setRho(double rho);
	void setSigm(double sigm);
	void setfTol(double fTol);
	void setmaxIter(size_t maxIter);
	double getAlpha(void);
	double getGam(void);
	double getRho(void);
	double getSigm(void);
	double getfTol(void);
	size_t getmaxIter(void);
};

class EvoOptimizer: public Optimizer {
	double sig1;
	double sig2;
	double sigW;
	size_t stopCnt;
	size_t maxIter;
	size_t nPool;

	Poco::Random rand;

	double getRand() {
		return (rand.nextDouble() + rand.nextDouble() + rand.nextDouble() - 1.5);
	}
public:
	EvoOptimizer() :
			sig1(0.5), sig2(10.00), sigW(0.7), stopCnt(1000), maxIter(15000), nPool(
					100) {
		rand.seed();
	}
	virtual bool optimize(NMOptimizerObject& object,
			NMOptimizerParams& startParams, NMOptimizerParams& bestParams,
			double& bestValue);



};

}
}
} // namespaces

