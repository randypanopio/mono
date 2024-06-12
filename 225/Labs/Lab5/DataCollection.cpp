/* 
 * DataCollection.cpp
 *
 * Description: Implementation of a SHSL list-based DataCollection ADT class.
 * There are no class invariant!
 *
 * Author: AL
 * Date: June 2024
 */

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
	  

// Description: Default constructor. Constructs a DataCollection object.
DataCollection::DataCollection(){

}

// Description: Copy constructor creates a new DataCollection object as a 
//              copy of an existing DataCollection object.
DataCollection::DataCollection(const DataCollection & DC){

  head = nullptr;

  if (DC.head != nullptr){
    Node *current = DC.head;
    while (current != nullptr){
      this->append(current->data); 
      current = current->next; 
    }
  }
}

// To do: If you have not yet implemented (overloaded) the assignment (=) operator
//        in Lab 3, I invite you to overload this operator for this class.

// Description: Destroys a DataCollection object, releasing heap memory.
DataCollection::~DataCollection(){

  Node * temp = nullptr;
  for ( Node * toBeDeleted = head; toBeDeleted != nullptr; ) {
    temp = toBeDeleted->next;
    delete toBeDeleted;
    toBeDeleted = temp;
  }
  head = nullptr;
}

// Description: Appends "newElement" to the DataCollection.
//              Returns true if "newElement" has been 
//              successful appended, otherwise, false.
bool DataCollection::append(int newElement){

   // Put your code here!

}

// Description: Prepends "newElement" to the DataCollection.
//              Returns true if "newElement" has been 
//              successful appended, otherwise, false.
bool DataCollection::prepend(int newElement){
   
   // Put your code here!

}

// Description: Prints the content of this DataCollection "thisDC"
//              using this format: {element1, element2, ..., elementn}.
ostream & operator<<(ostream & os, const DataCollection & thisDC) {

  DataCollection::Node *current = thisDC.head;
  cout << "{"; 
  while (current != nullptr){
    cout << current -> data; 
    current = current -> next; 
    if (current != nullptr){
      cout << ","; 
    }
  }
  cout << "}";

  return os;

} 
