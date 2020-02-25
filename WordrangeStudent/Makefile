CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = AVL.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange AVL.o wordrange.o

AVL.o: AVL.cpp AVL.h
	$(CXX) -g $(CXXFLAGS) -c AVL.cpp

wordrange.o: AVL.cpp AVL.h wordrange.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

clean: 
	rm -f *.o
	rm wordrange