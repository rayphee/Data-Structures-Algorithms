//  Rafi Mueen
//  Programming Assignment #1
//  This program parses through an input file with instructions, executes them,
//  and returns the result of each instruction in an output file.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

//This is the base abstract class "simpleList" from which "stack" and "queue"
//are derived. It includes 3 protected member functions, 2 virtual public member
//functions, 1 public function to return its name, a public data member to
//store its size, two public data members to store references to the first and
//last elements of itself, a private data member to store its name, and a
//private class to create its elements (nodes).
template <class T>
class simpleList{
protected:
  //The following protected member functions are inherited unchanged by both
  //stack and queue.

  //"insertNodeAtStart" works by accepting a data value (int, double, string) and
  //creating a new node via the private "node" class defined later in this
  //program. It works by checking to see if the current list is not empty; if it
  //is, the function sets the "firstNode" and "lastNode" properties to point to
  //the newly created node. If the list is not empty, the new node is given a
  //pointer to the old "firstNode" of the list and the list's "firstNode"
  //property is updated with the current node's location. In both cases, the
  //"listSize" property is updated for accurate referencing.
  void insertNodeAtStart(T nodeDataValue){
    node *newNode = new node(nodeDataValue);
    if (listSize==0){
      firstNode = newNode;
      lastNode = newNode;
      listSize++;
    }
    else{
      newNode->nextNode = firstNode;
      firstNode = newNode;
      listSize++;
    }
  };

  //Similar to "insertNodeAtStart", "insertNodeAtEnd" works by accepting a data
  //value (int, double, string) and creating a new node. It works by passing the
  //work to "insertNodeAtStart" if the list is empty. If the list is not,
  //however the node associated with the current "lastNode" is updated so its
  //"nextNode" pointer points to the newly created node. Finally, the list's
  //"lastNode" and "listSize" properties are updated to reflect the changes.
  void insertNodeAtEnd(T nodeDataValue){
    if (listSize==0){
      insertNodeAtStart(nodeDataValue);
    }
    else{
      node *newNode = new node(nodeDataValue);
      lastNode->nextNode = newNode;
      lastNode = newNode;
      listSize++;
    }
  };

  //"removeNodeAtStart" works by accepting no arguments and temporarily moving
  //the node associated with "firstNode" to a variable named "deleteNode". The
  //value stored in the node is then saved in another variable for returning
  //later. To complete the removal, the "nextNode" property stored in the node-
  //to-be-deleted is used to update the "firstNode" property of the list, the
  //node is deleted from memory, and the "listSize" property is updated to
  //reflect the changes.
  T removeNodeAtStart(){
    node *deleteNode = firstNode;
    T popValue = deleteNode->dataField;
    firstNode = deleteNode->nextNode;
    delete deleteNode;
    listSize--;
    return popValue;
  };

  //
private:
  string listName;
  //This "node" class definition allows a node to store the next element in the
  //sequence, store data, and initialize with the right properties.
  class node{
  public:
    node *nextNode;
    T dataField;

    //The "node" class's constructor is declared here.
    node(T passedDataValue);
  };
public:
  //"getListName" allows the private data member "listName" to be returned to
  //the outside world.
  string getListName(){
    return listName;
  };
  virtual void push(T pushDataValue) = 0;
  virtual T pop() = 0;
  node *firstNode;
  node *lastNode;
  int listSize;

  //The constructor is declared here
  simpleList(string passedListName);
};

//This constructor initializes any simpleList with the necessary properties;
//specifically, the function needs to be initialized with a name (in this case,
//stored in the private data member "listName")
template <class T>
simpleList<T>::simpleList(string passedListName){
  listSize = 0;
  firstNode = NULL;
  lastNode = NULL;
  listName = passedListName;
};

//This constructor initializes every node with a data value and sets its
//"nextNode" data member to NULL by default.
template <class T>
simpleList<T>::node::node(T passedDataValue){
  dataField = passedDataValue;
  nextNode = NULL;
};

