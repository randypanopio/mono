#include <iostream>
#include <string>
#include <cctype>

using std::cout;
using std::ws;
using std::cin;
using std::endl;

class Node {
	
public:

	// Public data members - Why are the data members public?
	int data = 0;           // The data in the node
	Node * next = nullptr;  // Pointer to next node
	
	// Constructors
	Node();
	Node(int theData);
	Node(int theData, Node * theNextNode);

};

Node::Node(){ }

Node::Node(int theData): data(theData) { }

Node::Node(int theData, Node * theNextNode): data(theData), next(theNextNode) { }

unsigned int getCharIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a'; // do bit arithmetic 
    } else {
        throw std::invalid_argument("Passed character is not a valid alphabet letter.");
    }
    return 0;
}

int main() {
    cout << "\nHello World!" << endl;

    Node* profileArray[26][5];

    profileArray[0][0] = new Node(0);
    profileArray[0][1] = new Node(1);

    int char_index = 0;

    for (int i = 0; i < 5; i++) {
        auto profile = profileArray[char_index][i];
        if (profile != nullptr) {
            cout << "\nNon empty profile: "  <<  profile->data << ", at index:" << i << endl;
        } else {
            cout << "\nNull profile at index: "  << i << endl;
        }
    }


    // int a = getCharIndex('a');
    // cout << "\ngetCharIndex char a: " << a << endl;
    // int z = getCharIndex('z');
    // cout << "\ngetCharIndex char z: " << z << endl;
    // int d = getCharIndex('d');
    // cout << "\ngetCharIndex char d: " << d << endl;
    // int h = getCharIndex('h');
    // cout << "\ngetCharIndex char h: " << h << endl;    
    // int ve = getCharIndex('6');
    // cout << "\ngetCharIndex char 6: " << ve << endl;
    return 0;
}


