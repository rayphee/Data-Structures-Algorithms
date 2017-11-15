//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <cmath>
#include <algorithm>
#include "graph.h"

using namespace std;


int graph::insert(string &sourceVertex, string &sinkVertex, int cost){
  bool graphContainsSource;
  bool graphContainsSink;
  vertex *sourceVertexPointer = static_cast<vertex *> (mapping->getPointer(sourceVertex, &graphContainsSource));
  vertex *sinkVertexPointer = static_cast<vertex *> (mapping->getPointer(sinkVertex, &graphContainsSink));
  if(!graphContainsSource){
    vertex insertionVertex(sourceVertex);
    vertices.push_back(insertionVertex);
    mapping->insert(sourceVertex, &vertices.back());
    *sourceVertexPointer = static_cast<vertex> (vertices.back());
  }
  else{

  }
  if(!graphContainsSink){

  }
  else{

  }
  return 0;
}

bool graph::contains(const std::string &vertex){
  return mapping->contains(vertex);
}


graph::graph(int capacity){
  mapping = new hashTable(capacity*2);
}

graph::vertex::vertex(std::string &name){
  id = name;
  isDefined = false;
  minDistance = -1;
  previousVertex = NULL;
}
