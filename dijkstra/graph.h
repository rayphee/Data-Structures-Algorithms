//Rafi Mueen
//DSA Assignment 5

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <list>
#include <string>
#include "hash.h"

class graph{

public:

  graph(int capacity = 100);

  int insert(std::string &sourceVertex, std::string &sinkVertex, int cost);

  bool contains(const std::string &vertex);

private:

  class vertex{
  public:
    std::string id;
    bool isDefined;
    int minDistance;
    void *previousVertex;

    vertex(bool isDefined = false, int minDistance = -1, void *previousVertex = NULL);

    class edge{
      int weight;
      void *adjacentVertex;
    };
    std::list<edge> edges;
  };

  std::list<vertex> vertices;

  hashTable *mapping;

};

#endif //_GRAPH_H
