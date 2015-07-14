/*
 * neuroSoft.h
 *
 *  Created on: 10 lip 2015
 *      Author: jabko
 */

#ifndef NEUROSOFT_H_
#define NEUROSOFT_H_

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
#include <stdarg.h>

class TestLBFGS {
public:

	TestLBFGS();
	int sendMesToPipe(char* msg, ...);
	std::string receiveMessFromPipe();
	Poco::Pipe outPipe;
	Poco::Pipe inPipe;

private:
	std::string cmd;
	std::vector<std::string> args;

};

#endif /* NEUROSOFT_H_ */
