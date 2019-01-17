// CS 211 lab 11
//
//  Written by Pat troy

#include "Point2d.h"


   // use of class constructors to initialize the variables
   Point2d::Point2d (int px, int py)
   {
      x = px;
      y = py;
   }

   // default constructor: set point to (0, 0)
   Point2d::Point2d ( ) 
   {
      x = 0;
      y = 0;
   }


   void Point2d::setX (int px)
   {
     x = px;
   }

   int Point2d::getX() const
   {
     return x;
   }

   void Point2d::setY (int py)
   {
     y = py;
   }

   int Point2d::getY() const
   {
     return y;
   }

   void Point2d::setXY (int px, int py)
   {
      setX(px);
      setY(py);
   }

   double Point2d::distanceFrom (Point2d pt) const
   {
     double deltaX = std::abs ( 1.0 * x - pt.getX() );
     double deltaY = std::abs ( 1.0 * y - pt.getY() );

     return sqrt ( ( deltaX * deltaX ) + ( deltaY * deltaY ) ); 
   }


   // Code used for testing in Lab 10
   // Note there could be errors in this code 
   int Point2d::getQuadrant() const
   {
     // return 0 if not in a quadrant
     if ( x == 0 && y == 0 )
       return 0;
     // return 1 if both x and y are positive
     else if ( x > 0 && y > 0 )
       return 1;
     // return 2 if both x is negative and y is positive
     else if ( x < 0 && y > 0 )
       return 2;
     // return 3 if both x and y are negative
     else if ( x < 0 || y < 0 )
       return 3;
     // return 4 if both x is positive and y is negative
     else 
       return 4;
   }

   // note this is unsafe since length of buf is never verified
   char*  Point2d::toStr(char* buf) const
   {
    sprintf ( buf, "(%d, %d)", x, y);
    return buf;
   } 



