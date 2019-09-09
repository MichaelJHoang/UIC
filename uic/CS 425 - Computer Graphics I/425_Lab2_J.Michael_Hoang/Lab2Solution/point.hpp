//
//  point.hpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#ifndef point_hpp
#define point_hpp

#include <cmath>
#include <iostream>

using namespace std;

struct Point {
    double x, y, z, w;
    Point();
    Point(double, double, double);
    Point(double, double, double, double);
    Point(Point const &);
    
    Point operator+(Point p);
    Point operator-(Point p);
    Point operator-();
    Point cross(Point p);
    
    Point homogeneousToCartesian();
    Point normalize();
    void print();
    double getW();
};

#endif /* point_hpp */
