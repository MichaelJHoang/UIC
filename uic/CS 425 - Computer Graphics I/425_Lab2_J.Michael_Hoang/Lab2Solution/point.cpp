//
//  point.cpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#include "point.hpp"

// constructor
Point::Point() {
    x = y = z = 0;
    w = 1;
}
Point::Point(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
    w = 1;
}
Point::Point(double a, double b, double c, double d) {
    x = a;
    y = b;
    z = c;
    w = d;
}
Point::Point(Point const &p) {
    x = p.x;
    y = p.y;
    z = p.z;
    w = p.w;
}


/**
 return the difference of two points
 (intended to return a vector between two points)
 */
Point Point::operator-(Point p) {
    return Point(x - p.x, y - p.y, z - p.z, w - p.w);
}

/**
 take the inverse of a point/vector
 */
Point Point::operator-() {
    return Point(-x, -y, -z, w);
}

/**
 return the cross product of 2 vectors
 | i   j   k |
 | x   y   z |
 |p.x p.y p.z|
 */
Point Point::cross(Point p) {
    return Point(y * p.z - z * p.y, -x * p.z + z * p.x, x * p.y - y * p.x);
}


/**
 convert homogeneous point to a cartesian point
 */
Point Point::homogeneousToCartesian() {
    return Point(x / w, y / w, z / w);
};


/**
 convert a vector to length 1
 */
Point Point::normalize() {
    double length = sqrt(x * x + y * y + z * z);
    return Point(x / length, y / length, z / length, w);
};

void Point::print() {
    cout << "Point: " << x << ' ' << y << ' ' << z << ' ' << w << endl;
}
