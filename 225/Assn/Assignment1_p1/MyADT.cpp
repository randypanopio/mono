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


// Profile* profilesArray[MyADT::MAX_ALPHA][5];
    
// Default constructor.
MyADT::MyADT() {
   cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
   // You can also use the above cout to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
 
   /* Put your code here */
   totalElementCount = 0;
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
   // You can also use the above cout to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

   /* Put your code here */
   totalElementCount = 0;
}  

// Overloaded assignment operator - Covered in Lab 4
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) { }
	
// Destructor - Covered in Lab 3
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above cout to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
   /* Put your code here */
   
}  

// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {
    cout << "MyADT::getElementCount executed" << endl; 
    return totalElementCount;
}


// Description: Inserts an element in the data collection MyADT.
//              Returns "true" when the insertion is successfull, otherwise "false".
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted, MyADT's class invariants are still true
//                and the appropriate elementCount has been incremented.
// Time Efficiency: O(m)
bool MyADT::insert(const Profile& newElement) {
    cout << "MyADT::insert executed" << endl; 
    // time efficiency is O(m), as despite doing a linear search O(m)
    // and another iteartion for the insertion step (with a possible resize)
    // which is another O(m), the overall efficiency is O(m)
    if (search(newElement) == nullptr){
        int char_index = getCharIndex(newElement.getSearchKey());
        // TODO replace with getlength of the inner dynamic list
        // linear insert to first open position
        for (int i = 0; i < 5; i++) {
            if (profileArray[char_index][i] == nullptr) {
                profileArray[char_index][i] = new Profile(newElement);
                elementCount[char_index]++;
                totalElementCount++;
                return true;
            }
        }
    } 
    // profile already stored, or something went wrong, return false
    return false;
}  

// Description: Removes an element from the data collection MyADT. 
//              Returns "true" when the removal is successfull, otherwise "false".    
// Precondition: The data collection MyADT is not empty.  
// Postcondition: toBeRemoved (if found) is removed, MyADT's class invariants are still true
//                and the appropriate elementCount is decremented.
// Time Efficiency: 
bool MyADT::remove(const Profile& toBeRemoved) {
    cout << "MyADT::remove executed" << endl; 
    /* Put your code here */
    return true;
}  

// Description: Removes all elements from the data collection MyADT. 
// Precondition: The data collection MyADT is not empty. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
// Time Efficiency: 
void MyADT::removeAll() {
    cout << "MyADT::removeAll executed" << endl; 
    /* Put your code here */

}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
// Precondition: The data collection MyADT is not empty.
// Time Efficiency: O(m)
Profile* MyADT::search(const Profile& target) {
    cout << "MyADT::search executed" << endl; 
    // time efficiency is O(m) as it will do a linear scan from the indexed inner array of the letter subgroup

    int char_index = getCharIndex(target.getSearchKey());
    // TODO replace with getlength of the inner dynamic list
    for (int i = 0; i < 5; i++) {
        auto profile = profileArray[char_index][i];
        // NOTE instead of comparing by pointers if they are the exact same object
        // I will assume to accept copied objects as valid, so will compare by the unique usernames
        if (profile != nullptr){
            if (target.getUserName() == profile->getUserName()){
                return profile;
            }
        }
    }
    return nullptr;
}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
// Time Efficiency: 
void MyADT::print() {
    cout << "MyADT::print executed" << endl; 
    /* Put your code here */  

} 

unsigned int MyADT::getCharIndex(char c) const {
    cout << "MyADT::getCharIndex (private) executed" << endl; 
    if (c >= 'a' && c <= 'z') {
        int ans = c - 'a'; // do bit arithmetic 
        cout << "MyADT::getCharIndex recieved char: " << c << ", returning the value: " << ans << endl; 
        return ans;
    } else {
        throw std::invalid_argument("Passed character is not a valid alphabet letter.");
    }
}

//  End of implementation file


/***

implementation attempts:
array of arrays, l1 array fixed size 26, 2nd array dynamic resizing list

insert O(m) 
index profile by first letter into l1 array, O(1)
append to end of list, O(1)
however resizing would require O(m) 


remove O(m)
index by first letter l1 array O(1)
linear scan for profile in l2 array O(m)

modify O(m)
from extending the existing search function



*/