all: main

main: main.o Node.o WeightedGraph.o
	g++ -o main main.o Node.o WeightedGraph.o

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

WeightedGraph.o: WeightedGraph.cpp WeightedGraph.h
	g++ -c WeightedGraph.cpp