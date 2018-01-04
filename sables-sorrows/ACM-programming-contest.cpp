//Rafi Mueen
//DSA Assignment 6

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int globalArray[1001][1001];


void parseAndCheck(string inputFilename, string outputFilename){
  ifstream inputFile;
  inputFile.open(inputFilename.c_str());
  ofstream outputFile(outputFilename.c_str());

  if (!inputFile) {
    cerr << "Error: could not open " << inputFilename << endl;
    exit(1);
  }
  string firstLine;
  string secondLine;
  string mergedLine;
  while(!inputFile.eof()){
    getline(inputFile, firstLine);
    getline(inputFile, secondLine);
    getline(inputFile, mergedLine);
    int firstLength = firstLine.length();
    int secondLength = secondLine.length();
    int mergedLength = mergedLine.length();
    if ((firstLength + secondLength) != mergedLength){
      outputFile << "*** NOT A MERGE ***" << endl;
      continue;
    }
    memset(globalArray, 0, sizeof(globalArray));
    for (int j = 0; j <= secondLength; j++){
      for (int i = 0; i <= firstLength; i++){
        if ((i == 0) && (j == 0)){
          globalArray[i][j] = 4;
        }
        else if ((j == 0) && (firstLine[i-1] == mergedLine[i-1]) && (globalArray[i-1][j])){
          globalArray[i][j] = 1;
        }
        else if ((i == 0) && (secondLine[j-1] == mergedLine[j-1]) && (globalArray[i][j-1])){
          globalArray[i][j] = 2;
        }
        else if((firstLine[i-1] == mergedLine[i+j-1]) && (secondLine[j-1] != mergedLine[i+j-1]) && (globalArray[i-1][j] || globalArray[i][j-1])){
          globalArray[i][j] = 1;
        }
        else if ((firstLine[i-1] != mergedLine[i+j-1]) && (secondLine[j-1] == mergedLine[i+j-1]) && (globalArray[i-1][j] || globalArray[i][j-1])){
          globalArray[i][j] = 2;
        }
        else if ((firstLine[i-1] == mergedLine[i+j-1]) && (secondLine[j-1] == mergedLine[i+j-1]) && (globalArray[i-1][j] || globalArray[i][j-1])){
          globalArray[i][j] = 3;
        }
      }
    }
    if(globalArray[firstLength][secondLength]){
      if(globalArray[firstLength][secondLength] == 1){
        mergedLine[firstLength + secondLength - 1] = toupper(mergedLine[firstLength + secondLength - 1]);
      }
      else if((globalArray[firstLength][secondLength] == 3) && (secondLine[secondLength] != mergedLine[firstLength + secondLength - 1])){
        mergedLine[firstLength + secondLength - 1] = toupper(mergedLine[firstLength + secondLength - 1]);
      }
      for (int i = firstLength; i>0; i--){
        while(globalArray[i][secondLength-1] && secondLength){
          if(globalArray[i][secondLength-1] == 1){
            mergedLine[i + secondLength-2] = toupper(mergedLine[i + secondLength-2]);
          }
          else if((globalArray[i][secondLength-1] == 3) && ((secondLine[secondLength-2] != mergedLine[i + secondLength-2]) || !(globalArray[i][secondLength-2]))){
            mergedLine[i + secondLength-2] = toupper(mergedLine[i + secondLength-2]);
          }
          secondLength--;
        }
        if(globalArray[i-1][secondLength] == 1) {
          mergedLine[i + secondLength-2] = toupper(mergedLine[i + secondLength-2]);
        }
        else if((globalArray[i-1][secondLength] == 3) && (secondLine[secondLength-1] != mergedLine[i + secondLength-2])){
          mergedLine[i + secondLength-2] = toupper(mergedLine[i + secondLength-2]);
        }
      }
      outputFile << mergedLine << endl;
    }
    else{
      outputFile << "*** NOT A MERGE ***" << endl;
    }
  }
  inputFile.close();
}

// main function:
int main(){
  string inputFilename, outputFilename;

  cout << "Enter name of input file: ";
  cin >> inputFilename;
  cout << "Enter name of output file: ";
  cin >> outputFilename;

  parseAndCheck(inputFilename, outputFilename);

  return 0;
}
