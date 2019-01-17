// The C Preprocessor directive of "#ifndef" means "IF Not DEFined"
//    This allows for "selective inclusion" of code based on 
//    the inclusion of a #define statement
//
//
// the #ifndef statements (2 here and 1 at the end of the .h file)
//   prevent redeclaration errors from occurring
#ifndef POINT2D_CLASS_BY_TROY
#define POINT2D_CLASS_BY_TROY
//  the above 2 lines when included basically translate to:
//    if the preprocessor constant is not defined, then define it
//    and the class specified "selective inclusion" section
//  
//  So the first time the above 2 lines are encountered, the
//    preprocessor constant and the class will get defined
//  if the 2 lines lines of code are ever encountered again,
//    the code defining the preprocessor constant AND THE CLASS
//    will be skipped, the avoid the redeclaration error

// CS 211 - Point2d Class
//
//  Written by Pat Troy

#include <cstdio>
#include <cstdarg>
#include <cmath>

class Point2d
{
  // data members are almost ALWAYS private
  private:
    // the X and Y coordinates for the point
    int x;
    int y;


  public:

   // use of class constructors to initialize the variables
   Point2d (int px, int py);
   Point2d ( ) ;

   void setX (int px);
   int getX() const;
   void setY (int py);
   int getY() const;
   void setXY (int px, int py);
   double distanceFrom (Point2d pt) const;
   int getQuadrant() const;
   char*  toStr(char* buf) const;

};

// Closing statement for the above #ifndef
#endif
