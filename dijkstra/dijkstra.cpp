//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <ctime>
#include "graph.h"
#include "heap.h"

using namespace std;

// loadGraph function: creates a filestream with the string passed to it as the
// file from which it streams. Parses each line into three pieces, which serve
// as arguments to the insertEdge function for the graph passed to it.
void loadGraph(string inputFilename, graph &graphToLoad){
  ifstream inputFile;

  inputFile.open(inputFilename.c_str());
  if (!inputFile) {
    cerr << "Error: could not open " << inputFilename << endl;
    exit(1);
  }
  string line;
  while(getline(inputFile, line)){
    istringstream ss(line);
    string source, sink;
    int cost;
    ss >> source >> sink >> cost;
    graphToLoad.insertEdge(source, sink, cost);
  }
  inputFile.close();
}

// dijkstra function: where the magic happens. A heap is created to hold the
// vertices and their minimum weights. First, the starting vertex is readied by
// setting its minDistance to 0 and marking it as isDefined true. Then, all of its
// adjacent vertices are added to the heap with their minDistance updated as
// necessary. The following loop keeps running until the heap is completely empty,
// but is essentially an extension of the first loop for the starting vertex, yet
// opened up for the following vertices.
void dijkstra(graph &graphToTraverse, string startVertexName){
  heap dijkstraHeap(100);
  string *poppedVertexName;
  int *updatingWeights;
  graph::vertex *vertexToAnalyze;
  graph::vertex *adjacentToAnalyze;
  int currentPathCost;

  vertexToAnalyze = static_cast<graph::vertex *> (graphToTraverse.getVertex(startVertexName));
  vertexToAnalyze->minDistance = 0;
  vertexToAnalyze->isDefined = true;

  for(list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();++iterEdge){
    adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
    currentPathCost = iterEdge->weight;
    if(adjacentToAnalyze->minDistance == -1){
      dijkstraHeap.insert(adjacentToAnalyze->id, iterEdge->weight, adjacentToAnalyze);
      adjacentToAnalyze->previousVertex = vertexToAnalyze;
      adjacentToAnalyze->minDistance = currentPathCost;
    }
    else if(adjacentToAnalyze->minDistance > currentPathCost){
      dijkstraHeap.setKey(adjacentToAnalyze->id, currentPathCost);
      adjacentToAnalyze->previousVertex = vertexToAnalyze;
      adjacentToAnalyze->minDistance = currentPathCost;
    }
  }

  while(!dijkstraHeap.deleteMin(poppedVertexName, updatingWeights, &vertexToAnalyze)){
    vertexToAnalyze = static_cast<graph::vertex *> (vertexToAnalyze);
    if(!vertexToAnalyze->isDefined){
      vertexToAnalyze->isDefined = true;
      for(list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();++iterEdge){
        adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
        currentPathCost = vertexToAnalyze->minDistance + iterEdge->weight;
        if(adjacentToAnalyze->minDistance == -1){
          dijkstraHeap.insert(adjacentToAnalyze->id, currentPathCost, adjacentToAnalyze);
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
          adjacentToAnalyze->minDistance = currentPathCost;
        }
        else if(adjacentToAnalyze->minDistance > currentPathCost){
          dijkstraHeap.setKey(adjacentToAnalyze->id, currentPathCost);
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
          adjacentToAnalyze->minDistance = currentPathCost;
        }
      }
    }
  }
}

// outputSolvedGraph function: creates a filestream for the file specified by the
// string inputted to it first. Then, the graph that was passed iterates through
// each vertex, determines if it is defined (if not "NO PATH" is printed). If it is
// defined, a stack is initialized to iterate through all previousVertex's for the
// vertex found and printed in order by successively popping after its minDistance
// is printed.
void outputSolvedGraph(string outputFilename, graph &solvedGraph){
  ofstream outputFile(outputFilename.c_str());
  stack<std::string> tracebackStack;
  for(std::list<graph::vertex>::iterator iterVert = solvedGraph.vertices.begin(); iterVert != solvedGraph.vertices.end(); iterVert++){
    outputFile << iterVert->id << ": ";
    if(iterVert->isDefined){
      outputFile << iterVert->minDistance;
      outputFile << " [";
      graph::vertex *tracebackVertex;
      graph::vertex *helloVertex;
      tracebackVertex = static_cast<graph::vertex *> (iterVert->previousVertex);
      while(tracebackVertex){
        tracebackStack.push(tracebackVertex->id);
        tracebackVertex = (static_cast<graph::vertex *> (tracebackVertex->previousVertex));
      }
      while(!tracebackStack.empty()){
        outputFile << tracebackStack.top() << ", ";
        tracebackStack.pop();
      }
      outputFile << iterVert->id;
      outputFile << "]" << endl;
    }
    else{
      outputFile << "NO PATH" << endl;
    }
  }
  outputFile.close();
}

// main function: initializes empty graph and associated variables required to load
// and output graph data. Also prints commands to terminal window to facilitate
// process of loading and outputting the graph/algorithm results.
int main(){
  clock_t checkStartTime, checkEndTime;
  double checkTime;
  string inputFilename, outputFilename;
  graph dijkstraGraph(1000);
  string startVertex = "";

  cout << "Enter name of graph file: ";
  cin >> inputFilename;
  loadGraph(inputFilename, dijkstraGraph);
  while(!dijkstraGraph.contains(startVertex)){
    cout << "Enter a valid vertex id for the starting vertex: ";
    cin >> startVertex;
  }
  cout << "Enter name of output file: ";
  cin >> outputFilename;

  checkStartTime = clock();
  dijkstra(dijkstraGraph, startVertex);
  checkEndTime = clock();
  checkTime = ((double) (checkEndTime - checkStartTime)) / CLOCKS_PER_SEC;

  outputSolvedGraph(outputFilename, dijkstraGraph);

  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << checkTime << endl;

  return 0;
}
