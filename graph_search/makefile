CXX = g++
CXXFLAGS = -std=c++11 -I/usr/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = demo.o test.o

all: tree test

tree: demo.o
	$(CXX) -o tree demo.o $(LDFLAGS)
	./tree

test: test.o
	$(CXX) -o test test.o

demo.o: demo.cpp Node.hpp Tree.hpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

test.o: test.cpp Node.hpp Tree.hpp Complex.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

valgrind: tree
	valgrind --leak-check=full ./tree

clean:
	rm -f *.o tree test
