CXX=g++
INCLUDE_PATH=include/
SOURCE_PATH=src
CXXFLAGS=-std=c++11 -c -Wall -I

all:
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) main.cpp $(SOURCE_PATH)/*.cpp
	$(CXX) *.o -o game.out

clean:
	rm -rf *.o
	rm game.out
