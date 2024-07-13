/*
 * testDriver_Q.cpp
 * 
 * Description: Drives the testing for A4. 
 *
 * Author: Randy Panopio
 * Last Modification Date: July 2024
 */
#include "BinaryHeap.h"
#include "BinaryHeap.cpp"
#include <iostream>
#include "EmptyDataCollectionException.h"  // Include the exception class

template class BinaryHeap<int>;

int main() {
    // Create a BinaryHeap of integers
    BinaryHeap<int> heap;

    // Insert some elements
    int elements[] = {10, 5, 3, 2, 7, 1};
    for(int i = 0; i < 6; ++i) {
        std::cout << "insert element: " << elements[i] << std::endl;
        heap.insert(elements[i]);
    }

    // Retrieve the minimum element
    try {
        std::cout << "Minimum element: " << heap.retrieve() << std::endl;
    } catch (const EmptyDataCollectionException& e) {
        std::cerr << e.what() << std::endl;
    }

    // Remove elements and print the minimum each time
    while (heap.getElementCount() > 0) {
        try {
            std::cout << "Removing element: " << heap.retrieve() << std::endl;
            heap.remove();
        } catch (const EmptyDataCollectionException& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
