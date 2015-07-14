/*
 * neuroSoft.cpp
 *
 *  Created on: 10 lip 2015
 *      Author: jabko
 */

#include "neuroSoft.h"

TestLBFGS::TestLBFGS() {
	std::string cmd("/home/jabko/workspace/PipePocoRead/Debug/PipePocoRead");
	std::vector<std::string> args;
	Poco::ProcessHandle ph = Poco::Process::launch(cmd, args, &inPipe, &outPipe,
			0);

}

int TestLBFGS::sendMesToPipe(char* msg, ...) {
	std::string len = "";
	std::string buff = "";
	int paragraph = 0;

	va_list ap;
	va_start(ap, msg);

	buff += msg;
	buff += "\n";
	paragraph++;
	while (1) {
		char *str = va_arg(ap, char *); // get next argument
		if (str == NULL)
			break;
		buff += str;
		buff += "\n";
		paragraph++;
//			std::cout<<buff<<"|"<<std::endl;
	}
//		std::cout<<buff<<"||"<<std::endl;

	Poco::NumberFormatter::append(len, buff.size() - paragraph);
	len += "\n";
	Poco::NumberFormatter::append(len, paragraph);
	buff = len + "\n" + buff;
	std::cout << buff << "|" << std::endl;
	int send = this->inPipe.writeBytes((const void*) buff.data(), buff.size());
	return send;
}
