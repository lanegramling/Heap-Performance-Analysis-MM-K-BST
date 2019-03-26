lab9: main.o
	g++ -std=c++11 -g -Wall main.o -o lab9
main.o: main.cpp HeapK.h HeapK.hpp Timer.h Timer.hpp BinarySearchTree.h BinarySearchTree.hpp BinaryNode.h BinaryNode.hpp
	g++ -std=c++11 -g -Wall -c main.cpp
clean:
	rm *.o lab9
