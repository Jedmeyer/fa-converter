LIBS=-lcppcms -lbooster -std=c++11


all: hello

hello: hello.cpp
	$(CXX) -O2 -Wall -g -fsanitize=address -fno-omit-frame-pointer hello.cpp -o hello ${LIBS}

clean:
	rm -fr hello hello.exe cppcms_rundir
