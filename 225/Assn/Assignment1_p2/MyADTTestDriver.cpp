/*
 * MyADTTestDriver.cpp
 *
 * Description: Test Driver for MyADT class.
 * 
 * Author: Randy Panopio
 * Modified on: May 2024 
 */

#include <cassert>
#include <iostream>
#include <iomanip>
#include "MyADT.h"
#include "Profile.h"

using std::cout;
using std::endl;
using std::setprecision;
using std::fixed;

int main() {
    // create MyADT object using default ctor
    cout << endl << "Create a valid default MyADT -> testing constructor MyADT()." << endl;
    MyADT adt = MyADT();


    // generate Profiles for testing
    Profile p1("aaa", "Alex V.", "alexv@mail.com", "January 1, 1999");
    Profile p2("aba", "Andrew K.", "andrewkv@mail.com", "January 1, 1999");
    Profile p3("aca", "Amy W.", "amyw@mail.com", "January 1, 1999");
    Profile p4("ade", "Alina T.", "alinat@mail.com", "January 1, 1999");
    Profile p5("a", "Avril K.", "avrilk@mail.com", "January 1, 1999");
    Profile p6("aza", "Andong Z.", "andongz@mail.com", "January 1, 1999");
    Profile p1_duplicate("aaa", "Alex V.", "alexv@mail.com", "January 1, 1999");

    // Test insertion
    cout << endl << "Testing insert Method" << endl;
    // insert valid profiles
    assert(adt.insert(p1) == true);
    assert(adt.insert(p2) == true);
    assert(adt.insert(p3) == true);
    assert(adt.insert(p4) == true);

    // test if p5 was correctly inserted in the correct sort order (position 0)
    assert(adt.insert(p5) == true);
    // assert()

    cout << "Insertion of 5 profiles should have all succeeded. And the array[a] is full if max length is 5" << endl;

    cout << endl << "Testing getElementCount Method" << endl;
    // Test getElementCount
    assert(adt.getElementCount() == 5);

    // attempt to insert over the maximum (5) array size
    assert(adt.insert(p6) == false);
    assert(adt.getElementCount() == 5);

    // attempt to insert a duplicate
    assert(adt.insert(p1_duplicate) == false);
    assert(adt.getElementCount() == 5);

    cout << "Additional insert method testing, and getElementCount testing completed." << endl;

    cout << endl << "Testing search Method" << endl;
    // Test search
    Profile* searchResult = adt.search(p2);
    assert(searchResult != nullptr);
    assert(searchResult->getUserName() == "aba");
    cout << "search testing completed. was able to find inserted profile p2" << endl;

    // Test removal
    cout << endl << "Testing remove Method" << endl;
    // attempt to remove valid profile
    assert(adt.remove(p3) == true);
    assert(adt.getElementCount() == 4);
    // attempt to remove a non-exitent profile
    Profile p_notinserted("zzz", "Zyke V.", "zykev@mail.com", "January 1, 1999");
    assert(adt.remove(p_notinserted) == false);
    assert(adt.getElementCount() == 4);
    cout << "remove testing completed. was able to remove profile p3, and unable to remove a non-existent profile p_notinserted, and get the correct profile count." << endl;

    // Test printing by simply calling
    cout << endl << "Testing print Method" << endl;
    adt.print();
    cout << endl << "Print should have displayed 4 profiles, in username order of: [a, aaa, aba, ade]." << endl;

    // Test removeAll
    cout << endl << "Testing removeAll Method" << endl;
    adt.removeAll();
    assert(adt.getElementCount() == 0);
    adt.print();
    cout << "removeAll testing completed. If no profiles were printed, test was succesful. MyADT has been reset to initial state." << endl;

    cout << endl << endl << "All assertions passed! MyADTTestDriver completed." << endl;
    return 0;
}