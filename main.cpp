/* 
UNR Fall 2022 CPE 400 Final Project - Main File
Authors: Gerard Bensadoun Gutsens and Zephyr Vincent
Last Modified: 12 December 2022
*/

#include <iostream>
#include <string>
#include "Node.h"
#include "WeightedGraph.h"
#include <stdlib.h>
#include <time.h>

int main() {
  srand (time(NULL));  //setup srand for later use with probabilities

/* Part 1 - Network Initialization */
  Node nodeList[10];
 
  char linksA[9] = {'B', 'C', 'D'}; 
  int linkCostsA[9] = {2, 3, 1};
  nodeList[0].addNode('A', 3, linksA, linkCostsA, 0);

  char linksB[9] = {'A', 'C', 'D'}; 
  int linkCostsB[9] = {2, 2, 3};
  nodeList[1].addNode('B', 3, linksB, linkCostsB, 0);
  
  char linksC[9] = {'A', 'B', 'G', 'H'}; 
  int linkCostsC[9] = {3, 2, 3, 4};
  nodeList[2].addNode('C', 4, linksC, linkCostsC, 0);

  char linksD[9] = {'A', 'B', 'E', 'F'};
  int linkCostsD[9] = {1, 3, 2, 3};
  nodeList[3].addNode('D', 4, linksD, linkCostsD, 0);

  char linksE[9] = {'D', 'G', 'I', 'J'};
  int linkCostsE[9] = {2, 2, 5, 4};
  nodeList[4].addNode('E', 4, linksE, linkCostsE, 0);

  char linksF[9] = {'D', 'J'};
  int linkCostsF[9] = {3, 3};
  nodeList[5].addNode('F', 2, linksF, linkCostsF, 0);

  char linksG[9] = {'C', 'E', 'H', 'I', 'J'};
  int linkCostsG[9] = {3, 2, 1, 3, 2};
  nodeList[6].addNode('G', 5, linksG, linkCostsG, 0);
  
  char linksH[9] = {'C', 'G', 'I', 'J'};
  int linkCostsH[9] = {4, 1, 1, 2};
  nodeList[7].addNode('H', 4, linksH, linkCostsH, 0);

  char linksI[9] = {'E','G', 'H', 'J'};
  int linkCostsI[9] = {5, 3, 1, 2};
  nodeList[8].addNode('I', 4, linksI, linkCostsI, 0);

  char linksJ[9] = {'E', 'F', 'G', 'H', 'I'};
  int linkCostsJ[9] = {4, 3, 2, 2, 2};
  nodeList[9].addNode('J', 4, linksJ, linkCostsJ, 0);
  
  //Intialize the probabiity of failure for each node based on user input
  std::cout << "For each node, please enter an integer value from 0 to 100 representing its percentage probability of failure." << std::endl;
  std::cout << "Node 1 = A, Node 2 = B, Node 3 = C, etc." << std:: endl << std::endl;

  //Iterate through all 10 nodes, accepting user input
  for(int i = 1; i < 11; i++){
    int failureProb = 0;
    std::cout << "Node " << i << " Failure Probability: ";
    std::cin >> failureProb; 
    nodeList[(i-1)].setFailureProb(failureProb);
  }

  //Intialize the probabiity of link failure based on user input
  int linkFailure = 0;
  std::cout << std::endl << "Enter a integer value from 0 to 100 representing the probabilty of link failure (this percentage probability is equal for all links): ";
  std::cin >> linkFailure;

  //Iterate through all 10 nodes, set values for linkFailure
  for(int i = 0; i < 10; i++){
    nodeList[i].setLinkFailure(linkFailure);
  }

  //Initialize network with values set above
  WeightedGraph originalGraph(10, nodeList);

  //Print out Network Graph
  std::cout << std::endl << "Original Graph: " << std::endl;
  originalGraph.printGraph();

/* Part 2 - Original Dijkstra's Algorithm */
  std::cout << std::endl << "=================================" << std::endl;
  std::cout << "Original Routing Algorithm (no failed links/nodes" << std::endl;

  //Accept user input for source node choice
  char sourceLabel;
  std::cout << "Enter the letter of the source node for Dijsktra's Algorithm: ";
  std::cin >> sourceLabel;

  //Run dijsktra's algorithm with user chosen source node
  originalGraph.dijkstraAlgo(sourceLabel);

/* Part 3 - Node and Link Failure */
  //initialize variables for while loop (multiple rounds)
  int userChoice = 0, round = 1;

  //initialize currentGraph for use with node/link failure
  WeightedGraph currentGraph = originalGraph;

  //do-while loop to run rounds of node/link failure simulation
  do{
    std::cout << std::endl << "=================================" << std::endl;

    //user option to reset network to original status (restore failed nodes)
    if(userChoice == 1){ //if statement occurs in all except the 1st round
      int resetGraph;
      std::cout << "Reset graph to original? (1 for yes, 0 for no): ";
      std::cin >> resetGraph;

      //if user chooses, reset the currentGraph to be equal to the original network system
      if(resetGraph){
        currentGraph = originalGraph;
      }
    }

    //Node and Link Failure
    std::cout << std::endl << "Round " << round << " of node and link failure" << std::endl;

    //calling WeightedGraph member functions to print out failed nodes/links
    //Functions delete failed nodes and links from currentGraph 
    currentGraph.nodeFailure();
    currentGraph.linkFailure();

    //user option to display the updated network (with failed nodes/links)
    int printOutGraph;
    std::cout << std::endl << "Print out updated graph? (1 for yes, 0 for no): ";
    std::cin >> printOutGraph;

    if(printOutGraph){
      std::cout << std::endl << "New Graph: " << std::endl;
      currentGraph.printGraph();
    }

    //run Dijkstra's Algorithm
    std::cout << std::endl << "Round " << round << " Dijkstra's Algorithm" << std::endl;

    //run algorithm with prior user chosen source node
    currentGraph.dijkstraAlgo(sourceLabel);

    //user option to run another round of link/node failure or end program
    std::cout << std::endl << "Run another round? (1 for yes, 0 for no): ";
    std::cin >> userChoice;
    std::cout << std::endl;
    
    round += 1; //increment round counter
  }while(userChoice == 1);
}