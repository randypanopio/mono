/*
* Circle.cpp
*
* Description: This class models a circle
* Class Invariant: "Coordinate system" of the circle uses the Cartesian (xy) plane. Area of the circle is calculated as pi*r^2
*
* Author: Randy Panopio
* Creation date: May 2025
*/

#include <iostream>
#include "Circle.h" // header file

// logging 
using std::cout;
using std::endl;

// Now, read each of the method implementations. 
// The Circle:: preceding each method indicates that the method belongs to the Circle class. 
// If it is omitted, the compiler will attempt to create a separate function 
// (not belonging to the class). This is not what you want.

// Default constructor
// Note: This part of the constructor's header " : width(1), height(1)"
// is called the "initialization list". 
// Check what our textbook and online resources have to say about it!
Circle::Circle() : x(1), y(1), radius(1) { }

// Parameterized constructor
// Description: Create a new Circle with the given values.
Circle::Circle(int x, int y, double radius)
{
    
}

// End of the implementation file