LIBS=-lcppcms -lbooster -lmudflap -std=c++11


all: hello

hello: hello.cpp
	$(CXX) -O2 -Wall -g -fmudflap hello.cpp -o hello ${LIBS}

clean:
	rm -fr hello hello.exe cppcms_rundir
