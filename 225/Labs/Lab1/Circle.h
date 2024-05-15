/*
* Circle.h
*
* Description: This class models a circle
* Class Invariant: "Coordinate system" of the circle uses the Cartesian (xy) plane. Area of the circle is calculated as pi*r^2
*
* Author: Randy Panopio
* Creation date: May 2025
*/

class Circle {

private: 

   // Everything that follows is private and cannot be "seen" and 
   // directly accessed from outside the class (from client code).
   // To access these private member attributes, client code needs to use the getters and setters.
  
   int xCoordinate;
   int yCoordinate;
   double radius;
   

public: 

   // Everything that follows is public and can be "seen" and directly accessed 
   // from outside the class (from client code).
   
   // Default constructor
   Circle(); 
   
   // Parameterized constructor
   // Description: Create a new Circle with the given values.
   Circle(int x, int y, double radius);
      
   // Getters return information about the Circle. 
   int getX() const;
   int getY() const;
   double getRadius () const;

   // Setters change the values of the class' member attributes.
   void move(int horizontal, int vertical);
   void setRadius(double r);
   
   // Description: Compute and return the area of "this" Circle.
   unsigned int computeArea() const;   
   
   // Description: Displays the circle's member attributes. EG: x = 0, y = 11, radius = 0.2
   void displayCircle() const;

   // Description: Checks if this circle intersects with the passed circle
   bool intersect(Circle c);

};
// End of Circle.h