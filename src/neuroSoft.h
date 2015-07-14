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
#include "Poco/NumberParser.h"
#include "Poco/Random.h"
#include "Test.h"
#include <iostream>
#include <string.h>
#include <stdarg.h>

class TestLBFGS {
public:

	TestLBFGS(void);
	TestLBFGS(char* args, ...);
	int sendMesToPipe(char* msg, ...);
	void receiveMessFromPipe(void);

	std::string getReceiveString(void);
	double getReceiveDouble(void);


private:
	std::string cmd;
	std::vector<std::string> args;
	Poco::Pipe outPipe;
	Poco::Pipe inPipe;

	std::string receiveString;
	double receiveDouble;

};

#endif /* NEUROSOFT_H_ */
