/* 
 * Stack.h
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author: Randy Panopio
 * Date: June 2024
 */
 
#include <iostream>
#include <stdexcept>

class Stack {

  private:
    
    // Description:  Nodes for a singly-linked list - Do not modify!
    class StackNode {
      public:
        int data;
        StackNode * next;
    };

    // reference to head -> which is the entry point of the stack. but NOT the top of the stack
    StackNode* head;
    // top is not tracked (could be), but it is at the end of the SHSL in this implementation

  public:
    Stack();
    ~Stack();
    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;
};