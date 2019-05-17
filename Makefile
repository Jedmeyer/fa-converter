LIBS=-lcppcms -lbooster -std=c++11


all: hello

hello: hello.cpp
	$(CXX) -O2 -Wall -g hello.cpp -o hello ${LIBS}

clean:
	rm -fr hello hello.exe cppcms_rundir
