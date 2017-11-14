//Rafi Mueen
//DSA Assignment 4
//Modified from DSA Assignment 3 for Heap Implementation

#include <iostream>
#include "hash.h"

using namespace std;

// Inserts the specified key into the hash table by analyzing occupied entries via
// hashing and then linearly probing in the data vector. It determines if the key
// to be inserted is already listed in the vector, either as a deleted element (in
// which case the function will return 0 and change the isDeleted flag to false) or
// not deleted (in which case the function will return return 1). If the key is not
// listed in the hash table, it inserts it at the closest unoccupied vector slot.
// After the insertion, the function calls the rehash function if the occupied
// portion of the hashtable becomes too large.
int hashTable::insert(const std::string &key, void *pv){
  int positionCandidate = hash(key);

  while(data[positionCandidate].isOccupied){
    if(data[positionCandidate].key == key){
      if(data[positionCandidate].isDeleted){
        data[positionCandidate].isDeleted = false;
        data[positionCandidate].pv = pv;
        return 0;
      }
      else
        return 1;
    }
    else{
      if(positionCandidate == (capacity-1)){
        positionCandidate = 0;
      }
      else{
        positionCandidate++;
      }
    }
  }

  data[positionCandidate].key = key;
  data[positionCandidate].isOccupied = true;
  data[positionCandidate].isDeleted = false;
  data[positionCandidate].pv = pv;
  filled++;

  if((2*filled) > capacity){
    if(!rehash())
      return 2;
  }

  return 0;
}

// Determines if the specified key is in the hashtable by calling the findPos
// function. If the findPos function returns anything other than -1, this function
// will return true. Otherwise, the return is false.
bool hashTable::contains(const std::string &key){
  if(findPos(key) != -1){
    return true;
  }
  return false;
}

// Retrieves the pointer associated with the specified key (if it exists) by
// calling the findPos function. If the findPos function returns anything other
// than -1, this function will return the pointer associated with the key and mark
// the boolean passed to it as true. Otherwise, it marks the boolean as false and
// returns the NULL pointer.
void *hashTable::getPointer(const std::string &key, bool *b){
  int keyPosition = findPos(key);
  if(keyPosition == -1){
    *b = false;
    return NULL;
  }
  *b = true;
  return data[keyPosition].pv;
}

// Sets the pointer field for the vector element associated with the specified key
// (if it exists) by using the findPos function. If the findPos function returns
// anything other than -1, this function will set the pointer field of the vector
// element to the pointer value passed to it and return 0. Otherwise, it returns 1.
int hashTable::setPointer(const std::string &key, void *pv){
  int keyPosition = findPos(key);
  if(keyPosition == -1){
    return 1;
  }
  data[keyPosition].pv = pv;
  return 0;
}

// "Removes" the vector element associated with the specified key by using the
// findPos function. If the key is not associated with any element (findPos returns
// -1) in the vector, then the function returns false. If the findPos returns a
// value other than -1, the function retrieves the element at the corresponding
// position in the vector and sets its "isDeleted" field to true.
bool hashTable::remove(const std::string &key){
  int keyPosition = findPos(key);
  if(keyPosition == -1){
    return false;
  }
  data[keyPosition].isDeleted = true;
  return true;
}

// The hashing function.
int hashTable::hash(const std::string &key){
  unsigned int b    = 378551;
  unsigned int a    = 63689;
  unsigned int hash = 0;

  for(std::size_t i = 0; i < key.length(); i++){
    hash = hash * a + key[i];
    a = a * b;
  }
  return hash%capacity;
}

// Retrieves the position of the vector element associated with the specified key.
// This function hashes the input key and attempts to search for a match with the
// specified key if the element at the position specified by the hashing function
// is occupied. If the function does not find a match at first, it linearly probes
// the vector element by iterating its position until it reaches a match, at which
// point it returns the value of the position it reached the match. If the position
// counter iterates to the capacity of the vector, it is set to 0, at which point
// it proceeds to iterate until it finds a match.
int hashTable::findPos(const std::string &key){
  int currentPosition = hash(key);

  while(data[currentPosition].isOccupied){
    if(data[currentPosition].key == key && !data[currentPosition].isDeleted){
      return currentPosition;
    }
    else{
      if(currentPosition == (capacity-1)){
        currentPosition = 0;
      }
      else{
        currentPosition++;
      }
    }
  }

  return -1;
}

// Rehashes the hashtable by using the insert function and copying over old data to
// a resized vector. The capacity of the new table is set after checking if the
// current table is a valid size, after which a new prime number is fetched using
// the getPrime function that is twice the size of the current capacity. The
// current data vector is duplicated, then each non deleted element of the
// duplicated vector is reinserted using the eponymous member function to a resized
// data vector (sized according to the prime returned by getPrime).
bool hashTable::rehash(){
  if(capacity == 0)
    return false;
  vector<hashItem> transferData = data;
  int oldCapacity = capacity;
  capacity = getPrime(2*capacity);
  data.resize(capacity);
  filled = 0;

  for(int i = 0;i<capacity;i++){
    data[i].key = "";
    data[i].isOccupied = false;
    data[i].isDeleted = false;
  }

  for(int i=0;i<oldCapacity;i++){
    if(transferData[i].isOccupied && !transferData[i].isDeleted)
      insert(transferData[i].key, transferData[i].pv);
  }

  return true;
}

// Returns a prime larger than the size requested in the argument. Uses a for loop
// to iterate through an array until a prime larger than the argument is found.
unsigned int hashTable::getPrime(int size){
  static unsigned int primes[] = {60493, 115249, 319993, 524287, 999331, 1046527};
  int i = 0;
  while(primes[i] < size){
    i++;
  }
  return primes[i];
}

// Constructor that sets all properties associated with the hashtable. Sets the
// capacity of the table to the value returned by getPrime when its argument is set
// to the size passed to the constructor, proceeds to resize the data vector to the
// same size, sets the number of slots filled in the table to 0, and resets all
// fields for every element in the data vector.
hashTable::hashTable(int size){
  capacity = getPrime(size);
  data.resize(capacity);
  filled = 0;

  for(int i=0;i<capacity;i++){
    data[i].key = "";
    data[i].isOccupied = false;
    data[i].isDeleted = false;
  }
}
