//
//  matrix.cpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#include "matrix.hpp"

// default constructed matrix is a 4x4 identity matrix
// i is the row, j is the column
Matrix4::Matrix4() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            elements[i][j] = (i == j) ? 1 : 0;
        }
    }
}

// ------ matrix multiplication helper functions ------- //
/* multiply a matrix row by a vector */
double Matrix4::multiplyRow(double *row, Point p) {
    double a = row[0] * p.x;
    double b = row[1] * p.y;
    double c = row[2] * p.z;
    double d = row[3] * p.w;
    
    return a + b + c + d;
}

/* multiply a matrix row by a matrix column */
double Matrix4::multiplyRow(double *row, Matrix4 &m, int column) {
    double a = row[0] * m.elements[0][column];
    double b = row[1] * m.elements[1][column];
    double c = row[2] * m.elements[2][column];
    double d = row[3] * m.elements[3][column];
    
    return a + b + c + d;
}


// ------- public functions ------ //

/* set a value in the matrix manually */
void Matrix4::set(int i, int j, double value) {
    elements[i][j] = value;
}

/* print matrix elements to stdout - for debugging */
void Matrix4::print() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << elements[i][j] << ' ';
        }
        cout << endl;
    }
}


/** 
 overloaded multiplication operator "*"
 multiply 2 matrices
 returns a new matrix 
 */
Matrix4 Matrix4::operator*(Matrix4 multiplicand) {
    Matrix4 m;
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m.elements[i][j] = multiplyRow(elements[i], multiplicand, j);
        }
    }

    return m;
}

/**
 overloaded multiplication operator "*"
 multiply a matrix and a homogeneous point
 returns a new homogeneous point
 */
Point Matrix4::operator*(Point multiplicand) {
    double x = multiplyRow(elements[0], multiplicand);
    double y = multiplyRow(elements[1], multiplicand);
    double z = multiplyRow(elements[2], multiplicand);
    double w = multiplyRow(elements[3], multiplicand);
    
    return Point(x, y, z, w);
}

// ------- constructors for transformation matrices ------ //
Scale4::Scale4(double sx, double sy, double sz) : Matrix4() {
    elements[0][0] = sx;
    elements[1][1] = sy;
    elements[2][2] = sz;
}

Translate4::Translate4(double tx, double ty, double tz) : Matrix4() {
    elements[0][3] = tx;
    elements[1][3] = ty;
    elements[2][3] = tz;
}

Rotate4::Rotate4(double angle, char axis) : Matrix4() {
    double c = cos(angle);
    double s = sin(angle);
    
    switch (axis) {
        case 'x':
        case 'X':
            elements[1][1] = c;
            elements[1][2] = -s;
            elements[2][1] = s;
            elements[2][2] = c;
            break;
        case 'y':
        case 'Y':
            elements[0][0] = c;
            elements[0][2] = s;
            elements[2][0] = -s;
            elements[2][2] = c;
            break;
        case 'z':
        case 'Z':
            elements[0][0] = c;
            elements[0][1] = -s;
            elements[1][0] = s;
            elements[1][1] = c;
            break;
        default:
            break;
    }
}

// transforms 1 coordinate system into another
R4::R4(Point rx, Point ry, Point rz) : Matrix4() {
    Point nx = rx.normalize();
    Point ny = ry.normalize();
    Point nz = rz.normalize();

    elements[0][0] = nx.x;
    elements[0][1] = nx.y;
    elements[0][2] = nx.z;
    elements[1][0] = ny.x;
    elements[1][1] = ny.y;
    elements[1][2] = ny.z;
    elements[2][0] = nz.x;
    elements[2][1] = nz.y;
    elements[2][2] = nz.z;
}

// shears against the z-axis only
Shear4::Shear4(double shx, double shy) : Matrix4() {
    elements[0][2] = shx;
    elements[1][2] = shy;
}

PerspProject4::PerspProject4(double d) : Matrix4() {
    elements[3][3] = 0;
    elements[3][2] = 1 / d;
}

OrthProject4::OrthProject4() : Matrix4() {
    elements[2][2] = 0;
}
