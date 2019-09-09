//
//  database.hpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
//
// Updated by Ashwini Naik - 09/30/2018

#ifndef database_hpp
#define database_hpp

#include <cmath>
#include <vector>
#include "point.hpp"
#include "Model.hpp"
using namespace std;

class Database {
    Model terminal, runway, atct, atct2, radarTower, radarDish, background, number2;
    vector<double> window;
    int frontPlane, backPlane;
    
public:
    Database();
    
    vector<Model *> objects();
    Model * radarPtr();
    Point horizonMidpt();
    
    Point initialPlanePosition();
//    Point vpn();  // this will be calculated dynamically, so it is being left out of the db
    Point vup();
    
    Point prp();
    int left();
    int right();
    int top();
    int bottom();
    int front();
    int back();
    
    int screenWidth();
    int screenHeight();
};

#endif /* database_hpp */
