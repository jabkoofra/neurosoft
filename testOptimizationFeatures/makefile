CC=g++

CFLSGS= -Wall -std=c++0x
CFLSGS+= -L/usr/local/lib 
CFLSGS+= -I/usr/local/include

all: testOPT

testOPT: NMOptimizer.o TestNMOptimizer.o Test.o testPoco.o wrapper_c.o
	g++ -Wall -std=c++0x -L/usr/local/lib -o "../testOPT" testPoco.o NMOptimizer.o TestNMOptimizer.o Test.o wrapper_c.o -lPocoFoundation

testPoco.o: testPoco.cpp
	$(CC) -c $(CFLSGS) testPoco.cpp

NMOptimizer.o: NMOptimizer.cpp
	$(CC) -c $(CFLSGS) NMOptimizer.cpp

TestNMOptimizer.o: TestNMOptimizer.cpp
	$(CC) -c $(CFLSGS) TestNMOptimizer.cpp

Test.o: Test.cpp
	$(CC) -c $(CFLSGS) Test.cpp

wrapper_c.o: wrapper_c.cpp
	$(CC) -c $(CFLSGS) wrapper_c.cpp

clean:
	rm -rf *o testWrapper