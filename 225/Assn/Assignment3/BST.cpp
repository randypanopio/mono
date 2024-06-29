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
      // cout << "Copy Constructor Invoked"<< endl;
      if (aBST.root != nullptr) {
         // clear current tree
         clear(root);

         root = new BSTNode(*(aBST.root));
         copyTreeR(root, aBST.root); // recursively copy over the tree elements
         elementCount = aBST.elementCount; // assign the other trees count to this
      }
   }

   // Overloaded assignment (=) operator
   void BST::operator=(const BST & rhs) {
      // check if attempting to assign the same tree to itself
      // cout << "Overload (=) assignment Invoked"<< endl;
      if (this != &rhs) {
         // clear the current tree
         clear(root);

         // recursively copy over the tree elements
         if (rhs.root != nullptr) {
            root = new BSTNode(*(rhs.root));
            copyTreeR(root, rhs.root);
         } else {
            root = nullptr;
         }
         
         elementCount = rhs.elementCount; // correctly assign the other tree's count to this 
         // cout << "Overload (=) assignment completed!"<< endl;
      }
   }

   // Destructor
   BST::~BST() {
      // cout << "Destructor Invoked"<< endl;
      // frees the memory allocated of this bst when it gets deleted
      clear(root);
   }

   // helper function, clear the tree recursively
   void BST::clear(BSTNode* node) {
      if (node != nullptr) {
         clear(node->left);
         clear(node->right);
         delete node;
      }
   }

   // Helper function to copy the tree recursively
   void BST::copyTreeR(BSTNode*& newNode, BSTNode* sourceNode) {
      if (sourceNode != nullptr) {
         newNode = new BSTNode(sourceNode->element);
         copyTreeR(newNode->left, sourceNode->left);
         copyTreeR(newNode->right, sourceNode->right);
      }
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
         // create a new Node from the element and attempt to insert
         // catch the recursive functions exception and rethrow, as it has more idea of what kind of exception should be shown to the user
         // delete node when exception appears
         // otherwise I would have to recursive search if the element exists THEN throw the ElementAlreadyExistsException, but doing it this way allows me to save another O(logn) function call
         BSTNode *newNode = new BSTNode(newElement);
         try {
            bool result = insertR(newNode, root); // insert
            if (result) {
               elementCount++; // successful insert, increase count
            }
         // rethrow known exceptions            
         } catch (ElementAlreadyExistsException const&) {
            delete newNode;
            throw; 
         } catch (UnableToInsertException const&) {
            delete newNode;
            throw;
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
         if (current->element == newBSTNode->element) {
            // cout << "insertR failed: ElementAlreadyExistsException"<< endl;
            throw ElementAlreadyExistsException("Element already exists in the BST.");
         }
         // cout << "insertR failed: UnableToInsertException"<< endl;
         throw UnableToInsertException("Unable to insert element in BST. Bad Tree?");
         return false; // this will never return in this case.
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
         // cout << "exception: EmptyDataCollectionException" << endl;
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
         // cout << "exception: ElementDoesNotExistException" << endl;
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
         // cout << "exception: EmptyDataCollectionException" << endl;
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