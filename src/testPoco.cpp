///*
// * testPoco.cpp
// *
// *  Created on: 21 maj 2015
// *      Author: Przemyslaw Jablonski
// */
//
//#include <vector>
//
//#include "../optimizationFeatures/NMOptimizer.h"
//#include "Test.h"
//#include "TestNMOptimizer.h"
//#include "Poco/NumberParser.h"
//#include "Poco/Random.h"
//
//
//
//#include <string.h>
//#include <iostream>
//
//using namespace nrs::geometry::nmoptimizer;
//
//int main(int argc, char** argv) {
//
//	NMOptimizer opt;
//	EvoOptimizer evo;
//
//	std::vector<double> param;
//	std::vector<double> bestNM;
//	std::vector<double> bestEvo;
//
//	AcleyTestFunction acley;
//	SphereTestFunction sphare;
//	TridTestFunction trid;
//	RastriginTestFunction rastrigin;
//
//	struct name nameT;
//	struct task taskT;
//	int argFirst;
//
////	std::cout <<" odebarane w testPoco.cpp ; va = " <<taskT.va<< std::endl;
////	std::cout<<" odebarane w testPoco.cpp ; vb = " <<taskT.vb<<std::endl;
//
//	if (argc > 2 && argc <= 4) {
//		argFirst = Poco::NumberParser::parse(argv[1], ' ');
//
//		if (argv[2] != 0) {
//			param.push_back(Poco::NumberParser::parseFloat(argv[2], '.', ' '));
//		}
//		if (argv[3] != 0) {
//			param.push_back(Poco::NumberParser::parseFloat(argv[3], '.', ' '));
//		}
//	} else if (argc <= 2) {
//		argFirst = 1;
//		Poco::Random rnd;
//		param.push_back(rnd.nextDouble()*5);
//		param.push_back(rnd.nextDouble()*5);
//	}
//
//	if (argc > 4) {
//		argFirst = 1;
//		strcpy(nameT.nameTask, argv[4]);
//		strcpy(nameT.nameResult, argv[5]);
//
//		konsumentGetTask(nameT, taskT);
//		param.push_back(taskT.va);
//		param.push_back(taskT.vb);
//	}
//
//	if (argFirst == 1) {
//		Test testNM(opt, acley);
//		testNM.startPar.setVect(param);
//		testNM.bestPar.setVect(bestNM);
//		testNM.doTest();
//		testNM.displayInfo();
//
//		if (argc > 4) {
//			std::vector<double> f;
//			testNM.bestPar.getVect(f);
//			konsument(nameT, testNM.getBestValue(), f);
//		}
//
//	} else if (argFirst == 2) {
//		Test testEvo(evo, acley);
//		testEvo.startPar.setVect(param);
//		testEvo.bestPar.setVect(bestEvo);
//		testEvo.doTest();
//		testEvo.displayInfo();
//
//		if (argc > 4) {
//			std::vector<double> f;
//			testEvo.bestPar.getVect(f);
//			konsument(nameT, testEvo.getBestValue(), f);
//		}
//	}
//
//	return 0;
//}
