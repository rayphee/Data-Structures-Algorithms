//Rafi Mueen
//DSA Assignment 5

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
  string edgeName;
  int updatingWeights;
  graph::vertex *startVertex;
  graph::vertex *startAdjacentToAnalyze;
  int edgeNumber = 0;

  startVertex = static_cast<graph::vertex *> (graphToTraverse.getVertex(startVertexName));
  startVertex->minDistance = 0;
  startVertex->previousVertex = NULL;
  startVertex->isDefined = true;

  // cout << "startVertex address: " << startVertex << endl;

  for(std::list<graph::edge>::iterator iterEdge = startVertex->edges.begin(); iterEdge != startVertex->edges.end();){
    startAdjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
    // cout << edgeNumber << startAdjacentToAnalyze->id << startAdjacentToAnalyze->isDefined << startAdjacentToAnalyze->minDistance << endl;
    dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, startAdjacentToAnalyze);
    edgeNumber++;
    cout << "Iteration " << edgeNumber << " with weight " << iterEdge->weight << endl;
    if(startAdjacentToAnalyze->minDistance == -1){
      startAdjacentToAnalyze->minDistance = iterEdge->weight;
      startAdjacentToAnalyze->previousVertex = startVertex;
      cout << startAdjacentToAnalyze->id << ": minDistance: " << startAdjacentToAnalyze->minDistance << endl;
    }
    else if((startAdjacentToAnalyze->minDistance)>(startVertex->minDistance + iterEdge->weight)){
      startAdjacentToAnalyze->minDistance = startVertex->minDistance + iterEdge->weight;
      startAdjacentToAnalyze->previousVertex = startVertex;
      cout << startAdjacentToAnalyze->id << ": minDistance: " << startAdjacentToAnalyze->minDistance << endl;
    }
     iterEdge++;
  }


  while(!graphToTraverse.isSolved){
    // cout << "goes into loop" << endl;
    graph::vertex *vertexToAnalyze;
    graph::vertex *adjacentToAnalyze;
    int updatingWeights;
    string *edgeName;
    cout << "deleteMin returned: " << dijkstraHeap.deleteMin(edgeName, &updatingWeights, &vertexToAnalyze) << endl;
    //cout << "vertexToAnalyze address: " << vertexToAnalyze << endl;
    //cout << "vertexToAnalyze's id before loop: " << (static_cast<graph::vertex *> (vertexToAnalyze))->id << endl;
    // if(static_cast<graph::vertex *> (vertexToAnalyze)->isDefined){
    //   graphToTraverse.isSolved = true;
    //   return;
    // }
    if(!(static_cast<graph::vertex *> (vertexToAnalyze)->isDefined)){
      static_cast<graph::vertex *> (vertexToAnalyze)->isDefined = true;
      for(std::list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();){
        adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
        // cout << edgeNumber << adjacentToAnalyze->id << adjacentToAnalyze->isDefined << adjacentToAnalyze->minDistance << endl;
        dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, adjacentToAnalyze);
        // cout << "address insert should have inserted: " << adjacentToAnalyze << endl;
        cout << "Iteration " << edgeNumber << " with weight " << iterEdge->weight << endl;
        edgeNumber++;
        if(adjacentToAnalyze->minDistance == -1){
          adjacentToAnalyze->minDistance = (static_cast<graph::vertex *> (vertexToAnalyze))->minDistance + iterEdge->weight;
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
          cout << (static_cast<graph::vertex *> (adjacentToAnalyze->previousVertex))->id;
          cout << adjacentToAnalyze->id << ": minDistance: " << adjacentToAnalyze->minDistance << endl;
        }
        else if((adjacentToAnalyze->minDistance) > ((static_cast<graph::vertex *> (vertexToAnalyze))->minDistance + iterEdge->weight)){
          adjacentToAnalyze->minDistance = (static_cast<graph::vertex *> (vertexToAnalyze))->minDistance + iterEdge->weight;
          adjacentToAnalyze->previousVertex = vertexToAnalyze;
          cout << (static_cast<graph::vertex *> (adjacentToAnalyze->previousVertex))->id;
          cout << adjacentToAnalyze->id << ": minDistance: " << adjacentToAnalyze->minDistance << endl;
        }
         iterEdge++;
      }
    }
    cout << "vertexToAnalyze's id after loop: " << vertexToAnalyze->id << endl;
    if(dijkstraHeap.isEmpty()){
      graphToTraverse.isSolved = true;
    }
  }
  return;
}

void outputSolvedGraph(string outputFilename, graph &solvedGraph){
  for(std::list<graph::vertex>::iterator iterVert = solvedGraph.vertices.begin(); iterVert != solvedGraph.vertices.end(); iterVert++){
    cout << iterVert->id << ": ";
    if(iterVert->isDefined){
      cout << iterVert->minDistance;
      cout << " [";
      graph::vertex *tracebackVertex;
      graph::vertex *helloVertex;
      tracebackVertex = static_cast<graph::vertex *> (iterVert->previousVertex);
      // helloVertex =
      // cout << tracebackVertex->id;
      while(tracebackVertex){
        cout << tracebackVertex->id << ", ";
        tracebackVertex = (static_cast<graph::vertex *> (tracebackVertex->previousVertex));
      }
      cout << iterVert->id;
      cout << "]" << endl;
    }
    else{
      cout << "NO PATH" << endl;
    }
  }
}

int main(){
  clock_t checkStartTime, checkEndTime;
  double checkTime;
  string inputFilename, outputFilename;
  graph dijkstraGraph(1000);
  string startVertex = "";

  // cout << "Enter name of graph file: ";
  // cin >> inputFilename;
  // loadGraph(inputFilename, dijkstraGraph);
  // while(!dijkstraGraph.contains(startVertex)){
  //   cout << "Enter a valid vertex id for the starting vertex: ";
  //   cin >> startVertex;
  // }
  // cout << "Enter name of output file: ";
  // cin >> outputFilename;

  //DELETE WHEN FINISHED
  inputFilename = "graph.txt";
  startVertex = "v1";
  outputFilename = "output.txt";
  loadGraph(inputFilename, dijkstraGraph);


  checkStartTime = clock();
  dijkstra(dijkstraGraph, startVertex);
  checkEndTime = clock();
  checkTime = ((double) (checkEndTime - checkStartTime)) / CLOCKS_PER_SEC;

  outputSolvedGraph(outputFilename, dijkstraGraph);

  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << checkTime << endl;

  return 0;
}
