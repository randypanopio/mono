/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 *                    Its concrete data structure (CDT) is not expandable.  
 *                    This signifies that when this data collection becomes full,
 *                    you do not have to resize its data structure (not in this Assignment 1).  
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *
 * Author: AL and Randy Panopio
 * Last modified on: May 2024
 */

#include <cstddef>
#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;
    
// Default constructor.
MyADT::MyADT() {
    // cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
    // You can also use the above cout to figure out when this constructor is executed.
    // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

    // initalize my profileArray with null pointers
    for (unsigned int i = 0; i < MAX_ALPHA; ++i) {
        for (unsigned int j = 0; j < MAX_ELEMENTS; ++j) {
            profileArray[i][j] = nullptr;
        }
        elementCount[i] = 0;
    }   
    totalElementCount = 0;
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
    // cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
    // You can also use the above cout to figure out when this constructor is executed.
    // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

    // initalize my profileArray with null pointers
    for (unsigned int i = 0; i < MAX_ALPHA; ++i) {
        for (unsigned int j = 0; j < MAX_ELEMENTS; ++j) {
            profileArray[i][j] = nullptr;
        }
        elementCount[i] = 0;
    }   
    totalElementCount = 0;
}  

// Overloaded assignment operator - Covered in Lab 4
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) { }
	
// Destructor - Covered in Lab 3
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
    // cout << "MyADT::destructor" << endl;  // For testing purposes ...
    // You can also use the above cout to figure out when this destructor is executed.
    // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

    removeAll();
}  

// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {
    //cout << "MyADT::getElementCount executed" << endl; 
    return totalElementCount;
}


// Description: Inserts an element in the data collection MyADT.
//              Returns "true" when the insertion is successfull, otherwise "false".
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted, MyADT's class invariants are still true
//                and the appropriate elementCount has been incremented.
// Time Efficiency: O(m)
bool MyADT::insert(const Profile& newElement) {
    // cout << "MyADT::insert executed" << endl; 
    // time efficiency is O(m), as despite doing a binary search: O(logm)
    // and inserting up to the limit of the array: O(m)
    // checking the correct sort order and shifting elements: O(m)
    // the overall efficiency is O(m)

    if (search(newElement) == nullptr) { // check if profile exists before insertion
        unsigned int char_index = getCharIndex(newElement.getSearchKey());

        // check if there is available space
        if (elementCount[char_index] < MAX_ELEMENTS) {
            // insert the new element in to correct sorted order
            unsigned int sortPos = elementCount[char_index]; // assume the insert position is at the end of the current array
            // cout << "MyADT::insert initial sortPos set to: " << sortPos << endl; 

            for (unsigned int i = 0; i < elementCount[char_index]; ++i) {
                // compare on each iteration if the new element to where it should be inserted, use overloaded operators
                bool inPosition = *profileArray[char_index][i] > newElement; // sort by ascending alphabetical order (eg a->z), inverse comparison if descending (z->a)
                if (inPosition){
                    // found the correct insert position, update the insert index
                    sortPos = i;
                    break;
                }
            }
            // cout << "MyADT::insert final sortPos set to: " << sortPos << endl; 

            // shift remaining elements to the right
            // iterate from the end of current end of array and shift right
            // can assume the array is not full since we already checked if there is space in our array
            for (unsigned int i = elementCount[char_index]; i > sortPos; --i){
                // cout << "MyADT::insert shifting profile: " << profileArray[char_index][i - 1] << "at position[" << i-1 << "], to: position[" << i << "]"<< endl;
                profileArray[char_index][i] = profileArray[char_index][i - 1];
            }

            // finally insert the new element in the correct position
            profileArray[char_index][sortPos] = new Profile(newElement);
            elementCount[char_index]++;
            totalElementCount++;
            // cout << "MyADT::insert successfully inserted element. Below is resulting state" << endl; 
            return true;
        } 
        // else {
        //     cout << "MyADT::insert array charset: " << newElement.getSearchKey() << ", is full. Aborting insertion" << endl; 
        // }
    } 
    // cout << "MyADT::insert failed to insert profile (username):" << newElement.getUserName() << endl; 
    // profile already stored, or something went wrong, return false
    return false;
}  

