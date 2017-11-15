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
  graph::vertex *adjacentToAnalyze;
  int edgeNumber = 0;

  startVertex = static_cast<graph::vertex *> (graphToTraverse.getVertex(startVertexName));
  startVertex->minDistance = 0;
  startVertex->previousVertex = NULL;
  startVertex->isDefined = true;

  for(std::list<graph::edge>::iterator iterEdge = startVertex->edges.begin(); iterEdge != startVertex->edges.end();){
    adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
    cout << edgeNumber << adjacentToAnalyze->id << adjacentToAnalyze->isDefined << adjacentToAnalyze->minDistance << endl;
    dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, adjacentToAnalyze);
    cout << "address insert should have inserted: " << adjacentToAnalyze << endl;
    edgeNumber++;
    if(adjacentToAnalyze->minDistance == -1){
      adjacentToAnalyze->minDistance = iterEdge->weight;
      adjacentToAnalyze->previousVertex = startVertex;
    }
    else if((adjacentToAnalyze->minDistance)>(startVertex->minDistance + iterEdge->weight)){
      adjacentToAnalyze->minDistance = startVertex->minDistance + iterEdge->weight;
      adjacentToAnalyze->previousVertex = startVertex;
    }
     iterEdge++;
  }

  cout << "The in between area..." << endl;

  while(!graphToTraverse.isSolved){
    graph::vertex *vertexToAnalyze;
    cout << "deleteMin returned: " << dijkstraHeap.deleteMin(&edgeName, &updatingWeights, vertexToAnalyze) << endl;
    cout << "vertexToAnalyze address: " << vertexToAnalyze << endl;
    cout << "vertexToAnalyze's id before loop: " << vertexToAnalyze->id << endl;
    if(static_cast<graph::vertex *> (vertexToAnalyze)->isDefined){
      graphToTraverse.isSolved = true;
      return;
    }
    static_cast<graph::vertex *> (vertexToAnalyze)->isDefined = true;
    for(std::list<graph::edge>::iterator iterEdge = vertexToAnalyze->edges.begin(); iterEdge != vertexToAnalyze->edges.end();){
      adjacentToAnalyze = static_cast<graph::vertex *> (iterEdge->adjacentVertex);
      cout << edgeNumber << adjacentToAnalyze->id << adjacentToAnalyze->isDefined << adjacentToAnalyze->minDistance << endl;
      dijkstraHeap.insert(std::to_string(edgeNumber), iterEdge->weight, adjacentToAnalyze);
      cout << "address insert should have inserted: " << adjacentToAnalyze << endl;
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
    cout << "vertexToAnalyze's id after loop: " << vertexToAnalyze->id << endl;
  }
  return;
}

void outputSolvedGraph(string outputFilename, graph &solvedGraph){
  for(std::list<graph::vertex>::iterator iterVert = solvedGraph.vertices.begin(); iterVert != solvedGraph.vertices.end(); iterVert++){
    cout << iterVert->id << ": ";
    if(iterVert->isDefined){
      cout << iterVert->minDistance << endl;
      //MORE REVERSE PARSING HERE IS REQUIRED
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
