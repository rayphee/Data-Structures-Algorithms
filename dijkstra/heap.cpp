//Rafi Mueen
//DSA Assignment 5
//Modified from DSA Assignment 4 for Dijkstra Implementation

#include <iostream>
#include <cmath>
#include <algorithm>
#include "heap.h"

using namespace std;

// insert function: first determines if the heap is filled; if so, the function
// returns 1. If the string "id" passed to it is already in the heap, the function
// returns 2 after evaluating the boolean returned by the getPointer method from
// the hashTable class. Once the criteria for a valid insert is met, the function
// sets the fields for each data node to their appropriately passed values.
// Afterwards, the percolateUp functionis called to re-establish heap order and
// the filled property of this class is updated to reflect the change.
int heap::insert(const std::string &id, int key, void *pv){
  bool b;
  node *pn = static_cast<node *> (mapping->getPointer(id, &b));
  if(heapCapacity == filled){
    return 1;
  }
  else if(b){
    return 2;
  }
  data[filled+1].id = id;
  data[filled+1].key = key;
  data[filled+1].pData = pv;
  mapping->insert(id, &data[filled+1]);
  percolateUp(filled+1);

  filled++;
  return 0;
}

// setKey function: checks first to see if the hashTable map has a valid pointer
// to the appropriate heap node. If not, the function returns 1. However, if the
// boolean passed by the getPointer method is true, the pointer recovered is
// dereferenced, the key extracted, and the value set to the integer passed to the
// function.
int heap::setKey(const std::string &id, int key){
  bool b;
  node *nodeInQuestion = static_cast<node *> (mapping->getPointer(id, &b));
  if(!b){
    return 1;
  }
  nodeInQuestion->key = key;
  whichPercolate(getPos(nodeInQuestion));
  return 0;
}

// deleteMin function: first checks to see if the heap is filled or not; if so,
// the function returns 1. However, if the heap is nonempty, the appropriate
// variables passed to the function are set to the values associated with the root
// of the heap (denoted by data element 1). Afterwards, the percolateDown function
// is called to re-establish heap order and the filled property of this class is
// updated to reflect the change.
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
  if(filled == 0){
    return 1;
  }
  *pId = data[1].id;
  if(ppData){
    ppData = data[1].pData;
  }
  if(pKey){
    *pKey = data[1].key;
  }
  mapping->remove(data[1].id);
  data[1] = data[filled];
  mapping->setPointer(data[1].id, &data[1]);
  filled--;
  percolateDown(1);
  return 0;
}

// remove function: similar to the deleteMin function, but allows the user to input
// the specific node associated with the desired id to be destroyed. This is
// accomplished essentially the same way, but the node is identified by passing
// the id to the hashMap's getPointer method. This method recovers the node
// associated with the id and the process for deletion is essentially the same as
// for deleteMin.
int heap::remove(const std::string &id, int *pKey, void *ppData){
  bool b;
  node *nodeInQuestion = static_cast<node *> (mapping->getPointer(id, &b));
  if(!b){
    return 1;
  }
  int position = getPos(nodeInQuestion);
  if(pKey){
    *pKey = data[position].key;
  }
  if(ppData){
    ppData = data[position].pData;
  }
  mapping->remove(id);
  data[position] = data[filled];
  mapping->setPointer(data[position].id, &data[position]);
  filled--;
  whichPercolate(position);
  return 0;
}

