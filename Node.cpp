/* 
UNR Fall 2022 CPE 400 Final Project - Node Class File
Authors: Gerard Bensadoun Gutsens and Zephyr Vincent
Last Modified: 12 December 2022
*/

#include "Node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

//default constructor - set all values to NULL or 0
Node::Node() {
  m_label = '\0';
  m_numLinks = 0;
  for(int i = 0; i < 10; i++){
    m_links[i] = '\0';
    m_linkCosts[i] = 0;
  }
  m_failureProb = 0;
  m_linkFailure = 0;
}

//parameterized constructor - set all values to supplied values
Node::Node(char label, int numLinks, char links[], int linkCosts[], int failureProb) {
  m_label = label;
  m_numLinks = numLinks;
  for (int i = 0; i < m_numLinks; i++) {
    m_links[i] = links[i];
    m_linkCosts[i] = linkCosts[i];
  }
  m_failureProb = failureProb;
  m_linkFailure = 0;
}

//copy constructor - copy all values from those of given Node
Node::Node(const Node &other){
  m_label = other.m_label;
  m_numLinks = other.m_numLinks;
  for (int i = 0; i < m_numLinks; i++) {
    m_links[i] = other.m_links[i];
    m_linkCosts[i] = other.m_linkCosts[i];
  }
  m_failureProb = other.m_failureProb;
  m_linkFailure = other.m_linkFailure;
}

//assignment operator overload - copy all values from those of supplied Node
void Node::operator=(const Node &other){
  m_label = other.m_label;
  m_numLinks = other.m_numLinks;
  for (int i = 0; i < m_numLinks; i++) {
    m_links[i] = other.m_links[i];
    m_linkCosts[i] = other.m_linkCosts[i];
  }
  m_failureProb = other.m_failureProb;
  m_linkFailure = other.m_linkFailure;
}

//print out the details of current node
void Node::printNode(){
  //print out label and number of links
  std::cout << "Label: " << m_label << ", " << m_numLinks << ", Links: [";

  //iterate through list of links, printing values
  for(int i = 0; i < m_numLinks; i++){
    std::cout << m_links[i];
    if(i != (m_numLinks - 1)){
      std::cout << ", "; //adds comma if link is not last in list
    }
  }

  //print out link costs
  std::cout << "], Link Costs: [";

  //interate through list of link costs, printing values
  for(int i = 0; i < m_numLinks; i++){
    std::cout << m_linkCosts[i];
    if(i != (m_numLinks - 1)){
      std::cout << ", ";
     }
  }

  //print out failure probability of current node
  std::cout << "], failureProb: " << m_failureProb << std::endl;
}

//set node failure probability
void Node::setFailureProb(int failureProb){
  m_failureProb = failureProb;
}

//set link failure probability
void Node::setLinkFailure(int linkFailProb){
  m_linkFailure = linkFailProb;
}

//intialize all variables for new node
void Node::addNode(char label, int numLinks, char links[], int linkCosts[], int failureProb) {
  m_label = label;
  m_numLinks = numLinks;
  for (int i = 0; i < m_numLinks; i++) {
    m_links[i] = links[i];
    m_linkCosts[i] = linkCosts[i];
  }
  m_failureProb = failureProb;
}

//add supplied link and linkCost to current node's list
void Node::addLink(char link, char linkCost) {
  m_links[m_numLinks] = link;
  m_linkCosts[m_numLinks] = linkCost;
  m_numLinks++; //increment link counter
}

//helper function to remove a link from current node, given a link by it's label
void Node::removeLink(char link) {
  int deleteLink = 100; //int variable for index of link to be removed

  //iterate through list of links to find index deleteLink
  for (int i = 0; i < m_numLinks; i++) {
    if (m_links[i] == link) {
      deleteLink = i;
      break;
    }
  }

  //check if given link exists in curr Node lists
  if(deleteLink == 100){
    return;  //return function if link doesn't exist
  }
  
  //iterate through list of links and linkCosts starting after link to be removed
  for (int i = deleteLink + 1; i < m_numLinks; i++) {
    //shift up all values after link to be removed
    m_links[i - 1] = m_links[i];
    m_linkCosts[i - 1] = m_linkCosts[i];
  }
  //decrement linkCounter
  m_numLinks -= 1;
}

//check if provided label matches current node, return 1 if matches
bool Node::checkLabel(char label){
  if(m_label == label){
    return 1;
  }
  return 0;
}

//return char label of current node
char Node::getLabel(){
  return m_label;
}

//return the total number of links connected to current node
int Node::getNumLinks(){
  return m_numLinks;
}

//returns the link label for a given index link
char Node::getLink(int linkIndex){
  return m_links[linkIndex];
}

//return link cost from current node to given node, returns 1000 if nodes aren't adjacent
int Node::costToNode(char label){
  
  //iterate through links to find index of provided link
  for(int i = 0; i < m_numLinks; i++){
    if(m_links[i] == label){
      return m_linkCosts[i];  //if link is in list, return corresponding cost
    }
  }

  //if link is not in current node's list, return 1000 (large value)
  return 1000;
}

//run instance of node failure with set probability, return 1 if node failed
bool Node::nodeFail(){
 int randomVal = rand() % 100 + 1; //Generates random number between 1 and 100
 if(randomVal > m_failureProb){  //probability if node doesn't fail
   return 0;
 }else{  //otherwise indicates node failure
   return 1;
 }
}

//run instance of link failure for all links on current node, return total number of failed links
//the input is a char array by reference to store values of any deleted links
int Node::linkFail(char* failedLinks){
  //initialize helper variables
  int randomVal = 0, linkFailure = 0;

  //iterate through all the links of a given node
  for(int i = 0; i < m_numLinks; i++){
    if(m_links[i] > m_label){    //case to avoid checking links twice (on 2 diff nodes)
    
      randomVal = rand() % 100 + 1; //Generates random number between 1 and 100

      if( randomVal <= m_linkFailure ){ //probability if link fails
        failedLinks[linkFailure] = m_links[i];  //add link to provided char array
        removeLink( m_links[i] ); //call removeLink helper function to remove failed link
        linkFailure++; //increment counter for link failure
      }
    }
  }

  return linkFailure; //return total number of links that failed
}

//visit node, increases nodeFailure probability by 1
void Node::visitNode() {
  m_failureProb += 1; 
}