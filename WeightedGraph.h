/* 
UNR Fall 2022 CPE 400 Final Project - WeightedGraph Class Header File
Authors: Gerard Bensadoun Gutsens and Zephyr Vincent
Last Modified: 12 December 2022
*/

#ifndef WEIGHTEDGRAPH_H_
#define WEIGHTEDGRAPH_H_

#include <iostream>
#include "Node.h"

class WeightedGraph{
  private:
    int m_numNodes;
    Node m_nodeList[10];
  public:
    WeightedGraph(); //default constructor
    WeightedGraph(int numNodes, Node nodeList[]); //parameterized constructor
    WeightedGraph(WeightedGraph &other); //copy constructor
    void operator=(WeightedGraph &other); //assignment operator overload

    void printGraph(); //print out current network graph

    int getNumNodes(); //return number of nodes on graph
    Node getNode(int index); //return node value for provided index
    int findNode(char source); //return int index of provided node label
    void removeNode(int index); //remove node from graph

    void dijkstraAlgo(char source); //run dijkstra's algorithm on current graph, from provided source node

    void nodeFailure(); //run nodeFailure probability for all nodes in network
    void linkFailure(); //run linkFailure probability for all links in network
};

#endif