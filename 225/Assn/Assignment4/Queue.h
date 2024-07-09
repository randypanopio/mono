/*
 * Queue.h
 * 
 * Description: Array-based implementation of Queue as an ADT class.
 *
 * Class Invariant: Queue maintained in FIFO order.
 * 
 * Author: Randy Panopio
 * Date of last modification: July 2024
 */

#ifndef QUEUE_H
#define QUEUE_H

template <class ElementType>
class Queue {
private:
   constexpr static unsigned int INITIAL_CAPACITY = 6;           // Constant INITIAL_CAPACITY
   ElementType* elements;                                        // pointer array of queue's elements

   unsigned int elementCount = 0;             // Number of elements in the Queue - if you need it!
   unsigned int capacity = INITIAL_CAPACITY;  // Initial capacity of the data structure (number of cells in the array)
   unsigned int frontindex = 0;               // Index of front element (next dequeued/peeked element)
   unsigned int backindex = 0;                // Index of where the next element will be enqueued 

/******* Start of Queue Public Interface *******/
public:
   // Description: Constructor
   Queue();

   // Description: Copy  Constructor
   // Time Efficiency: O(n)
   Queue(const Queue& rhs);

   // Description: Destructor
   ~Queue();

   // Description: Returns true if this Queue is empty, otherwise false.
   // Postcondition: This Queue is unchanged by this operation.
   // Time Efficiency: O(1)
   bool isEmpty() const;
   
   // Description: Inserts "newElement" at the back of this Queue 
   //              (which is not necessarily the back of this Queue's data structure) 
   //              and returns true if successful, otherwise false.
   // Time Efficiency: O(n), amortized to O(1)
   bool enqueue(ElementType & newElement);
   
   // Description: Removes (but does not return) the element at the front of this Queue 
   //              (which is not necessarily the front of this Queue's data structure).
   // Precondition: This Queue is not empty.
   // Exception: Throws EmptyDataCollectionException if this Queue is empty.   
   // Time Efficiency: O(n), amortized to O(1)
   void dequeue(); 

   // Description: Returns (but does not remove) the element at the front of this Queue
   //              (which is not necessarily the front of this Queue's data structure).
   // Precondition: This Queue is not empty.
   // Postcondition: This Queue is unchanged by this operation.
   // Exception: Throws EmptyDataCollectionException if this Queue is empty.
   // Time Efficiency: O(1)
   ElementType & peek() const;
};
/******* End of Queue Public Interface *******/
#endif