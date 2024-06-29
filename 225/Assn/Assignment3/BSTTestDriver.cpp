/*
 * BSTTestDriver.cpp
 * 
 * Description: Drives the testing of the BST ADT class. 
 *
 * Author: AL
 * Last Modification Date: June 2024
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
#include "BST.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::nothrow;


void display(WordPair& anElement) {
  cout << anElement;
} 


// As you discover what main() does, record your understanding of the code by commenting it.
// If you do not like this main(), feel free to write your own.
// Remember, this is a test driver. Feel free to modify it as you wish!
int main(int argc, char *argv[]) {

  BST * testing = new(nothrow) BST();
  if (testing != nullptr) {
      
    string aLine = "";
    string aWord = "";
    string englishW = "";
    string translationW = "";
    string filename = "";
    string delimiter = ":";
    size_t pos = 0;
    WordPair translated;
	 
    // Expecting at least a filename on the command line.
    if ( ( argc > 1 ) ) {
      filename = argv[1];

      ifstream myfile(filename);
      if (myfile.is_open()) {
        cout << "Reading from a file:" << endl;  // For debugging purposes
        while ( getline (myfile,aLine) ) {
          pos = aLine.find(delimiter);    
          englishW = aLine.substr(0, pos);
          aLine.erase(0, pos + delimiter.length());
          translationW = aLine;
          WordPair aWordPair(englishW, translationW);
          
          // insert aWordPair into "testing" using a try/catch block
          try {
            testing->insert(aWordPair);
          } catch (...) {
            cout << "some exception was caught during insertion" << endl;
          }
        }
        myfile.close();

        // test the original tree:
        cout << "--------------------" << endl;
        cout << "testing traverseInOrder with original BST:" << endl;
        testing->traverseInOrder(display);
        cout << "--------------------" << endl;
        // More BST testing happening here such as:
        // Here is the hint:
        cout << "--------------------" << endl;
        cout << "****Copying one BST into another" << endl;
        BST * testing2 = new(nothrow) BST(*testing); 
        assert(testing2 != nullptr);
        cout << "testing2 is:" << endl; 
        try {
          testing2->traverseInOrder(display);
        }
        catch (EmptyDataCollectionException& anException) {
          cout << "Testing empty" << endl;
        }
        catch (ElementDoesNotExistException& anException) {
          cout << anException.what( ); // For debugging purposes
		}	 
        cout << "--------------------" << endl; 

        // More BST testing continues ...
        // manually delete the allocated BSTs 
        cout << "testing destructors of the BSTs" << endl;
        if (testing != nullptr) {
          delete testing;
        }
        if (testing2 != nullptr) {
          delete testing2;
        }
        cout << "--------------------" << endl; 
      }
      else 
        cout << "Unable to open file" << endl;
    }
    else
      cout << "Missing the data filename!" << endl;
  }
  else  
    cout << "new failed!" << endl;	

  cout << "end of program" << endl;
  return 0;
}