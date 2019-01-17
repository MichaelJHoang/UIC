#include "Point3d.h"

// For the Constructors call the Constructor from Point2d that will
//   take care of the most work for the Point3d class
Point3d::Point3d (int px, int py, int pz)
 : Point2d (px, py)
{
 z = pz;
}

Point3d::Point3d ()
 : Point2d ()
{
 z = 0;
}

void Point3d::setZ (int pz)
{
 z = pz;
}

int Point3d::getZ () const
{
 return z;
}

// try to use methods from the inherited class whenever possible
void Point3d::setXYZ ( int px, int py, int pz)
{
 setXY(px, py);
 setZ (pz);
}

// sometimes it is easier not to use the inherited methods
//   however, this means that code is duplicated (which is not good)
double Point3d::distanceFrom (Point3d pt) const
{
 double deltaX = std::abs ( 1.0 * getX() - pt.getX() );
 double deltaY = std::abs ( 1.0 * getY() - pt.getY() );
 double deltaZ = std::abs ( 1.0 * getZ() - pt.getZ() );

 //printf ("dX %f, dY %f, dZ %f\n", deltaX, deltaY, deltaZ);
 return sqrt ( ( deltaX * deltaX ) + 
               ( deltaY * deltaY ) + 
               ( deltaZ * deltaZ ) );
}

char* Point3d::toStr (char* buf) const
{
 sprintf ( buf, "(%d, %d, %d)", getX(), getY(), z);
 return buf;
}
