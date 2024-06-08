/*
 * Stack.cpp
 * 
 * Class Description: An inefficient implementation of a Stack using SHSL, where the push and pop occurs at the end of the SHSL, causing both operations to be O(n)
 * Class Invariants: The stack must not be empty when trying to pop or peek. The "top" of the stack is at the "end" of the SHSL
 * 
 * Author: AL and Randy Panopio
 * Last modified on: June 2024
 */

#include "Stack.h"

// Constructor
Stack::Stack() : head(nullptr) {

}

// Destructor
Stack::~Stack() {
    // iterate through all known nodes and dealloc
    while (!isEmpty()) {
        pop();
    }
}

// Push an element to the stack
void Stack::push(int value) {
    // create the internal class node, and assign its value
    StackNode* newNode = new StackNode();
    newNode->data = value;
    newNode->next = nullptr;

    // check if stack is empty, if so assign this node as its head
    if (isEmpty() && head == nullptr) {
        head = newNode;
    } else {
        // iterate from the head until reaching the top of the stack
        StackNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // assign the previous top to now point to newNode, becoming the new top
        current->next = newNode;
    }
}

// Pop an element from the stack
int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    StackNode* current = head;
    StackNode* prev = nullptr;

    // iterate until the end of the stack O(n)
    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) {
        // check if we are at the head, set it to null
        head = nullptr;
    } else {
        // unlink the previous node from current, prepare for removal
        prev->next = nullptr;
    }

    // current is now the "end" of the stack, finally remove
    int value = current->data;
    delete current;

    // return the popped val
    return value;
}

// Peek the top element of the stack
int Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }

    // start iterating from the "head" of the SHSL reaching the "top" of the Stack O(n)
    StackNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // return value of the top of the stack
    return current->data;
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return head == nullptr;
}

//  End of implementation file