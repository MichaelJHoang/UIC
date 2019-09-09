//
//  matrix.hpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <cmath>
#include "point.hpp"

using namespace std;

struct Matrix4 {
    Matrix4();
    Matrix4 operator*(Matrix4);
    Point operator*(Point);
    void set(int i, int j, double value);
    void print();
    
    protected:
        double elements[4][4];
        double multiplyRow(double row[], Point p);
        double multiplyRow(double row[], Matrix4 &m, int column);
};

struct Scale4 : Matrix4 {
    Scale4(double sx, double sy, double sz);
};

struct Translate4 : Matrix4 {
    Translate4(double tx, double ty, double tz);
};

struct Rotate4 : Matrix4 {
    Rotate4(double angle, char axis);
};

struct R4 : Matrix4 {
    R4(Point rx, Point ry, Point rz);
};

struct Shear4 : Matrix4 {
    Shear4(double shx, double shy);
};

struct PerspProject4 : Matrix4 {
    PerspProject4(double d);
};

struct OrthProject4 : Matrix4 {
    OrthProject4();
};

#endif /* matrix_hpp */
