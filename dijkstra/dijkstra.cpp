//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "graph.h"
#include "heap.h"

using namespace std;

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
void dijkstra(graph &graphToTraverse, string startVertexName){
  heap dijkstraHeap(100);
  string *edgeName;
  int *updatingWeights;
  void *vertexToAnalyzeVoid;
  graph::vertex *vertexToAnalyze;
  graph::vertex *adjacentToAnalyze;
  int edgeNumber = 0;

  vertexToAnalyze = static_cast<graph::vertex *> (graphToTraverse.getVertex(startVertexName));
  vertexToAnalyze->minDistance = 0;
  vertexToAnalyze->previousVertex = NULL;
  vertexToAnalyze->isDefined = true;

  for(std::list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();){
    adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
    dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, adjacentToAnalyze);
    edgeNumber++;
    if(adjacentToAnalyze->minDistance == -1){
      adjacentToAnalyze->minDistance = iterEdge->weight;
      adjacentToAnalyze->previousVertex = vertexToAnalyze;
    }
    else if((adjacentToAnalyze->minDistance)>(vertexToAnalyze->minDistance + iterEdge->weight)){
      adjacentToAnalyze->minDistance = vertexToAnalyze->minDistance + iterEdge->weight;
      adjacentToAnalyze->previousVertex = vertexToAnalyze;
    }
     iterEdge++;
  }

  cout << endl;

  while(!graphToTraverse.isSolved){
    dijkstraHeap.deleteMin(edgeName, updatingWeights, &vertexToAnalyzeVoid);
    vertexToAnalyze = static_cast<graph::vertex *> (vertexToAnalyzeVoid);
    if(!vertexToAnalyze->isDefined){
      vertexToAnalyze->isDefined = true;
      for(std::list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();){
        adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
        dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, adjacentToAnalyze);
        edgeNumber++;
        if(adjacentToAnalyze->minDistance == -1){
          adjacentToAnalyze->minDistance = vertexToAnalyze->minDistance + iterEdge->weight;
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
        }
        else if((adjacentToAnalyze->minDistance)>(vertexToAnalyze->minDistance + iterEdge->weight)){
          adjacentToAnalyze->minDistance = vertexToAnalyze->minDistance + iterEdge->weight;
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
        }
         iterEdge++;
      }
    }
    if(dijkstraHeap.isEmpty()){
      graphToTraverse.isSolved = true;
    }
  }
  return;
}

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
// and output graph data
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
