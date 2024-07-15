/* 
 * PriorityQueue.h
 *
 * Description: Priority Queue class. Uses a Min binary heap
 *
 * 
 * Author: Randy Panopio
 * Last Modification: July 2024
 *
 */

#include "PriorityQueue.h"
#include "BinaryHeap.h"
#include "EmptyDataCollectionException.h"
#include <iostream>
#include <sys/types.h>

using std::cout;
using std::endl;

// Default constructor
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue() {
    cout << "PQ default ctor invoked: " << endl; 
    // TODO update PQ to memory allocate in FIRST insertion
    heap = new BinaryHeap<ElementType>();
}

// Copy constructor
template <class ElementType>
PriorityQueue<ElementType>::PriorityQueue(const PriorityQueue& rhs) {
    cout << "PQ copy ctor invoked: " << endl; 
    heap = new BinaryHeap<ElementType>(*rhs.heap);
}


// destructor
template <class ElementType>
PriorityQueue<ElementType>::~PriorityQueue() {
    cout << "PQ destructor invoked: " << endl; 
    delete heap;
}

// Description: Returns true if this Priority Queue is empty, otherwise false.
// Postcondition: This Priority Queue is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
    return (heap->getElementCount() <= 0);
}

// Description: Inserts "newElement" in this Priority Queue and 
//              returns true if successful, otherwise false.
// Time Efficiency: O(log2 n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType & newElement) {
    cout << "Inserting element in PQ: " << newElement << endl; 
    // TODO update PQ to memory allocate in FIRST insertion
    return heap->insert(newElement);
}

// Description: Removes (but does not return) the element with the next
//              "highest" priority value from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Exception: Throws EmptyDataCollectionException if Priority Queue is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void PriorityQueue<ElementType>::dequeue() {
    try {
        heap->remove();
        cout << "Removed an element from PQ: " << endl; 
    } catch (const EmptyDataCollectionException &e) {
        throw;
    } 
}

// Description: Returns (but does not remove) the element with the next 
//              "highest" priority value from the Priority Queue.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged by this operation.
// Exception: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class ElementType>
ElementType & PriorityQueue<ElementType>::peek() const {
    try {
        auto element = heap->retrieve();
        cout << "Peeked PQ element: " << element << endl; 
        return element;
    } catch (const EmptyDataCollectionException &e) {
        throw;
    }    
}
