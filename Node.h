/* 
UNR Fall 2022 CPE 400 Final Project - Node Class Header File
Authors: Gerard Bensadoun Gutsens and Zephyr Vincent
Last Modified: 12 December 2022
*/

#ifndef NODE_H_
#define NODE_H_

#include <iostream>

class Node {
private:
  char m_label;
  int m_numLinks;
  char m_links[9];
  int m_linkCosts[9];
  int m_failureProb;
  int m_linkFailure;

public:
  Node(); //default constructor
  Node(char label, int numLinks, char links[], int linkCosts[], int failureProb); //parameterized constructor
  Node(const Node &other);  //copy constructor
  void operator=(const Node &other); //assignment operator overload

  void printNode(); //print out the details of current node

  void setFailureProb(int failureProb); //set node failure probability
  void setLinkFailure(int linkFailProb); //set link failure probability

  void addNode(char label, int numLinks, char links[], int linkCosts[], int failureProb); //node initialization
  void addLink(char link, char linkCost); //add link and linkCost to current node's list
  void removeLink(char link); //remove link and corresponding linkCost
  
  bool checkLabel(char label); //check if label matches current node
  char getLabel(); //return char label of current node
  int getNumLinks(); //return the total number of links connected to current node
  char getLink(int linkIndex); //returns the link label for a given index link

  int costToNode(char label); //return link cost from current node to given node, returns 1000 if nodes aren't adjacent

  bool nodeFail(); //run instance of node failure with set probability, return 1 if node failed
  int linkFail(char* failedLinks); //run instance of link failure for all links on current node, return total number of failed links

  void visitNode(); //visit node -> increases nodeFailure probability
};

#endif