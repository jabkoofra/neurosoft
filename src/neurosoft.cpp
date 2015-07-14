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
	lbfgs.sendMesToPipe("111","222","333",NULL);

//	std::string cmd("/home/jabko/workspace/PipePocoRead/Debug/PipePocoRead");
//	std::vector<std::string> args;
//	args.push_back(" ");
//	Poco::Pipe outPipe;
//	Poco::Pipe inPipe;
//	std::cout << "PID: " << getpid() << std::endl;
//	ProcessHandle ph = Process::launch(cmd, args, &inPipe, &outPipe, 0);
//	const char *r = sendPipe("1729",inPipe);
//	inPipe.writeBytes((const void*) r, 14);
//	std::cout<<"PID2 "<< ph.id()<<std::endl;

	char buff[1];
	memset((char *) &buff, 0, strlen(buff));
	int t = 1;
	std::string receive = "";


	while (t) {
		receive += buff;
		t = lbfgs.outPipe.readBytes(buff, 1);
//		std::cout<<buff<<"|"<<receive<<std::endl;
	}
	std::cout<<std::endl;
	std::cout << receive << std::endl;

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
