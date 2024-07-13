/* 
 * BinaryHeap.cpp
 *
 * Description: Array-based Binary Heap ADT class.
 *
 * Class Invariant:  Always a Array-based Binary Heap.
 * 
 * Author: Randy Panopio
 * Last Modification: July 2024
 *
 */  

#include <cmath>
// #include <iostream>
#include "BinaryHeap.h"  // Header file
#include "EmptyDataCollectionException.h"

// using std::cout;
// using std::endl;
  
// Constructor
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap() {
   elements = new ElementType[INITIAL_CAPACITY];
}

// Copy Constructor
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap(const BinaryHeap& rhs) : elementCount(rhs.elementCount), capacity(rhs.capacity) {
   // initialize new array
   elements = new ElementType[capacity];
   // copy over elements from other array
   for (unsigned int i = 0; i < elementCount; ++i) {
      elements[i] = rhs.elements[i];
   }
}

// Destructor
template <class ElementType>
BinaryHeap<ElementType>::~BinaryHeap() {
   delete[] elements;
}

// Description: Returns the number of elements in the Binary Heap.
// Postcondition: The Binary Heap is unchanged by this operation.
// Time Efficiency: O(1)
template <class ElementType>
unsigned int BinaryHeap<ElementType>::getElementCount() const {
   return elementCount;
}

// Description: Inserts "newElement" into the Binary Heap. 
//              It returns true if successful, otherwise false.      
// Time Efficiency: O(log2 n) Amortized, O(n) during resize operation
template <class ElementType>
bool BinaryHeap<ElementType>::insert(ElementType & newElement) {
   if (elementCount == capacity) {
      // Resize the array
      unsigned int newCapacity = capacity * 2;
      ElementType* newElements = new ElementType[newCapacity];

      // Copy elements to the new array, O(n) operation
      for (unsigned int i = 0; i < elementCount; ++i) {
         newElements[i] = elements[i];
      }

      // Delete old array and reassign elements to new array
      delete[] elements;
      elements = newElements;
      capacity = newCapacity;
      // cout << "Resized (increased) BinaryHeap's inner array to: " << capacity << endl; 
   }

   // insert new element at bottom of heap
   elements[elementCount] = newElement;
   elementCount++;
   // maintain heap invariant reheap inserted element
   reHeapUp(elementCount - 1);
   return true;
}

// Description: Removes (but does not return) the necessary element.
// Precondition: This Binary Heap is not empty.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(log2 n)
template <class ElementType>
void BinaryHeap<ElementType>::remove() {  
   if(elementCount == 0){
      // throw EmptyDataCollectionException("remove() called with an empty BinaryHeap.");
   }
   elements[0] = elements[elementCount - 1];
   elementCount--;
   
   // TODO include a resize down like Queue did, but leave alone for now

   // No need to call reheapDown() is we have just removed the only element
   if ( elementCount > 0 ) {
      reHeapDown(0);
   }
   return;
}

// Description: Retrieves (but does not remove) the necessary element.
// Precondition: This Binary Heap is not empty.
// Postcondition: This Binary Heap is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(1) 
template <class ElementType>
ElementType & BinaryHeap<ElementType>::retrieve() const {
   // analogous to peek
   if (elementCount == 0) {
      throw EmptyDataCollectionException("retrieve() called with an empty BinaryHeap.");
   }
   return elements[0];
}

// Utility methods:
// Description: Recursively put the array back into a Min Binary Heap.
template <class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned int index) { // renamed to index, indexOfRoot is misleading
   unsigned int indexOfMinChild = index;
   
   // Find indices of children.
   unsigned int indexOfLeftChild = 2 * index + 1;
   unsigned int indexOfRightChild = 2 * index + 2;

   // Base case: elements[index] is a leaf as it has no children
   if (indexOfLeftChild > elementCount - 1) {
      return;
   }

   // If we need to swap, select the smallest child
   // If (elements[index] > elements[indexOfLeftChild])
   if ( ! (elements[index] <= elements[indexOfLeftChild]) ) {
      indexOfMinChild = indexOfLeftChild;
   }      

   // Check if there is a right child, is it the smallest?
   if (indexOfRightChild < elementCount) {
      // if (elements[indexOfMinChild] > elements[indexOfRightChild])
      if ( ! (elements[indexOfMinChild] <= elements[indexOfRightChild]) ) {
         indexOfMinChild = indexOfRightChild;
      }         
   }

   // Swap parent with smallest of children.
   if (indexOfMinChild != index) {      
      ElementType temp = elements[index];
      elements[index] = elements[indexOfMinChild];
      elements[indexOfMinChild] = temp;
      
      // Recursively put the array back into a heap
      reHeapDown(indexOfMinChild);
   }
   return;
} 

template <class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned int index) {
   // Base case: we've reached the root of the heap
   if (index == 0) {
      return;
   }

   // Get the parent of this node and swap and reheap with that index
   unsigned int indexOfParent = std::floor((index - 1) / 2);
   // should be swapped and reheap if current index is not correctly in position
   if (elements[indexOfParent] > elements[index] ) {
      ElementType temp = elements[index];
      elements[index] = elements[indexOfParent];
      elements[indexOfParent] = temp;
      reHeapUp(indexOfParent);
   }
   return; // current index in correct position
}
