/* 
 * Queue.cpp - This current version of Queue class does not work well!
 *
 * Description: Array-based implementation of Queue as an ADT class.
 *
 * Class Invariant: Queue maintained in FIFO order.
 *
 * Author: Randy Panopio
 * Date: June 2024
 */
 
#include <iostream>
#include "Queue.h"

using std::cout;
using std::endl;

// Description: Constructor
Queue::Queue() {
  // allocate memory of elements
  elements = new int[INITIAL_CAPACITY];
  // cout << "Initialized a new Queue" << endl; 
}

// Copy constructor
Queue::Queue(const Queue& rhs) {
  // allocate new array
  elements = new int[rhs.capacity];
  
  // Copy over the data members from rhs to this queue
  elementCount = rhs.elementCount;
  capacity = rhs.capacity;
  frontindex = rhs.frontindex;
  backindex = rhs.backindex;

  // Copy over the elements from rhs to this queue
  for (unsigned int i = 0; i < elementCount; ++i) {
      elements[i] = rhs.elements[(rhs.frontindex + i) % rhs.capacity];
  }
  // cout << "Initialized a new Queue copying over another Queue's elements" << endl; 
}

// Destructor
Queue::~Queue()
{
  delete[] elements;
}

// Description: Inserts newElement at the back of Queue
// Time Efficiency: O(n), amortized to O(1)
void Queue::enqueue(int newElement) {
  // check if Q has reached capacity and do the resize algorithm
  if (elementCount == capacity) {
    // get the new doubled size
    int doubledCapacity = capacity * 2;
    // create the new doubled in size array
    int* newElements = new int[doubledCapacity];

    // Copy elements to the new array, O(n) operation
    for (unsigned int i = 0; i < elementCount; ++i) {
      // insert the elements from the start of this new array (to save space)
      // and correctly start inserting from the correct "start" index of the original array        
      newElements[i] = elements[(frontindex + i) % capacity];
    }

    // Update indices
    frontindex = 0;
    backindex = elementCount;

    // assign new capacity
    capacity = doubledCapacity;

    // Delete old array and reassign elements to new array
    delete[] elements;
    elements = newElements;
    // cout << "resized (increased) Queue's inner array to: " << capacity << endl; 
  }

  // Proceed with the usual enqueue operation
  elementCount++;
  elements[backindex] = newElement;
  backindex = (backindex + 1) % capacity;
  return;
} 

// Description: Removes the frontmost element
// Precondition: Queue not empty, does not handle if Queue is empty
// Time Efficiency: O(n), Amortized to O(1)
void Queue::dequeue() {
  
  // Decremnt and update index, original operation
  elementCount--;
  frontindex = (frontindex + 1) % capacity;

  // check if Q needs to be resized
  if (elementCount > 0 && elementCount <= capacity / 4 && capacity > INITIAL_CAPACITY) {
    // get max of initial vs new halved capacity, take the larger
    unsigned int newCapacity = std::max(capacity / 2, INITIAL_CAPACITY); 
    int* newElements = new int[newCapacity];

    // Copy elements to the new array, O(n) operation
    for (unsigned int i = 0; i < elementCount; ++i) {
      newElements[i] = elements[(frontindex + i) % capacity];
    }

    // Update indices 
    frontindex = 0;
    backindex = elementCount;

    // update capacity
    capacity = newCapacity;

    // Delete old array and reassign elements to new array
    delete[] elements;
    elements = newElements;
    // cout << "resized (reduced) Queue's inner array to: " << capacity << endl; 
  }
  return;
} 

// Description: Returns a copy of the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
int Queue::peek() const {
  return elements[frontindex];    
} 

// Description: Returns true if and only if Queue empty
// Time Efficiency: O(1)
bool Queue::isEmpty() const {
  return elementCount == 0;
}

// Description: Assigns this Queue to the values of the passed in Queue
// Time Efficiency: O(n)
void Queue::operator=(const Queue &other)
{
    // Check for self-assignment
    if (this == &other) {
      return;
    }

    // Deallocate existing array
    delete[] elements;

    // Copy over the data members from other to this queue
    elementCount = other.elementCount;
    capacity = other.capacity;
    frontindex = other.frontindex;
    backindex = other.backindex;

    // Allocate new array 
    elements = new int[other.capacity];

    // Copy over the elements from other to this queue
    for (unsigned int i = 0; i < elementCount; ++i) {
      elements[i] = other.elements[(other.frontindex + i) % other.capacity];
    }
}
