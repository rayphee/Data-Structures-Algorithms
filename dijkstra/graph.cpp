//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <cmath>
#include <algorithm>
#include "graph.h"

using namespace std;


int graph::insertEdge(string &sourceVertexName, string &sinkVertexName, int cost){
  bool graphContainsSource;
  bool graphContainsSink;
  vertex *sourceVertex = static_cast<vertex *> (mapping->getPointer(sourceVertexName, &graphContainsSource));
  vertex *sinkVertex = static_cast<vertex *> (mapping->getPointer(sinkVertexName, &graphContainsSink));
  if(!graphContainsSource){
    vertex insertionSourceVertex(sourceVertexName);
    vertices.push_back(insertionSourceVertex);
    mapping->insert(sourceVertexName, &vertices.back());
    sourceVertex = static_cast<vertex *> (mapping->getPointer(sourceVertexName, &graphContainsSource));
  }
  if(!graphContainsSink){
    vertex insertionSinkVertex(sinkVertexName);
    vertices.push_back(insertionSinkVertex);
    mapping->insert(sinkVertexName, &vertices.back());
    sinkVertex = static_cast<vertex *> (mapping->getPointer(sinkVertexName, &graphContainsSink));
  }
  edge insertionEdge(cost, sourceVertex, sinkVertex);
  sourceVertex->edges.push_back(insertionEdge);
  return 0;
}

bool graph::contains(const std::string &vertex){
  return mapping->contains(vertex);
}

void *graph::getVertex(const std::string &vertex){
  bool b;
  return mapping->getPointer(vertex, &b);
}


graph::graph(int capacity){
  mapping = new hashTable(capacity*2);
  isSolved = false;
}

graph::vertex::vertex(std::string &name){
  id = name;
  isDefined = false;
  minDistance = -1;
  previousVertex = NULL;
}

graph::edge::edge(int cost, void *firstVertex, void *lastVertex){
  weight = cost;
  originVertex = firstVertex;
  adjacentVertex = lastVertex;
}