//The "stack" class finally defines the "push" and "pop" member functions. The
//"pop" function will stay the same for both stacks and queues; the "push"
//function will use different inherited functions from simpleList, however.
//The "stack" class uses "insertNodeAtStart" to push data.
template <class T>
class stack: public simpleList<T>{
public:
  void push(T pushDataValue){
    simpleList<T>::insertNodeAtStart(pushDataValue);
  };
  T pop(){
    return simpleList<T>::removeNodeAtStart();
  };
  //This line allows the "stack" class to use the same constructor as the
  //"simpleList" class
  stack(string passedListName):simpleList<T>(passedListName){};
};

//The "queue" class also defines "push" and "pop" member functions like the
//"stack" class does. However, the "push" member function is defined using the
//inherited function "insertNodeAtEnd".
template <class T>
class queue: public simpleList<T>{
public:
  void push(T pushDataValue){
    simpleList<T>::insertNodeAtEnd(pushDataValue);
  };
  T pop(){
    return simpleList<T>::removeNodeAtStart();
  };
  //As with the "stack" class, this allows the "queue" class to use the
  //constructor already defined for the "simpleList" class.
  queue(string passedListName):simpleList<T>(passedListName){};
};

//This template function allows a new list to be created. "createListWithName"
//accepts three arguments, which determine the list's name, what type of list
//(in terms of stacks and queues), and where the list is stored (based directly
//off of the data type the list stores). Each list is stored in a C++ "list"
//defined in "main()".
template <typename T>
void createListWithName(string createListName, string listType, list<simpleList<T> *> &listOfLists){
  simpleList<T> *newList;
  if (listType == "queue"){
    newList = new queue<T>(createListName);
    listOfLists.push_front(newList);
  }
  else if (listType == "stack"){
    newList = new stack<T>(createListName);
    listOfLists.push_front(newList);
  }
};

//This template function allows easy searching of lists. "findListWithName"
//accepts two arguments: the name of the list you are trying to look for, and
//which C++ "list" it should be stored in. An iterator is used to run through
//each "simpleList" list until either the function finds a match for a list with
//the desired "simpleList" list (and returns it), or finds nothing and returns a
//NULL pointer.
template <typename T>
simpleList<T>* findListWithName(string searchListName, list<simpleList<T> *> &listOfLists){
  typename list<simpleList<T> *>::iterator it = listOfLists.begin();
  while(it != listOfLists.end()){
    simpleList<T>* s = *it;
    if(s->getListName()==searchListName){
      return s;
    }
    it++;
  }
  return NULL;
};