// whichPercolate function: checks if the position in question has a key that does
// not obey the heap order property. If the current node key is less than its
// parent's, the percolateUp function is called. If the node's key is less than the
// keys of its children, the percolateDown function is called.
void heap::whichPercolate(int posCur){
  if(posCur > 1 && data[posCur].key < data[floor(posCur/2)].key){
    percolateUp(posCur);
  }
  else if((posCur*2 <= filled && data[posCur].key > data[2*posCur].key) || (posCur*2 + 1 <= filled && data[posCur].key > data[2*posCur+1].key)){
    percolateDown(posCur);
  }
}
// percolateUp function: first checks if the position in question can be
// percolated up in the first place; if the position is 1, the function simply
// maps the inserted node to the hashMap without any further ado. However, if the
// position is anything other than 1, the function checks the parent nodes of the
// node to see if their key values are smaller recursively. This is accomplished by
// checking the vector element that is the floor of the current position being
// percolated divided by two (a property of trees and arrays that match up
// conveniently) and updating the hashMap as neccessary for the displaced nodes.
// Once there is no more smaller key values to check against, the function maps
// the final position to the hashMap.
void heap::percolateUp(int posCur){
  if(posCur == 1){
    return;
  }
  while((data[posCur].key < data[floor(posCur/2)].key) && posCur != 1){
    node temporaryNode = data[posCur];
    data[posCur]= data[floor(posCur/2)];
    data[floor(posCur/2)] = temporaryNode;
    mapping->setPointer(data[posCur].id, &data[posCur]);
    posCur = floor(posCur/2);
  }
  mapping->setPointer(data[posCur].id, &data[posCur]);
}

// percolateDown function: first checks if the position in question can be
// percolated down in the first place; if the position is at filled, the function
// ends, as the heap is presumed to be in order. However, if the position is
// anything below filled, the function checks if there exists nodes that are
// children of the node in question. This is accomplished yet again by looking at
// positions double and double + 1 of the current position and seeing if the
// evaluated values are greater than the filled value. If one of the two values are
// at least less than filled, the function tries to determine if the lower of the
// two candidate values is equal to the filled value (this implies that the second
// value is simply too large and not in consideration). If so, this node is swapped
// and its position is destroyed. However, if the two candidate positions are less
// than the filled value, each candidate position value's respective nodes are
// visited to determine which position's key is smaller and follows a process
// similar to the previous case. This continues until there are no more candidate
// values smaller than filled, thus the heap is in order.
void heap::percolateDown(int posCur){
  if(posCur == filled){
    return;
  }
  while(2*posCur <= filled){
    if((2*posCur == filled) && (data[2*posCur].key < data[posCur].key)){
      node temporaryNode = data[posCur];
      data[posCur] = data[2*posCur];
      data[2*posCur] = temporaryNode;
      mapping->setPointer(data[posCur].id, &data[posCur]);
      mapping->setPointer(data[2*posCur].id, &data[2*posCur]);
      return;
    }
    else{
      if((data[2*posCur].key <= data[(2*posCur)+1].key) && (data[2*posCur].key < data[posCur].key)){
        node temporaryNode = data[posCur];
        data[posCur] = data[2*posCur];
        data[2*posCur] = temporaryNode;
        mapping->setPointer(data[posCur].id, &data[posCur]);
        mapping->setPointer(data[2*posCur].id, &data[2*posCur]);
        posCur = 2*posCur;
      }
      else if((data[2*posCur].key > data[(2*posCur)+1].key) && (data[(2*posCur)+1].key < data[posCur].key)){
        node temporaryNode = data[posCur];
        data[posCur] = data[(2*posCur)+1];
        data[(2*posCur)+1] = temporaryNode;
        mapping->setPointer(data[posCur].id, &data[posCur]);
        mapping->setPointer(data[(2*posCur)+1].id, &data[2*posCur+1]);
        posCur = (2*posCur)+1;
      }
      else{
        return;
      }
    }
  }
}

// getPos function: simply retrieves the position of the node specified by using
// pointer arithmetic
int heap::getPos(node *pn){
  int pos = pn - &data[0];
  return pos;
}

// Heap constructor: initializes the heap by setting properties associated with
// the heap to their desired values, allocating memory for a suitable hashMap, and
// initializing all data elements by sequentially erasing them to be primed for use.
heap::heap(int capacity){
  heapCapacity = capacity;
  data.resize(capacity+1);
  filled = 0;
  mapping = new hashTable(capacity*2);

  for(int i=0;i<capacity+1;i++){
    data[i].id = "";
    data[i].key = 0;
    data[i].pData = NULL;
  }
}
