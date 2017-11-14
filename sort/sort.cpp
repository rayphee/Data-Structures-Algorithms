//  Rafi Mueen
//  Programming Assignment #2
//  This program parses through an input file with data to sort, sorts them,
//  and returns the result of each sort in an output file and reports the time
//  taken to sort.

// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
     exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
list<Data *> bucketArray[100000];
list<Data *> sortedList;
list<Data *>::iterator firstStageIterator;
list<Data *>::iterator placeholderIterator;
list<Data *>::iterator comparatorIterator;
list<Data *>::iterator previousComparatorIterator;
int countingArray[1000000];

inline bool stringIsGreaterThan(Data *firstObject, Data *secondObject){
  return ((firstObject->data).compare(secondObject->data));
}

inline bool stringIsGreaterThanInsertion(string firstString, string secondString){
  if (firstString.compare(secondString) >= 0){
    return true;
  }
  else{
    return false;
  }
}

void insertionSort(list<Data *> &listToSort) {
  placeholderIterator = listToSort.begin();
  placeholderIterator++;
  for(;placeholderIterator != listToSort.end(); ++placeholderIterator){
    comparatorIterator = placeholderIterator;
    previousComparatorIterator = comparatorIterator;
    previousComparatorIterator--;
    while (comparatorIterator != listToSort.begin() && (*comparatorIterator)->data < (*previousComparatorIterator)->data){
      iter_swap(previousComparatorIterator, comparatorIterator);
      comparatorIterator--;
      previousComparatorIterator--;
    }
  }
}

void bucketSort(list<Data *> &listToSort, bool large, int listSize) {
  Data *sortedArray;
  int bucketNumber, digitOffset, digitCheck, bucketIndexDigits, bucketIndex;
  list<Data *>::iterator listEnd = listToSort.end();

  if (large){
    bucketNumber = 10000;
    digitOffset = 16;
  }
  else{
    bucketNumber = 1000;
    digitOffset = 17;
  }
  for (firstStageIterator = listToSort.begin();
  firstStageIterator != listEnd; firstStageIterator++){
    digitCheck = 20;

    while (((*firstStageIterator)->data)[digitCheck] != '.'){
      digitCheck--;
    }
    bucketIndexDigits = digitCheck - digitOffset;

    if (bucketIndexDigits < 1){
      bucketArray[0].push_back(*firstStageIterator);
    }
    else{
      bucketIndex = atoi(((*firstStageIterator)->data).substr(0,bucketIndexDigits).c_str());
      bucketArray[bucketIndex].push_back(*firstStageIterator);
    }
  }
  for (int i = 1; i <= bucketNumber; i++){
    //insertionSort(bucketArray[i]);
    bucketArray[i].sort(stringIsGreaterThan);
    sortedList.splice(sortedList.end(), bucketArray[i]);
  }
  swap(sortedList, listToSort);
}

void countingSort(list<Data *> &listToSort, int listSize) {
  Data *sortedArray[listSize];

  //first stage
  for (firstStageIterator = listToSort.begin();
  firstStageIterator != listToSort.end(); firstStageIterator++){
    //all this is doing is incrementing the index which the value that the data
    //object corresponds to
    int countingIndex = 1000*atof((*firstStageIterator)->data.c_str());
    countingArray[countingIndex]++;
    sortedArray[countingIndex] = *firstStageIterator;
  }

  //second stage
  for (int assigningIndex = 0; assigningIndex < 1000000; assigningIndex++){
    while (countingArray[assigningIndex] != 0){
      sortedList.push_back(sortedArray[assigningIndex]);
      countingArray[assigningIndex]--;
    }
  }

  //third stage
  swap(sortedList,listToSort);
}

void sortDataList(list<Data *> &listToSort) {
  // Fill in this function
  int listSize = listToSort.size();
  if (listSize > 101000){
    list<Data *>::iterator firstElement = listToSort.begin();
    int listElementSize = (*firstElement)->data.size();

    if (listElementSize < 8){
      //this is T3
      countingSort(listToSort, listSize);
    }
    else {
      string firstElementDigits = (*firstElement)->data.substr(0,10);
      firstElement++;
      string secondElementDigits = (*firstElement)->data.substr(0,10);
      if (secondElementDigits == firstElementDigits){
        //this is T4
        insertionSort(listToSort);
      }
      else{
        //this is T2
        bucketSort(listToSort, true, listSize);
      }
    }
  }
  else {
    //this is T1
    bucketSort(listToSort, false, listSize);
  }
}