//"main()" is where the command parsing, input file call, output file call
//execution of command decision, and housekeeping occurs.
int main(){
  string inputFileName, outputFileName, inputUnparsedData, inputParsedData;
  list<simpleList<int> *> listOfIntegerLists;
  list<simpleList<double> *> listOfDoubleLists;
  list<simpleList<string> *> listOfStringLists;
  cout << "Enter name of input file: ";
  cin >> inputFileName;
  cout << "Enter name of output file: ";
  cin >> outputFileName;
  ifstream inputFile(inputFileName);
  ofstream outputFile(outputFileName);

  //This conditional checks to see if the data in "inputFile" leads to a valid
  //file. If not, it throws an error, saying the input file was not found.
  if (inputFile.is_open()){
    //This while loop breaks each line and sets up individual word parsing using
    //"stringstream".
    while (getline(inputFile, inputUnparsedData)){
      outputFile << "PROCESSING COMMAND: " << inputUnparsedData << endl;
      string command, list, value;
      stringstream streamyString(inputUnparsedData);
      streamyString >> inputParsedData;
      command = inputParsedData;
      streamyString >> inputParsedData;
      list = inputParsedData;
      streamyString >> inputParsedData;
      value = inputParsedData;
      //These nested conditionals split up each line into appropriate decision
      //paths so that the correct processing occurs. Each nested conditional
      //essentially sends the "list" variable to either "findListWithName"
      //or "createListName", along with the appropriate "listOfLists" and
      //"value".
      if (command == "pop"){
        if (list[0] == 'i'){
          if(findListWithName<int>(list, listOfIntegerLists)== NULL){
            outputFile << "ERROR: This name does not exist!" << endl;
          }
          else{
            if (findListWithName<int>(list, listOfIntegerLists)->listSize == 0){
              outputFile << "ERROR: This list is empty!" << endl;
            }
            else{
              outputFile << "Value popped: " << findListWithName<int>(list, listOfIntegerLists)->pop() << endl;
            }
          }
        }
        else if (list[0] == 'd'){
          if(findListWithName<double>(list, listOfDoubleLists)== NULL){
            outputFile << "ERROR: This name does not exist!" << endl;
          }
          else{
            if (findListWithName<double>(list, listOfDoubleLists)->listSize == 0){
              outputFile << "ERROR: This list is empty!" << endl;
            }
            else{
              outputFile << "Value popped: " << findListWithName<double>(list, listOfDoubleLists)->pop() << endl;
            }
          }
        }
        else if (list[0] == 's'){
          if(findListWithName<string>(list, listOfStringLists)== NULL){
            outputFile << "ERROR: This name does not exist!" << endl;
          }
          else{
            if (findListWithName<string>(list, listOfStringLists)->listSize == 0){
              outputFile << "ERROR: This list is empty!" << endl;
            }
            else{
              outputFile << "Value popped: " << findListWithName<string>(list, listOfStringLists)->pop() << endl;
            }
          }
        }
        else{
          outputFile << "ERROR: Invalid list data type entry" << endl;
        }
      }
      else{
        if (command == "create"){
          if (list[0] == 'i'){
            if(findListWithName<int>(list, listOfIntegerLists)== NULL){
              if (value == "queue"){
                createListWithName<int>(list, "queue", listOfIntegerLists);
              }
              else if (value == "stack"){
                createListWithName<int>(list, "stack", listOfIntegerLists);
              }
              else{
                outputFile << "ERROR: Invalid list type entry" << endl;
              }
            }
            else{
              outputFile << "ERROR: This name already exists!" << endl;
            }
          }
          else if (list[0] == 'd'){
            if(findListWithName<double>(list, listOfDoubleLists)== NULL){
              if (value == "queue"){
                createListWithName<double>(list, "queue", listOfDoubleLists);
              }
              else if (value == "stack"){
                createListWithName<double>(list, "stack", listOfDoubleLists);
              }
              else{
                outputFile << "ERROR: Invalid list type entry" << endl;
              }
            }
            else{
              outputFile << "ERROR: This name already exists!" << endl;
            }
          }
          else if (list[0] == 's'){
            if(findListWithName<string>(list, listOfStringLists) == NULL){
              if (value == "queue"){
                createListWithName<string>(list, "queue", listOfStringLists);
              }
              else if (value == "stack"){
                createListWithName<string>(list, "stack", listOfStringLists);
              }
              else{
                outputFile << "ERROR: Invalid list type entry" << endl;
              }
            }
            else{
              outputFile << "ERROR: This name already exists!" << endl;
            }
          }
          else{
            outputFile << "ERROR: Invalid list data type entry" << endl;
          }
        }
        else if (command == "push"){
          if (list[0] == 'i'){
            if(findListWithName<int>(list, listOfIntegerLists)== NULL){
              outputFile << "ERROR: This name does not exist!" << endl;
            }
            else{
              findListWithName<int>(list, listOfIntegerLists)->push(stoi(value));
            }
          }
          else if (list[0] == 'd'){
            if(findListWithName<double>(list, listOfDoubleLists)== NULL){
              outputFile << "ERROR: This name does not exist!" << endl;
            }
            else{
              findListWithName<double>(list, listOfDoubleLists)->push(stod(value));
            }
          }
          else if (list[0] == 's'){
            if(findListWithName<string>(list, listOfStringLists)== NULL){
              outputFile << "ERROR: This name does not exist!" << endl;
            }
            else{
              findListWithName<string>(list, listOfStringLists)->push(value);
            }
          }
          else{
            outputFile << "ERROR: Invalid list data type entry" << endl;
          }
        }
        else{
          outputFile << "ERROR: This command does not exist!" << endl;
        }
      }
    }
  }
  else{
    outputFile << "No input file with name '" << inputFileName << "' found. " <<endl;
  }
  outputFile.close();
  return 0;
}
