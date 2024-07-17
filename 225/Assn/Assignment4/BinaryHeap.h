/* 
 * BinaryHeap.h
 *
 * Description: Array-based Binary Heap ADT class. This is a MIN binary heap.
 *
 * Class Invariant:  Always a Array-based Binary Heap.
 * 
 * Author: Randy Panopio
 * Last Modification: July 2024
 *
 */  

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

template <class ElementType>
class BinaryHeap {
private:
   constexpr static unsigned int INITIAL_CAPACITY = 6;           // Constant INITIAL_CAPACITY
   ElementType* elements;                                        // pointer array of queue's elements

   unsigned int elementCount = 0;             // Number of elements in the Queue - if you need it!
   unsigned int capacity = INITIAL_CAPACITY;  // Initial capacity of the data structure (number of cells in the array)

   // private functions
   // Helper function to heapify up (used in insert)
   void reHeapUp(unsigned int index);

   // Helper function to heapify down (used in remove)
   void reHeapDown(unsigned int index);
/******* Start of Binary Heap  Public Interface *******/	
public:
   // Description: Constructor
   BinaryHeap();

   // Description: Copy Constructor
   BinaryHeap(const BinaryHeap& rhs);

   // Description: Destructor
   ~BinaryHeap();

   // Description: Returns the number of elements in the Binary Heap.
   // Postcondition: The Binary Heap is unchanged by this operation.
   // Time Efficiency: O(1)
   unsigned int getElementCount() const;

   // Description: Inserts "newElement" into the Binary Heap. 
   //              It returns true if successful, otherwise false.      
   // Time Efficiency: O(log2 n)
   bool insert(ElementType & newElement);
      
   // Description: Removes (but does not return) the necessary element.
   // Precondition: This Binary Heap is not empty.
   // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
   // Time Efficiency: O(log2 n)
   void remove();

   // Description: Retrieves (but does not remove) the necessary element.
   // Precondition: This Binary Heap is not empty.
   // Postcondition: This Binary Heap is unchanged.
   // Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
   // Time Efficiency: O(1) 
   ElementType & retrieve() const;
};
/******* End of Binary Heap Public Interface *******/
// Include the implementation of the template class
#include "BinaryHeap.cpp"
#endif