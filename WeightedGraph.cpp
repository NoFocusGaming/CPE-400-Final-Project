/* 
UNR Fall 2022 CPE 400 Final Project - WeightedGraph Class Header File
Authors: Gerard Bensadoun Gutsens and Zephyr Vincent
Last Modified: 12 December 2022
*/

#include "WeightedGraph.h"
#include "Node.h"
#include <iostream>
#include <algorithm>

//default constructor, sets numNodes to 0
WeightedGraph::WeightedGraph(){
  m_numNodes = 0;
}

//parameterized constructor, sets values with provided nodeList
WeightedGraph::WeightedGraph(int numNodes, Node nodeList[]){
  m_numNodes = numNodes;
  for(int i = 0; i < m_numNodes; i++){
    m_nodeList[i] = nodeList[i];
  }
}

//copy constructor, copies all nodes from given graph to current graph
WeightedGraph::WeightedGraph(WeightedGraph &other){
  m_numNodes = other.getNumNodes();
  for(int i = 0; i < m_numNodes; i++){
    m_nodeList[i] = other.getNode(i);
  }
}

//assignment operator overload, copies all nodes from given graph to current graph
void WeightedGraph::operator=(WeightedGraph &other){
  m_numNodes = other.getNumNodes();
  for(int i = 0; i < m_numNodes; i++){
    m_nodeList[i] = other.getNode(i);
  }
}

//print out current network graph
void WeightedGraph::printGraph(){
  std::cout << "Network with " << m_numNodes << " nodes:" << std::endl;
  for(int i = 0; i < m_numNodes; i++){
    m_nodeList[i].printNode();
  }

  std::cout << std::endl;
}

//return number of nodes on graph
int WeightedGraph::getNumNodes(){
  return m_numNodes;
}

//return node value for provided index
Node WeightedGraph::getNode(int index){
  return m_nodeList[index];
}

//return int index of provided node label
int WeightedGraph::findNode(char source){
  //iterate through all nodes in network, check label of each
  for(int i = 0; i < m_numNodes; i++){
    if(m_nodeList[i].checkLabel(source)){
      return i; //if label matches given node label return current index
    }
  }
  return -1; //if the given label doesn't match any nodes in the network, return -1
}

//remove node from graph
void WeightedGraph::removeNode(int index){
  //iterate through all nodes other than the one to be deleted
  for (int i = 0; i < m_numNodes; i++) {
    if(i != index){
      //remove the node to be deleted from list of link connections on all other nodes
      m_nodeList[i].removeLink( m_nodeList[index].getLabel() );
    }
  }

  //shift all nodes after the one to be deleted
  for (int i = index + 1; i < m_numNodes; i++) {
    m_nodeList[i - 1] = m_nodeList[i];
  } 
  m_numNodes -= 1;  //decrement node counter
}

