/**
 * @file  NMOptimizer.cpp
 *
 * @date 2014-10-14 (mrv) module creation
 *
 * @author Paweł Mrówka
 * @author (C) Neurosoft Sp. z o.o. 1992-2014, Wrocław
 */

// $Id:$
#include "PrecompiledHeader.h"      // empty file in linux
#include "NMOptimizer.h"
#include <cmath>
#include <iostream>

namespace nrs {
namespace geometry {
namespace nmoptimizer {

namespace {
bool vecsAndValsComp(const std::pair<std::vector<double>, double>& v1,
		const std::pair<std::vector<double>, double>& v2) {
	return (v1.second < v2.second ? true : false);
}
} // anon. namespace

bool NMOptimizer::done(
		const std::vector<std::pair<std::vector<double>, double> >& vecsAndVals) {
//	size_t nDim = vecsAndVals.front().first.size();
//	for (size_t n1 = 0; n1 < nDim + 1; n1++)
//		for (size_t n2 = 0; n2 < nDim + 1; n2++)
//		{
//			if (n1==n2)
//				continue;
//			double len = 0.0;
//			for (size_t m = 0; m < nDim; m++)
//				len += (vecsAndVals[n1].first[m] - vecsAndVals[n2].first[m]) * (vecsAndVals[n1].first[m] - vecsAndVals[n2].first[m]);
//			if (sqrt(len) > termDist)
//				return false;
//		}

	if (vecsAndVals.back().second - vecsAndVals.front().second <= fTol)
		return true;
	return false;
}

bool NMOptimizer::optimize(NMOptimizerObject& object,
		NMOptimizerParams& startParams, NMOptimizerParams& bestParams,
		double& bestValue) {
	std::vector<double> initX;
	startParams.getVect(initX);
	size_t nDim = initX.size();

	if (nDim < 2)
		throw Poco::RuntimeException(
				"NMOptimizer::optimize: space dimension < 2");

	std::vector<std::pair<std::vector<double>, double> > vecsAndVals;

	// initialize simplex
	Poco::SharedPtr<NMOptimizerParams> tmpX = startParams.copy();
	tmpX->setVect(initX);
	vecsAndVals.push_back(std::make_pair(initX, object.value(*tmpX)));

	for (size_t n = 0; n < nDim; n++) {
		std::vector<double> v(initX);
		if (fabs(v[n]) < 0.00025)
			v[n] = 0.00025;
		else
			v[n] *= 1.05;

		tmpX->setVect(v);
		vecsAndVals.push_back(std::make_pair(v, object.value(*tmpX)));
	}

	std::sort(vecsAndVals.begin(), vecsAndVals.end(), vecsAndValsComp);

	for (size_t iterCnt = 0; iterCnt < maxIter && !done(vecsAndVals);
			iterCnt++) {
		std::vector<double> cog(nDim, 0.0);
		for (size_t n = 0; n < nDim; n++)
			for (size_t m = 0; m < nDim; m++)
				cog[m] += vecsAndVals[n].first[m] / nDim;

		// reflect
		std::vector<double> reflected(nDim);
		for (size_t m = 0; m < nDim; m++)
			reflected[m] = (1.0 + alph) * cog[m]
					- alph * vecsAndVals[nDim].first[m];

		tmpX->setVect(reflected);
		double reflectedV = object.value(*tmpX);

		if (reflectedV < vecsAndVals[0].second) {
			// expand
			std::vector<double> expanded(nDim);
			for (size_t m = 0; m < nDim; m++)
				expanded[m] = (1.0 + gam) * cog[m]
						- gam * vecsAndVals[nDim].first[m];

			tmpX->setVect(expanded);
			double expandedV = object.value(*tmpX);

			if (expandedV < reflectedV)
				vecsAndVals[nDim] = std::make_pair(expanded, expandedV);
			else
				vecsAndVals[nDim] = std::make_pair(reflected, reflectedV);
		} else {
			if (reflectedV < vecsAndVals[nDim - 1].second)
				vecsAndVals[nDim] = std::make_pair(reflected, reflectedV);
			else {
				bool doshrink = false;

				if (reflectedV < vecsAndVals[nDim].second) {
					// Contraction
					std::vector<double> contracted(nDim);
					for (size_t m = 0; m < nDim; m++)
						contracted[m] = (1.0 + rho) * cog[m]
								- rho * vecsAndVals[nDim].first[m];

					tmpX->setVect(contracted);
					double contractedV = object.value(*tmpX);

					if (contractedV <= reflectedV)
						vecsAndVals[nDim] = std::make_pair(contracted,
								contractedV);
					else
						doshrink = true;
				} else {
					// Inside contraction
					std::vector<double> contracted(nDim);
					for (size_t m = 0; m < nDim; m++)
						contracted[m] = (1.0 - rho) * cog[m]
								+ rho * vecsAndVals[nDim].first[m];

					tmpX->setVect(contracted);
					double contractedV = object.value(*tmpX);

					if (contractedV < vecsAndVals[nDim].second)
						vecsAndVals[nDim] = std::make_pair(contracted,
								contractedV);
					else
						doshrink = true;
				}

				if (doshrink) {
					for (size_t n = 1; n < nDim + 1; n++) {
						std::vector<double> tmp(nDim);
						for (size_t m = 0; m < nDim; m++)
							tmp[m] = vecsAndVals[0].first[m]
									+ sigm
											* (vecsAndVals[n].first[m]
													- vecsAndVals[0].first[m]);

						tmpX->setVect(tmp);
						vecsAndVals[n] = std::make_pair(tmp,
								object.value(*tmpX));
					}
				}
			}
		}

		std::sort(vecsAndVals.begin(), vecsAndVals.end(), vecsAndValsComp);

		if (callback) {
			Poco::SharedPtr<NMOptimizerParams> curBest = tmpX->copy();
			curBest->setVect(vecsAndVals.front().first);
			callback->onProgress(iterCnt, *curBest.get(),
					vecsAndVals.front().second);
		}
	}

	// termination
	bestParams.setVect(vecsAndVals[0].first);
	bestValue = object.value(bestParams);

	return true;
}

void NMOptimizer::setAlpha(double alph){this->alph	= alph;}
void NMOptimizer::setGam(double gam){this->gam=gam;}
void NMOptimizer::setRho(double rho){this->rho=rho;}
void NMOptimizer::setSigm(double sigm){this->sigm=sigm;}
void NMOptimizer::setfTol(double fTol){this->fTol = fTol;}
void NMOptimizer::setmaxIter(size_t maxIter){this->maxIter = maxIter;}
double NMOptimizer::getAlpha(void){return this->alph;}
double NMOptimizer::getGam(void){return this->gam;}
double NMOptimizer::getRho(void){return this->rho;}
double NMOptimizer::getSigm(void){return this->sigm;}
double NMOptimizer::getfTol(void){return this->fTol;}
size_t NMOptimizer::getmaxIter(void){return this->maxIter;}


bool EvoOptimizer::optimize(NMOptimizerObject& object,
		NMOptimizerParams& startParams, NMOptimizerParams& bestParams,
		double& bestValue) {
	std::vector<double> initX;
	startParams.getVect(initX);
	size_t nDim = initX.size();

	if (nDim < 2)
		throw Poco::RuntimeException(
				"EvoOptimizer::optimize: space dimension < 2");

	std::vector<std::pair<std::vector<double>, double> > vecsAndVals;

	// initialize pool
	Poco::SharedPtr<NMOptimizerParams> tmpX = startParams.copy();
	tmpX->setVect(initX);
	vecsAndVals.push_back(std::make_pair(initX, object.value(*tmpX)));

	for (size_t n = 0; n < nPool; n++) {
		std::vector<double> v(initX);
		for (size_t m = 0; m < nDim; m++)
			v[m] += sig1 * getRand();

		tmpX->setVect(v);
		vecsAndVals.push_back(std::make_pair(v, object.value(*tmpX)));
	}

	size_t breakCnt = 0;
	double lastBestVal;
	for (size_t iterCnt = 0; iterCnt < maxIter && breakCnt < stopCnt;
			iterCnt++) {
		std::sort(vecsAndVals.begin(), vecsAndVals.end(), vecsAndValsComp);

		std::cout << "EVO " << vecsAndVals.front().second << " "
				<< vecsAndVals.back().second << std::endl;

		if (iterCnt == 0 || vecsAndVals.front().second < lastBestVal) {
			lastBestVal = vecsAndVals.front().second;
			breakCnt = 0;
		} else
			breakCnt++;

		while (vecsAndVals.size() > nPool / 2)
			vecsAndVals.pop_back();

		while (vecsAndVals.size() < nPool) {
			size_t ind = rand.next(nPool / 2);
			std::vector<double> v(vecsAndVals[ind].first);
			bool s = rand.nextDouble() < sigW ? true : false;
			for (size_t m = 0; m < nDim; m++)
				v[m] += (s ? sig1 : sig2) * getRand();

			tmpX->setVect(v);
			vecsAndVals.push_back(std::make_pair(v, object.value(*tmpX)));
		}

		if (callback) {
			Poco::SharedPtr<NMOptimizerParams> curBest = tmpX->copy();
			curBest->setVect(vecsAndVals.front().first);
			callback->onProgress(iterCnt, *curBest.get(),
					vecsAndVals.front().second);
		}
	}

	std::sort(vecsAndVals.begin(), vecsAndVals.end(), vecsAndValsComp);
	bestParams.setVect(vecsAndVals[0].first);
	bestValue = object.value(bestParams);

	return true;
}

}
}
} // namespaces

