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
    graphToLoad.insert(source, sink, cost);
  }
  inputFile.close();
}
void dijkstra(graph &graphToTraverse, string startVertex, string outputFilename){


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
  dijkstra(dijkstraGraph, startVertex, outputFilename);
  checkEndTime = clock();
  checkTime = ((double) (checkEndTime - checkStartTime)) / CLOCKS_PER_SEC;

  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << checkTime << endl;

  return 0;
}
