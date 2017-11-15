//Rafi Mueen
//DSA Assignment 5

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <list>
#include <string>
#include "hash.h"
#include "heap.h"

class graph{

public:

  graph(int capacity = 100);

  int insert(std::string &sourceVertex, std::string &sinkVertex, int cost);

  bool contains(const std::string &vertex);

private:

  class edge{
    int weight;
    void *originVertex;
    void *adjacentVertex;
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
  void *dijkstraHeap;
};

#endif //_GRAPH_H
