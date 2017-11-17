//Rafi Mueen
//DSA Assignment 5

#include "graph.h"

using namespace std;

// insertionEdge function: inserts an edge to the adjacency list of sourceVertex;
// if either the source or sink vertices do not exist, the graph's vertex list is
// pushed a new vertex with appropriate id's and adjacency lists.
void graph::insertEdge(string &sourceVertexName, string &sinkVertexName, int cost){
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
  edge insertionEdge(cost, sinkVertex);
  sourceVertex->edges.push_back(insertionEdge);
}

// contains function: To keep the mapping private, a special "contains" function
// keeps the hash table locked away, but the contents of the graph searchable.
// Polymorphism ftw.
bool graph::contains(const std::string &vertex){
  return mapping->contains(vertex);
}

// getVertex function: Same deal as with contains, except this time it's to get
// access to the actual data associated with the searched id.
void *graph::getVertex(const std::string &vertex){
  bool b;
  return mapping->getPointer(vertex, &b);
}

// The Constructor: literally only initializes a hash table with the appropriate
// size
graph::graph(int initialSize){
  mapping = new hashTable(initialSize*2);
}

// the vertex constructor: initializes the vertex with the id passed to it and sets
// default values for the other fields (like previousVertex, minDistance, and
// isDefined; obviously when the graph is first generated, or when the vertex is
// added, these values are going to be by default, NULL, infinity (denoted by -1),
// and false respectively)
graph::vertex::vertex(std::string &name){
  id = name;
  isDefined = false;
  minDistance = -1;
  previousVertex = NULL;
}

// the edge constructor: initalizes each edge with a cost and the /next/ vertex
// (the one it's pointing to)
graph::edge::edge(int cost, void *passedVertex){
  weight = cost;
  adjacentVertex = passedVertex;
}
