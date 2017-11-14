//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <cmath>
#include <algorithm>
#include "graph.h"

using namespace std;


int graph::insert(string &sourceVertex, string &sinkVertex, int cost){
  bool graphContainsVertex;
  vertex *sourceVertexPointer = static_cast<vertex *> (mapping->getPointer(sourceVertex, &graphContainsVertex));
  if(!graphContainsVertex){

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
