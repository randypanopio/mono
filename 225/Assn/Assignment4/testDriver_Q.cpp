/*
 * testDriver_Q.cpp
 * 
 * Description: Drives the testing for A4. 
 *
 * Author: Randy Panopio
 * Last Modification Date: July 2024
 */
#include <iostream>
#include "BinaryHeap.h"
#include "EmptyDataCollectionException.h" // Include your exception header


int main() {
    // Create a BinaryHeap of integers
    BinaryHeap<int> heap;

    // Insert elements into the heap
    int elements[] = {10, 4, 5, 30, 3, 15};
    for (int elem : elements) {
        heap.insert(elem);
        std::cout << "Inserted " << elem << ", current min: " << heap.retrieve() << std::endl;
    }

    // Display the element count
    std::cout << "Heap element count: " << heap.getElementCount() << std::endl;

    // Remove elements from the heap and display the min element each time
    try {
        while (heap.getElementCount() > 0) {
            std::cout << "Min element: " << heap.retrieve() << std::endl;
            heap.remove();
        }
    } catch (const EmptyDataCollectionException& e) {
        std::cerr << e.what() << std::endl;
    }

    // Test the heap after all elements are removed
    try {
        heap.remove(); // This should throw an exception
    } catch (const EmptyDataCollectionException& e) {
        std::cerr << "Expected exception: " << e.what() << std::endl;
    }

    // Final state
    std::cout << "Heap element count after removals: " << heap.getElementCount() << std::endl;

    return 0;
}
