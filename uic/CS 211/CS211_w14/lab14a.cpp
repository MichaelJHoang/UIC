#include "Point2d.h"
#include "Point3d.h"

#include <iostream>

using namespace std;

int main()
{
 char buffer[300];   // needed for the toStr() methods

 printf ("Showing the bytes allocated for instances:\n");
   printf ("Size_of int: %d\n", sizeof (int) );
   printf ("Size_of Point2d: %d\n", sizeof (Point2d) );
   printf ("Size_of Point3d: %d\n", sizeof (Point3d) );

 printf ("\nUsing the Point2d class\n");
   Point2d p1 ( 4, 5);
   Point2d p2 ( 2, 8);
   printf ("The distance from %s ", p1.toStr(buffer) );
   printf ("to %s ", p2.toStr(buffer) );
   printf ("is %f\n", p1.distanceFrom(p2) );
 
 printf ("\nUsing the Point3d class\n");
   Point3d p3 ( 4, 5, -2);
   Point3d p4 ( 2, 8,  9);
   printf ("The distance from %s ", p3.toStr(buffer) );
   printf ("to %s ", p4.toStr(buffer) );
   printf ("is %f\n", p3.distanceFrom(p4) );
   cout << sizeof(Point3d) << endl;
   cout << sizeof(Point2d) << endl;
 
 return 1;
}
