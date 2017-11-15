//Rafi Mueen
//DSA Assignment 5

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <list>
#include <string>
#include "hash.h"
#include "heap.h"

class graph{

public:

  graph(int capacity = 100);

  int insertEdge(std::string &sourceVertex, std::string &sinkVertex, int cost);

  bool contains(const std::string &vertex);

  void *getVertex(const std::string &vertex);

  bool isSolved;

  class edge{
  public:
    int weight;
    void *originVertex;
    void *adjacentVertex;

    edge(int cost, void *firstVertex, void *lastVertex);
  };

  class vertex{
  public:
    std::string id;
    bool isDefined;
    int minDistance;
    void *previousVertex;

    vertex(std::string &id);
    std::list<edge> edges;
  };

  std::list<vertex> vertices;

  hashTable *mapping;
};

#endif //_GRAPH_H