// Description: Removes an element from the data collection MyADT. 
//              Returns "true" when the removal is successfull, otherwise "false".    
// Precondition: The data collection MyADT is not empty.  
// Postcondition: toBeRemoved (if found) is removed, MyADT's class invariants are still true
//                and the appropriate elementCount is decremented.
// Time Efficiency: O(m)
bool MyADT::remove(const Profile& toBeRemoved) {
    // cout << "MyADT::remove executed" << endl; 

    // get the index for the subarray
    auto char_index = getCharIndex(toBeRemoved.getSearchKey());
    if (char_index < 0 || char_index >= MAX_ALPHA) {
        return false; // Invalid character index
    }

    // iterate over the indexed inner array
    // NOTE: removal SHOULD still maintian sort order of the existing elements.
    for (unsigned int i = 0; i < elementCount[char_index]; ++i) { // iterate only up to valid 
        if (profileArray[char_index][i] != nullptr ) { // check if current ref is valid

            // compare profile using overloaded operators
            bool matchedProfile = *profileArray[char_index][i] == toBeRemoved;
            if (matchedProfile){ // check if the current is the profile we want to remove
                // Element found, deallocate memory and remove it
                // cout << "MyADT::remove profile: " << toBeRemoved.getName() << ", found! deleting." << endl; 
                delete profileArray[char_index][i];
                profileArray[char_index][i] = nullptr;

                // Shift remaining elements left. 
                // Start iterating from the position of i up to last valid open elementCount. 
                for (unsigned int j = i; j < elementCount[char_index] - 1; ++j) {
                    profileArray[char_index][j] = profileArray[char_index][j + 1];
                }

                // set the last position in array to null pointer, ensuring it will be the new open position.
                profileArray[char_index][elementCount[char_index] - 1] = nullptr;

                // Decrement counts
                elementCount[char_index]--;
                totalElementCount--;
                return true;
            }
        }
    }
    // cout << "MyADT::remove profile: " << toBeRemoved.getName() << ", failed to get removed." << endl; 
    return false; // Element not found
}  

// Description: Removes all elements from the data collection MyADT. 
// Precondition: The data collection MyADT is not empty. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
// Time Efficiency: O(m*n)
void MyADT::removeAll() {
    // cout << "MyADT::removeAll executed" << endl; 
    
    // iterate over the entire multi-dim array and deallocate memory
    // Time complexity is O(m*n) as it iterates over the alphabetic container array, then its inner contents array
    for (unsigned int i = 0; i < MAX_ALPHA; ++i) {
        for (unsigned int j = 0; j < MAX_ELEMENTS; ++j) {
            delete profileArray[i][j]; // Deallocate memory
            profileArray[i][j] = nullptr; // Set pointer to nullptr
        }
        elementCount[i] = 0;
    }
    totalElementCount = 0;
}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
// Precondition: The data collection MyADT is not empty.
// Time Efficiency: O(logm)
Profile* MyADT::search(const Profile& target) {
    // cout << "MyADT::search executed" << endl;
    // since the array is sorted by username, we can do binary search using that aparm to find element, cutting search time down to O(logm)
    // adapted from lecture's binary search pesudocode

    // initialize variables to entire length of the array for our binary search space
    int char_index = getCharIndex(target.getSearchKey());
    int low = 0;
    int high = elementCount[char_index] - 1;

    // use a while loop to resize search space
    while (low <= high) {
        // pick our middle point for binary search comparison
        int mid = low + (high - low) / 2;
        Profile* profile = profileArray[char_index][mid];

        if (profile == nullptr) {
            break; // If we encounter a null, the array elements end here
        }

        if (*profile == target) {
            // cout << "MyADT::search target: " << profile->getUserName() << ", found!" << endl; 
            return profile; // profile found
        }

        // our mid element was not our target, continue with iteration
        // bisect array in half limiting our search space in half for each iteration
        // by selecting which "half" of the sorted array our element should be in 
        if (*profile < target) { // use overloaded operator for comparison
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    // cout << "MyADT::search unable to find" << endl; 
    return nullptr;
}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
// Time Efficiency: O(m*n) iterating over the entire arrays
void MyADT::print() {
    // cout << "MyADT::print executed" << endl; 
    // our profiles should be in sorted order
    for (unsigned int i = 0; i < MAX_ALPHA; ++i) { 
        for (unsigned int j = 0; j < MAX_ELEMENTS; ++j) { 
            // if (i < 1) {
            //     cout << "profile position: [" << i << "][" << j << "]:" << endl; 
            // }
            // Print only non-null profiles
            if (profileArray[i][j] != nullptr) {
                cout << *profileArray[i][j];
            }
        }
    }
} 

// Description: Returns the correspondex index of an alphanumeric character used by the array. Helper function
// Time Efficiency: O(1)
unsigned int MyADT::getCharIndex(char c) const {
    // cout << "MyADT::getCharIndex (private) executed" << endl; 
    if (c >= 'a' && c <= 'z') {
        int ans = c - 'a'; // do bit arithmetic 
        // cout << "MyADT::getCharIndex recieved char: " << c << ", returning the value: " << ans << endl; 
        return ans;
    } else {
        throw std::invalid_argument("Passed character is not a valid alphabet letter.");
    }
}

//  End of implementation file