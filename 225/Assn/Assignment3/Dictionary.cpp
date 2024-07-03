/*
 * Dictionary.cpp
 * 
 * Description: Dictonary data collection ADT class.
 *              BST-based implementation.
 * 
 * Class invariant: Duplicated elements are not allowed.
 * 
 * Author: Randy Panopio
 * Date of last modification: July 2024
 */
 
#include "Dictionary.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;

    // Constructor and destructors
    // Default Ctor
    Dictionary::Dictionary(){
        keyValuePairs = new BST();
    }

    // copy ctor
    Dictionary::Dictionary(const Dictionary & Dictionary){
        keyValuePairs = new BST(*(Dictionary.keyValuePairs));
    }

    // overloaded assignment (=) operator
    void Dictionary::operator=(const Dictionary & rhs){
        if (this != &rhs) {
            delete keyValuePairs;
            // reuse the copy constructor of BST
            keyValuePairs = new BST(*(rhs.keyValuePairs));
        }
    }

    // destructor
    Dictionary::~Dictionary(){
        delete keyValuePairs;
    }
 
/* Dictionary Public Interface */   

    // Description: Returns the number of elements currently stored in the Dictionary.
    // Postcondition: This method does not change the Dictionary.
    // Time efficiency: O(1)
    unsigned int Dictionary::getElementCount() const {
        return keyValuePairs->getElementCount();
    }

    // Description: Puts "newElement" (association of key-value) into the Dictionary.
    // Precondition: "newElement" does not already exist in the Dictionary.
    //               This is to say: no duplication allowed.
    // Exception: Throws the exception "UnableToInsertException" 
    //            when newElement cannot be inserted in the Dictionary.  
    // Exception: Throws the exception "ElementAlreadyExistsException" 
    //            if "newElement" already exists in the Dictionary.
    // Time efficiency: O(logn) on average, O(n) worst case
    void Dictionary::put(WordPair & newElement) {
        // call insert and rethrow exceptions
        try {
            keyValuePairs->insert(newElement);
        } catch (const ElementAlreadyExistsException &e) {
            throw;
        } catch (const UnableToInsertException &e) {
            throw;
        }        
    }

    // Description: Gets "newElement" (i.e., the associated value of a given key) 
    //              from the Dictionary.
    // Precondition: Dictionary is not empty.
    // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
    // Exception: Throws the exception ElementDoesNotExistException
    //            if the key is not found in the Dictionary.
    // Postcondition: This method does not change the Dictionary.
    // Time efficiency: O(logn) on average, O(n) worst case
    WordPair & Dictionary::get(WordPair & targetElement) const {
        // call retrieve and rethrow exceptions
        try {
            return keyValuePairs->retrieve(targetElement);
        } catch (const EmptyDataCollectionException &e) {
            throw;
        } catch (const ElementDoesNotExistException &e) {
            throw;
        }        
    }

    // Description: Prints the content of the Dictionary.
    // Precondition: Dictionary is not empty.
    // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
    // Postcondition: This method does not change the Dictionary.
    // Time efficiency: O(n)
    void Dictionary::displayContent(void visit(WordPair &)) const {
        // call traverseInOrder and rethrow exceptions
        try {
            keyValuePairs->traverseInOrder(visit);
        } catch (const EmptyDataCollectionException &e) {
            throw;
        }        
    }
