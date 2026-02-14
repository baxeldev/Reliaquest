CXX=g++
CXXFLAGS=-std=gnu++17 -O2

all: daemon cli

daemon: daemon.cpp
	$(CXX) $(CXXFLAGS) daemon.cpp -o daemon

cli: cli.cpp
	$(CXX) $(CXXFLAGS) cli.cpp -o cli

clean:
	rm -f daemon cli