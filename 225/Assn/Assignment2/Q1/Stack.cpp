/*
 * Stack.cpp
 * 
 * Class Description: 
 * Class Invariants: 
 * 
 * Author: AL and Randy Panopio
 * Last modified on: May 2024
 */


/**
Question 1 - Linked list-Based Stack ADT Class
The overall goal of this question is to implement a Stack as an ADT class using a linked-list data structure (CDT).

Careful: This Stack must have its top at the back of the linked list (as opposed to the front). This is different than the linked list-based Stack implementation we saw in our lectures where the elements were pushed at the front (head) of a SHSL list and popped from the front of this SHSL list.

We are not suggesting that locating the top of a Stack at the back (as opposed to the front) of its underlying data structure (i.e. linked list) is a particularly good way of designing your Stack ADT class since this design renders the operations of the Stack rather inefficient.

The point of the exercise is to give you an opportunity to completely design and implement a data collection ADT class using a linked list as its underlying data structure (CDT).

What You Need to Do
You are to design and implement a Stack ADT class with its underlying data structure such that it satisfies the above requirements. This data structure must be a singly headed singly linked list (SHSL list).

To get you started, you will find a partial Stack.h file in the zip file you have downloaded. You will see that the only thing this file contains is a private StackNode class with public data members. This class can be used to create a linked list. It is yet another way of creating a Node non-ADT class. Unlike the Node non-ADT class we presented in class, this StackNode class is embedded into another class.

Students who submit a linked list implementation where the top of the Stack is at the front of the linked list will receive 0 for this question.
*/
#include <cstddef>
#include <iostream>
#include <cctype>
#include "Stack.h"

using std::cout;
using std::endl;
    
// Default constructor.


//  End of implementation file