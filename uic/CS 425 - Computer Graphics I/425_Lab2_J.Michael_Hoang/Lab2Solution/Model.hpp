//
//  model.hpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/18/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#ifndef model_hpp
#define model_hpp

#include <vector>
#include <cmath>
#include <iostream>
#include "matrix.hpp"
#include "point.hpp"

using namespace std;

class Model {
protected:
    vector<Point> vertexList;
    vector<vector<int> > faceList;
    Point origin;
    
public:
    // constructors
    Model();
    Model(vector<Point> vertices);
    Model(vector<Point> vertices, vector<vector<int> > faces);
    
    vector<vector<Point> > getFaceVertices();

    void addModel(Model &m);
    void setOrigin(double, double, double);
    void localTransform(Matrix4 m);
    void transform(Matrix4 m);
    
    void draw();
    void print();
};

class Prism : public Model {
public:
    Prism(int numSides, float r1, float r2, float h);
};

class Box : public Model {
public:
    Box(float w, float h, float l);
};


#endif /* model_hpp */
