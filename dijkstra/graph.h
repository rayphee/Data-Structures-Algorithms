//Rafi Mueen
//DSA Assignment 5

#ifndef _GRAPH_H
#define _GRAPH_H

#include <list>
#include <string>
#include "hash.h"
#include "heap.h"

class graph{

public:

  // constructor - initializes with 100 for good measure if nothing is passed to
  // it; can resize if neccessary, but is really reflected by an internal change
  // (specifically in the mapping hash table)
  graph(int capacity = 100);

  // main function called to load graph. Inserts both vertices and edges
  void insertEdge(std::string &sourceVertex, std::string &sinkVertex, int cost);

  // checks to see if the vertex passed is in the graph at all
  bool contains(const std::string &vertex);

  // returns a void pointer to the vertex passed to it if it exists; otherwise, it
  // returns the NULL pointer (by design of hash table)
  void *getVertex(const std::string &vertex);

  // Nested edge class; links two vertices together. Contains the weight and
  // pointed vertex void pointer.
  class edge{
  public:
    int weight;
    void *adjacentVertex;

    edge(int cost, void *passedVertex);
  };

  // Nested vertex class; contains the name, a bool that determines if it's in the
  // set of known vertices, an integer representing the minimum cost ot reach it,
  // a pointer to the previous vertex that must be traversed to reach this one,
  // and a list of edges that reach to adjacent vertices.
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

private:

  // A nice hash table for easy access to everything!
  hashTable *mapping;
};

#endif //_GRAPH_H
