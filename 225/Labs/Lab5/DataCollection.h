/* 
 * DataCollection.h
 *
 * Description: Implementation of a SHSL list-based DataCollection ADT class.
 * There are no class invariant!
 *
 * Author: AL
 * Date: June 2024
 */
 
#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

using std::ostream;

class DataCollection {

private:

  // Description:  Nodes for a singly-headed singly-linked list (SHSL list)
  class Node {
    public:
    int data;  // Note: "data" can be assigned any integral values.           
    Node * next = nullptr;
    Node(int theData): data(theData) {}
  };
     
  // Data member: 
  Node * head = nullptr;  // "head" is the pointer to the first node

public:

  // Description: Default constructor. Constructs a DataCollection object.
  DataCollection();

  // Description: Copy constructor creates a new DataCollection object as a 
  //              copy of an existing DataCollection object.
  DataCollection(const DataCollection & DC);

  // To do: If you have not yet implemented (overloaded) the assignment (=) operator
  //        in Lab 3, I invite you to overload this operator for this class.

  // Description: Destroys a DataCollection object, releasing heap memory.
  ~DataCollection();

  // Description: Appends "newElement" to the DataCollection.
  //              Returns true if "newElement" has been 
  //              successful appended, otherwise, false.
  void append(int newElement);

  // Description: Prepends "newElement" to the DataCollection.
  //              Returns true if "newElement" has been 
  //              successful appended, otherwise, false.
  void prepend(int newElement);
            
  // Description: Prints the content of this DataCollection "thisDC"
  //              using this format: {element1, element2, ..., elementn}.
  friend ostream & operator<<(ostream & os, const DataCollection & thisDC); 
};
#endif
