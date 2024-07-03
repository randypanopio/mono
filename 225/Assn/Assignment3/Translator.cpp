/*
 * Translator.cpp
 * 
 * Description: An interactive Translator/Dictionary application. 
 *
 * Author: Randy Panopio
 * Last Modification Date: July 2024
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include "Dictionary.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::nothrow;
using std::getline;


// helper function to pass down to display function of dictionary
void display(WordPair& anElement) {
    cout << anElement;  
} 


// As you discover what main() does, record your understanding of the code by commenting it.
// If you do not like this main(), feel free to write your own.
// Remember, this is a test driver. Feel free to modify it as you wish!
int main(int argc, char *argv[]) {
    // instantiate a Dictionary object
    Dictionary * dictionary = new Dictionary();
    if (dictionary != nullptr) {
        // Read in the data filename the user entered at the command line.
        // Expecting at least a filename on the command line.
        if ( ( argc > 1 ) ) {
            string filename = "";
            filename = argv[1];

            string aLine = "";
            string aWord = "";
            string englishW = "";
            string translationW = "";
            string delimiter = ":";
            size_t pos = 0;
            WordPair translated;

            ifstream myfile(filename);
            // Read in the data filename the user entered at the command line.
            if (myfile.is_open()) {
                cout << "Reading from a file and inserting data into Dictionary" << endl;
                while ( getline (myfile,aLine) ) {
                    pos = aLine.find(delimiter);    
                    englishW = aLine.substr(0, pos);
                    aLine.erase(0, pos + delimiter.length());
                    translationW = aLine;
                    WordPair aWordPair(englishW, translationW);
                    
                    // Load its content (all the word pairs) into the Dictionary.
                    // insert aWordPair into "testing" using a try/catch block
                    try {
                        dictionary->put(aWordPair);
                    } catch (const ElementAlreadyExistsException& e) {
                        cout << "Exception caught: " << e.what() << endl;
                    } catch (const UnableToInsertException& e) {
                        cout << "Exception caught: " << e.what() << endl;
                    } catch (...) {
                        cout << "An unknown exception was caught." << endl;
                    }
                }
                myfile.close();

                // While not EOF
                cout << "Enter word to translate. (Ctrl+D to end):" << endl;
                string input = "";
                while (getline(cin, input)) {
                    try {
                        WordPair searchWord(input, ""); // create dummy wordpair object to search only by key
                        auto myWord = dictionary->get(searchWord);
                        // no exception found, have a valid word:
                        cout << myWord;
                    } catch (const ElementDoesNotExistException& e) {
                        cout << "***Not Found!***" << endl;
                    } catch (const EmptyDataCollectionException& e) {
                        cout << "***Dictionary constructed is empty! Check input data file.***" << endl;
                    } catch (...) {
                        cout << "An unknown exception was caught." << endl;
                    }
                }                
            } else {
                cout << "Unable to open file!" << endl;
            }            
        } else {
            cout << "Missing the data filename!" << endl;
        }            
    } else {
        cout << "Unable to create a Dictionary object!" << endl;
    }

    // Free allocated memory
    if (dictionary != nullptr) {
        delete dictionary;
    }
    cout << "End of translate program" << endl;
    return 0;
}

 
// Read in the data filename the user entered at the command line.
// Load its content (all the word pairs) into the Dictionary.
// While not EOF
//   Read the English word the user entered at the command line.
//   Translate this English word using the Dictionary object.
//   Print <English word>:<word in the other language> on the computer monitor screen.
//   If the English word was not found, print ***Not Found!*** instead.

// questions
// Q: What is the time efficiency of the display feature described above?
// ANS: In the best case, O(logn) if we can just binary search the bst tree, however if the tree insertion becomes degenerate, then it becomes O(n), as we may have to traverse the whole length of the tree (as we are only using a BST and not a self balancing tree)

// Q: Notice that there is no code actually doing the printing in the BST ADT class i.e., this BST class is totally i/o free. How can we achieve this? How is it done?
// ANS: We pass along a function that does the printing to the iteration function, and that behaviour can be modified. Since it is not the responsibility of the BST class to "print" only to go through it's elements, by implementing a function in which a function is passed, this maintains the Wall metaphor of responsibility.

// Q: Why is it advantageous to keep classes i/o free?
// ANS: With the Wall metaphor, a class should only be responsible for what is it's intended purpose. So for example the Dictionary class only handles the retrieval of information from a dictionary, and the responsibility of retrieving external data such as I/O operations should NOT be the resposibility of the dictionary class.

// Q: We know that the time efficiency of the best case scenario of inserting an element into a BST and retieving an element from a BST is O(log2 n). How can we guarantee that each BST insertion and retrieval will be done in O(log2 n)? In other words, how can you guarantee that your BST will not degenerate into a linear data structure as you insert elements into it, hence producing the worst case scenario of BST insertion with a time efficiency of O(n)? We know that one way to avoid the BST's worst case scenario would be to implement an AVL tree instead of a BST. But since we are not asked to implement an AVL, there must be another way to avoid the BST's worst case scenario.
// ANS: The way a degenerate tree gets constructed is when we are inserting elements in an increasing or decreasing order, causing a single lined tree. When we construct the tree on a random order, we avoid this problem. So the input dictionary file should be randomly arranged to avoid this problem