//============================================================================
// Name        : neurosoft.cpp
// Author      : Przemyslaw Jablonski
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "../optimizationFeatures/NMOptimizer.h"
#include "../testOptimizationFeatures/TestNMOptimizer.h"

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Pipe.h"
#include "Poco/Process.h"
#include <Poco/NumberFormatter.h>
#include "Poco/NumberParser.h"
#include "Poco/Random.h"
#include "Test.h"
#include <iostream>
#include <string.h>
#include "neuroSoft.h"


//class TestFun: public Poco::Runnable {
//	virtual void run() {
//		Test testEvo(evo, acley);
//				testEvo.startPar.setVect(param);
//				testEvo.bestPar.setVect(bestEvo);
//				testEvo.doTest();
//				testEvo.displayInfo();
//	}
//};

using namespace nrs::geometry::nmoptimizer;
using Poco::Process;
using Poco::ProcessHandle;

const char* sendPipe(std::string msg, Poco::Pipe &inPipe) {
	std::string len;
	Poco::NumberFormatter::append(len, msg.size());
	std::string buff(len + "\n" + msg + "\n");
	inPipe.writeBytes((const void*) buff.data(), buff.size());
	return buff.data();
}

int main(int argc, char **argv) {

	TestLBFGS lbfgs;
	lbfgs.sendMesToPipe("q","1","w","2","e","3","r","4",NULL);

	std::string receive ="";
	lbfgs.receiveMessFromPipe();

	receive = lbfgs.getReceiveString();
	std::cout << "Odebrane: "<<std::endl<<receive<<"|:|" ;

	double d = Poco::NumberParser::parseFloat(receive);
	sleep(3);
	std::cout<< lbfgs.getReceiveDouble()<< std::endl;
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
//	Poco::Random rnd;
//	param.push_back(rnd.nextDouble() * 5);
//	param.push_back(rnd.nextDouble() * 5);
//
//	Test testEvo(opt, acley);
//
//	testEvo.startPar.setVect(param);
//	testEvo.bestPar.setVect(bestEvo);
//
//	Poco::Thread thread;
//	thread.start(testEvo);
//	thread.join();
//	std::cout << std::endl;
//
//	sleep(2);
//
//	testEvo.doTest();
//	testEvo.displayInfo();



	std::cout << "koniec" << std::endl;
	return 0;
}
