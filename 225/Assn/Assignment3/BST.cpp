/*
 * BST.cpp
 * 
 * Description: Binary Search Tree (BST) data collection ADT class.
 *              Link-based implementation.
 *
 * Class invariant: Duplicated elements are not allowed.
 *                  It is always a BST.
 * 
 * Author: Randy Panopio
 * Date of last modification: June 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this BST class.
// Why? Because we shall use these prototypes when creating our "marking"
// test driver. So, if our test driver cannot call the methods of you BST 
// class because the prototype of these public methods don't match, 
// we won't be able to successfully mark your assignment.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
   }
   
   // Overloaded oeprator
   // Description: Assignment (=) operator: copy (assign) "rhs" BST 
   //              object to "this" BST object such that both objects
   //              are an exact, yet independent, copy of each other.
   void BST::operator=(const BST & rhs) {

   }                
   
   // Destructor 
   BST::~BST() {
      delete root;
      root = nullptr;
   }                
   
   
/* BST Public Interface */
 
   // Description: Returns the number of elements currently stored in the BST.   
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     
      return elementCount;
   }

   // Description: Inserts an element into the BST.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the BST.
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the BST.
   // Exception: Throws the exception "UnableToInsertException" when "newElement" 
   //            cannot be inserted into the BST. 
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
      // check if tree is empty, initialize tree with this new element      
      if (root == nullptr) {
         root = new BSTNode(newElement);
         elementCount++;
      } else {
         // TODO i guess she wants us to do search and throw exception?
         // create a new Node from the element and attempt to insert
         BSTNode *newNode = new BSTNode(newElement); 
         try {

         } catch (ElementAlreadyExistsException){
            // re throw exception
         }
         if (!insertR(newNode, root)) { // call directly the recursive insert, and check result
            // unable to insert, already exist throw exception
            delete newNode;
            cout << "exception: ElementAlreadyExistsException on" << newElement.getEnglish() << endl;
            throw ElementAlreadyExistsException("Element already exists in the BST.");
         } else {
            // successful insert increase counter
            cout << "insert successful: on" << newElement.getEnglish() << endl;
            elementCount++; 
         }
      }
   } 
   
   // Description: Recursive insertion into a BST.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              BST. Otherwise, returns false.
   // Time efficiency: O(log2 n)
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
      // do binary search on which position to insert the new node
      if (newBSTNode->element < current->element) {
         // new node is less so go left of tree
         if (current->left == nullptr) {
            // empty left subtree found, insert here
            current->left = newBSTNode;
            return true;
         } else {
            // left subtree not empty, recurse
            return insertR(newBSTNode, current->left);
         }
      } else if (newBSTNode->element > current->element) {
         // new node is greater so go right of tree
         if (current->right == nullptr) {
            // empty right subtree, insert here
            current->right = newBSTNode;
            return true;
         } else {
            // right subtree not empty, recurse 
            return insertR(newBSTNode, current->right);
         }
      } else {
         // comparison failed, do not insert, duplicate found, or something catastrophic somehow happened
         throw ElementAlreadyExistsException("Element already exists in the BST.");
         cout << "insertR failed: comparison failed! duplicate almost likely found"<< endl;
         return false;
      }
   }
   
   // Description: Retrieves "targetElement" from the BST.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: BST is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the BST is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the BST.
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(log2 n)
   /* Feel free to use the provided code below.
      You can add to it, if you find it necessary to do so,
	  or you can replace it using your own implementation. */ 
   WordPair& BST::retrieve(WordPair & targetElement) const {
      if (elementCount == 0) {
         cout << "exception: EmptyDataCollectionException" << endl;
         throw EmptyDataCollectionException("BST is empty.");
      }        
     WordPair& translated = retrieveR(targetElement, root);
     return translated;
   }

   // Description: Recursive retrieval from a BST.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the BST.
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
      if (current == nullptr) {
         cout << "exception: ElementDoesNotExistException" << endl;
         throw ElementDoesNotExistException("Element does not exist in the BST.");
      } else if (targetElement < current->element) {
         return retrieveR(targetElement, current->left);
      } else if (targetElement > current->element) {
         return retrieveR(targetElement, current->right);
      } else {
         return current->element;
      }
   }  
   
   // Description: Traverses the BST in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: BST is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the BST is empty.
   // Postcondition: This method does not change the BST.
   // Time efficiency: O(n) 
   /* Feel free to use the provided code below.
      You can add to it, if you find it necessary to do so,
	  or you can replace it using your own implementation. */   
   void BST::traverseInOrder(void visit(WordPair &)) const {
      if (elementCount == 0) {
         cout << "exception: ElementDoesNotExistException" << endl;
         throw EmptyDataCollectionException("BST is empty.");
      }
      traverseInOrderR(visit, root);
      return;
   }

   // Description: Recursive "in order" traversal of a BST.   
   // Postcondition: This method does not change the BST. 
   // Time efficiency: O(n)
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
      if (current != nullptr) {
         traverseInOrderR(visit, current->left);
         visit(current->element);
         traverseInOrderR(visit, current->right);
      }
   }