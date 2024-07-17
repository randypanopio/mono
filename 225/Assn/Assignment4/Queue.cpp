/*
 * Queue.h
 * 
 * Description: Array-based implementation of Queue as an ADT class. 
 * Minimizes memory footprint by dynamically resizing the array during enqueue and deqeueu
 *
 * Class Invariant: Queue maintained in FIFO order.
 * 
 * Author: Randy Panopio
 * Date of last modification: July 2024
 */
#ifndef QUEUE_CPP
#define QUEUE_CPP

// #include <iostream>
#include "Queue.h"
#include "EmptyDataCollectionException.h"

// using std::cout;
// using std::endl;

// Default constructor
template <class ElementType>
Queue<ElementType>::Queue() {
    elements = new ElementType[capacity];
}

// Destructor
template <class ElementType>
Queue<ElementType>::~Queue() {
    delete[] elements;
}

// Copy constructor
template <class ElementType>
Queue<ElementType>::Queue(const Queue& rhs) {
    // allocate new array
    elements = new ElementType[capacity];
    // Copy over the data members from rhs to this queue
    elementCount = rhs.elementCount;
    capacity = rhs.capacity;
    frontindex = rhs.frontindex;
    backindex = rhs.backindex;

    // Copy over the elements from rhs to this queue
    for (unsigned int i = 0; i < elementCount; ++i) {
        // this is to copy the exact indices from the other array, maybe this is not needed?
        elements[i] = rhs.elements[(rhs.frontindex + i) % rhs.capacity];
    }
}


// Description: Inserts newElement at the back of Queue
// Time Efficiency: O(n), amortized to O(1)
template <class ElementType>
bool Queue<ElementType>::enqueue(ElementType & newElement) {
    // Check if Queue has reached capacity and do the resize algorithm
    if (elementCount == capacity) {
        // Get the new doubled size
        unsigned int doubledCapacity = capacity * 2;

        // Create the new doubled-in-size array
        ElementType* newElements = new ElementType[doubledCapacity];

        // Copy elements to the new array, O(n) operation
        for (unsigned int i = 0; i < elementCount; ++i) {
            // Insert the elements from the start of this new array (to save space)
            // and correctly start inserting from the correct "start" index of the original array        
            newElements[i] = elements[(frontindex + i) % capacity];
        }

        // Update indices
        frontindex = 0;
        backindex = elementCount;

        // Assign new capacity
        capacity = doubledCapacity;

        // Delete old array and reassign elements to new array
        delete[] elements;
        elements = newElements;
        // cout << "Resized (increased) Queue's inner array to: " << capacity << endl; 
    }

    // Proceed with the usual enqueue operation
    elementCount++;
    elements[backindex] = newElement;
    backindex = (backindex + 1) % capacity;
    return true;
}

// Description: Removes the frontmost element
// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
// Time Efficiency: O(n), Amortized to O(1)
template <class ElementType>
void Queue<ElementType>::dequeue() {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("dequeue() called with an empty Queue.");
    }
    // Decrement and update index, original operation
    elementCount--;
    frontindex = (frontindex + 1) % capacity;

    // Check if Queue needs to be resized
    if (elementCount > 0 && elementCount <= capacity / 4 && capacity > INITIAL_CAPACITY) {
        // Get max of initial vs new halved capacity, take the larger
        unsigned int newCapacity = std::max(capacity / 2, INITIAL_CAPACITY); 
        ElementType* newElements = new ElementType[newCapacity];

        // Copy elements to the new array, O(n) operation
        for (unsigned int i = 0; i < elementCount; ++i) {
            newElements[i] = elements[(frontindex + i) % capacity];
        }

        // Update indices 
        frontindex = 0;
        backindex = elementCount;

        // Update capacity
        capacity = newCapacity;

        // Delete old array and reassign elements to new array
        delete[] elements;
        elements = newElements;
        // cout << "Resized (reduced) Queue's inner array to: " << capacity << endl; 
    }
    return;
}

// Description: Returns a copy of the frontmost element
// Exceptions: Throws EmptyDataCollectionException if this Queue is empty.
template <class ElementType>
ElementType& Queue<ElementType>::peek() const {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("peek() called with an empty Queue.");
    }
    return elements[frontindex];
}

// Description: Returns true if and only if Queue empty
// Time Efficiency: O(1)
template <class ElementType>
bool Queue<ElementType>::isEmpty() const {
    return elementCount == 0;
}

#endif