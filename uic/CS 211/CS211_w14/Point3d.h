// use the #ifndef to stop any redeclaration of the Point3d class
#ifndef POINT3D_CLASS_BY_TROY
#define POINT3D_CLASS_BY_TROY

#include "Point2d.h"

class Point3d : public Point2d
{
 private:
   // Only the Z coordinate since the X and Y coordinates are inherited
   int z;

 public:
   Point3d (int px, int py, int pz);
   Point3d ();

   void setZ (int pz);
   int getZ() const;

   void setXYZ ( int px, int py, int pz);
   double distanceFrom (Point3d pt) const;
   char* toStr(char* buf) const;
}; 

#endif