//run dijkstra's algorithm on current graph, from provided source node
void WeightedGraph::dijkstraAlgo(char source){

/* Part 1 - Initialize Helper Variables*/
  //initialize helper variables, for algorithm
  int nSize = 0;  //nSize stores the size of D[] array
  int otherNodes = m_numNodes - 1; //value of number of nodes to find path for

  //N[] stores completed node paths
  //preNode[] stores the previous node in path to curr node
  //shortNodeList[] stores list of node labels corresponding to nodes in D[]
  char N[otherNodes], preNode[otherNodes], shortNodeList[otherNodes];
  
  //D[] stores the current value of the cost of the path from src
  int D[otherNodes];

  //sets initial value in N[] array to source Node
  N[nSize] = source;
  nSize++; //increments nSize counter

/* Part 2 - Initial Steps in Dijkstra's Algorithm */
  //initial variables for dijkstra's algo
  int srcNode = 0, nIndex = 0;

  //variables for error handling
  bool srcNodeFound = 0, linksFound = 0;

  //iterate through all nodes setting initial values
  for (int i = 0; i < m_numNodes; i++) {
    //if curr node matches the label of the source node, set srcNodeFound
    if(m_nodeList[i].checkLabel(source)){
      srcNode = i;
      srcNodeFound = 1;  //set error handling var
    }else{ //if curr node is not the source node
      D[nIndex] = m_nodeList[i].costToNode(source);  //set D[] values to costToNode values from src to curr node
      shortNodeList[nIndex] = m_nodeList[i].getLabel(); //add label of curr node to helper array

      //if the src node is adjacent to curr node
      if(D[nIndex] < 1000){
        preNode[nIndex] = source; //set preNode to source node
        linksFound = 1;  //set error handling var
      }
      nIndex++; //increment index of helper counter
    }
  }

  //error checking (for cases where nodes/links were deleted)
  if(!srcNodeFound){  //if source node was deleted
    std::cout << "Source node '" << source << "' not found." << std::endl;
    return;
  }else if(!linksFound){ //if all links connecting to src node were deleted
    std::cout << "No links to source node '" << source << "' found." << std::endl;
    return;
  }

/* Part 3 - Looping Dijkstra's Algorithm */
  
  //loop Dijkstra's Algorithm until all nodes are in N
  while(nSize < m_numNodes){
    //initialize values of lowest/lowestIndex to large values
    int lowest = 1000, lowestIndex = 1000;

    //iterate through nodes to find index lowest D[] value of node not already in N[]
    for(int i = 0; i < otherNodes; i++){
      int complete = 0; //helper variable indicating if node is already in N[]
      
      //Check if curr Node is in N[]
      for(int j = 0; j < nSize; j++){
        if(shortNodeList[i] == N[j]){
          complete = 1; //if node is already in N[] set complete value to 1
        }
      }

      //if current node is not already in N[]
      if(!complete){
        //check if current node D[] value is lower than current lowest value
        if(D[i] < lowest){
          //update lowest D[] value information
          lowestIndex = i;
          lowest = D[i];
        }
      }  
    }

    //add the node with lowest D[] value to N[] array
    N[nSize] = shortNodeList[lowestIndex];
    nSize++; //increment size counter of N[] array

    //update D[] for all nodes adjacent to the lowest node, but not in N[]
    for(int i = 0; i < otherNodes; i++){
      //check if node is in array N[]
      int complete = 0; //reset helper value
      for(int j = 0; j < nSize; j++){
        if(shortNodeList[i] == N[j]){
          complete = 1; //if node is already in N[]
        }
      }

      //if current node is not in N[], update D[] value
      if( !complete ){
        int currIndex = lowestIndex; //initialze helper var currIndex
        if(currIndex >= srcNode){
          currIndex += 1;
        }

        //compare current D[] value to the sum of the lowest D[] value + the cost of the path from the curr node to lowest value node
        if(D[i] > D[lowestIndex] + m_nodeList[currIndex].costToNode(shortNodeList[i])){
          D[i] = D[lowestIndex] + m_nodeList[currIndex].costToNode(shortNodeList[i]);  //update D[] value
          preNode[i] = m_nodeList[currIndex].getLabel(); //update the value of preNode[]
        }
      }
    }
  }

/* Part 4 - Print Out Dijkstra's Algorithm Results */
  std::cout << "Dijkstra's Algorithm Results From Source Node " << source << std::endl;

  //iterate through all nodes other than src node
  for(int i = 0; i < otherNodes; i++){
    //print out the label of current node and path length to source
    std::cout << "Path to Node " << shortNodeList[i] << " : length = " << D[i] << " , Path (in reverse direction) = " << shortNodeList[i] << " ";

    //find index of the currentNode in original graph network node list
    int currNode = this->findNode(shortNodeList[i]);
    m_nodeList[currNode].visitNode(); //visit node along network path

    int j = i; //helper variables

    //print out path from current node to source by traversing through preNodes
    while(preNode[j] != source){
      std::cout << preNode[j] << " ";

      //find index of preNode in original graph network node list
      currNode = this->findNode(preNode[j]);
      m_nodeList[currNode].visitNode(); //visit preNode along network path

      //increment j for while loop iteration
      for(int index = 0; index < otherNodes; index++){
        if(shortNodeList[index] == preNode[j]){
          j = index;
          index = otherNodes;
        }
      }
    }
    std::cout << source << std::endl;
  }
}

//run nodeFailure probability for all nodes in network
void WeightedGraph::nodeFailure(){

  bool nodeFail = 0; //bool to check if any nodes failed
  
  std::cout << "Node Failures: ";
  
  for(int i = 0 ; i < m_numNodes; i++){
    //check value of i against updated value of m_numNodes, if there have been failed nodes
    if(nodeFail){
      if(i >= m_numNodes){
        break;
      }
    }
    
    if( m_nodeList[i].nodeFail() ){  // nodeFail returns 1 if currNode failed this round
      //print out failed node
      std::cout << m_nodeList[i].getLabel() << "; ";
      
      this->removeNode(i); //removeCurrNode
      
      nodeFail = 1; //set bool indicating node has failed
    }
  }

  //if no nodes failed this round, print out error message
  if(!nodeFail){
    std::cout << "No nodes failed this round.";
  }

  std::cout << std::endl;
}

//run linkFailure probability for all links in network
void WeightedGraph::linkFailure(){
  int numLinksFailed = 0, linkFailure = 0;
  char linksFailed[19];
  std::cout << "Link Failures: ";
  
  for(int i = 0; i < m_numNodes; i++){
    numLinksFailed = m_nodeList[i].linkFail(linksFailed); //tests links on each node to see if they fail

    //if links failed, remove them from other nodes
    for(int j = 0; j < numLinksFailed; j++){
      linkFailure = 1;
      std::cout << "(" << m_nodeList[i].getLabel() << " , " << linksFailed[j] << "); ";

      for(int index = 0; index < m_numNodes; index++){
        if(m_nodeList[index].getLabel() == linksFailed[j]){  //find the node for the other half of the link
          m_nodeList[index].removeLink( m_nodeList[i].getLabel() ); //remove label of currNode from other half of link
        }
      }
      
    }
  }
  
  //if no links failed this round, print out error message
  if(!linkFailure){
    std::cout << "No links failed this round.";
  }

  std::cout << std::endl;
}