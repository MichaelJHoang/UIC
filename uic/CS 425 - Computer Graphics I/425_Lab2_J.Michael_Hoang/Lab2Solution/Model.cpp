//
//  model.cpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/18/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#include "model.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ---- constructors ---- //
// empty
Model::Model() {
    vertexList = {};
    faceList = {};
}

// constructor taking a vector to initialize a vertex list
Model::Model(vector<Point> vertices) {
    vertexList = vertices;
    faceList = {};
}

// constructor taking a vector to initialize a vertex list
//    and a vector of face vectors
Model::Model(vector<Point> vertices, vector<vector<int> > faces) {
    vertexList = vertices;
    faceList = faces;
}


// ---- public methods ----- //

// get faces back as vectors of vertices
vector<vector<Point> > Model::getFaceVertices() {
    vector<vector<Point> > faceVertices = {};
    
    for (vector<int> face : faceList) {
        vector<Point> newFace = {};
        for (int vert_i : face) {
            newFace.push_back(vertexList[vert_i]);
        }
        faceVertices.push_back(newFace);
    }
    
    return faceVertices;
}

// combine data with another model
void Model::addModel(Model &m) {
    int sz = vertexList.size();
    vertexList.insert(vertexList.end(), m.vertexList.begin(), m.vertexList.end());
    
    for (const vector<int> &face : m.faceList) {
        vector<int> newFace = {};
        for (int vert_i : face) {
            newFace.push_back(vert_i + sz);
        }
        faceList.push_back(newFace);
    }
}

// set origin for local transformations
void Model::setOrigin(double x, double y, double z) {
    origin = Point(x, y, z);
}

// transform locally
void Model::localTransform(Matrix4 m) {
    Matrix4 m2 = Translate4(origin.x, origin.y, origin.z) * m * Translate4(-origin.x, -origin.y, -origin.z);
    for (Point &p : vertexList) {
        p = m2 * p;
    }
}

void Model::transform(Matrix4 m) {
    for (Point &p : vertexList) {
        p = m * p;
    }
    origin = m * origin;
}

/* print model vertices to stdout - for debugging */
void Model::print() {
    cout << "vertices: " << endl;
    for (Point v : vertexList) {
        cout << '(' << v.x << ", " << v.y << ", " << v.z << ')' << endl;
    }
    
    cout << "faces: " << endl;
    for (vector<int> f : faceList) {
        cout << '{';
        for (int i : f) {
            cout << i << ' ';
        }
        cout << '}' << endl;
    }
}

// convenience constructors for common geometries
Prism::Prism(int numSides, float r1, float r2, float h) : Model() {
    float theta = 2 * M_PI / numSides;
    
    for (int i = 0; i < numSides; ++i) {
        float c = cos(theta * i);
        float s = sin(theta * i);
        vertexList.push_back(Point(r1 * c, h / 2, r1 * s));
        vertexList.push_back(Point(r2 * c, -h / 2, r2 * s));

        if (i < numSides - 1) {
            faceList.push_back(vector<int>({ 2 * i, 2 * i + 2, 2 * i + 3, 2 * i + 1 }));
        }
        else {
            faceList.push_back(vector<int>({ 2 * i, 0, 1, 2 * i + 1 }));
        }
    }
}

Box::Box(float w, float h, float l) : Model() {
    vertexList = {
        Point(-w / 2, -h / 2, -l / 2),
        Point(-w / 2, -h / 2, l / 2),
        Point(w / 2, -h / 2, l / 2),
        Point(w / 2, -h / 2, -l / 2),
        Point(-w / 2, h / 2, -l / 2),
        Point(-w / 2, h / 2, l / 2),
        Point(w / 2, h / 2, l / 2),
        Point(w / 2, h / 2, -l / 2)
    };
    
    faceList = {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 0, 1, 5, 4 },
        { 2, 3, 7, 6 }
    };
}
