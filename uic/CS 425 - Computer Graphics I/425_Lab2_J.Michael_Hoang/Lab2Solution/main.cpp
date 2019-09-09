//
//  main.cpp
//  425_2_solution
//
//  Created by Kristine Lee on 10/14/17.
//  Copyright © 2017 Kristine Lee. All rights reserved.
// 
// Updated by Ashwini Naik - 09/30/2018



#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <iostream>
#include <cstdlib>

#include "Model.hpp"
#include "database.hpp"
#include "matrix.hpp"
#include "point.hpp"
using namespace std;

int t;                      // time
Database db;
vector<Model *> objects;
Point planePosition;
bool autopilot = false;     // true = smooth animation | false = move via key command

/* handle user interactions for animating screen */
void handleKeyEvent(unsigned char key, int x, int y) {
    switch (key) {
        case 27:    // ESC: exit program
            exit(0);
            break;
        case ' ':   // switch between manual and auto flight
            autopilot = !autopilot;
            break;
        case 'w':   // up
            autopilot = false;
            planePosition.y += 10;
            break;
        case 's':   // down
            autopilot = false;
            planePosition.y -= 10;
            break;
        case 'a':   // left
            autopilot = false;
            planePosition.x -= 10;
            break;
        case 'd':   // right
            autopilot = false;
            planePosition.x += 10;
            break;
        case 'f':   // forward
            autopilot = false;
            planePosition.z -= 10;
            break;
        case 'v':   // back
            autopilot = false;
            planePosition.z += 10;
            break;
        case 'r':   // reset
            autopilot = true;
            planePosition = db.initialPlanePosition();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// initialize database objects and set initial plane position
void initializeObjects() {
    planePosition = db.initialPlanePosition();
    objects = db.objects();
}

// compute the bitcode using perspective viewing volume / cohen-sutherland
int bitCode(Point p, double zmin) {
    return (p.y > -p.z)   |
        (p.y < p.z)  << 1 |
        (p.x > -p.z) << 2 |
        (p.x < p.z)  << 3 |
        (p.z < -1)   << 4 |
        (p.z > zmin) << 5;
}

// compute the bitcode using parallel viewing volume / cohen-sutherland
int bitCode(Point p) {
    if (p.w > 0) {
        return (p.y > p.w) |
        (p.y < -p.w) << 1  |
        (p.x > p.w)  << 2  |
        (p.x < -p.w) << 3  |
        (p.z < -p.w) << 4  |
        (p.z > 0)    << 5;
    }
    else {
        return (p.y < p.w) |
        (p.y > -p.w)  << 1 |
        (p.x < p.w)   << 2 |
        (p.x > -p.w)  << 3 |
        (p.z > -p.w)  << 4 |
        (p.z < 0)     << 5;
    }
}

vector<Point> clip(const vector<Point> &face) {
    vector<Point> clippedFace;
    
    // for each pair of vertices (edge endpoints)
    for (int i = 0, il = face.size(); i < il; ++i) {
        
        Point p1 = face.at(i);
        Point p2 = (i < il - 1) ? face.at(i + 1) : face.at(0);
        
        int code1 = bitCode(p1);
        int code2 = bitCode(p2);
        
        if ((code1 | code2) == 0) {
            // trivially accept
            clippedFace.push_back(p1);
            clippedFace.push_back(p2);
        }
        else if ((code1 & code2) != 0) {
            // trivially reject
        }
        else {
            // use parametric equations to get intersection w/ clipping planes
            
            Point d = p2 - p1;
            // edge = p1 + d * t
            
            // e.g., for the case x = W,
            //   edge.x = p1.x + d.x * t
            //   edge.w = p1.w + d.w * t
            // solve for t, etc....

            double t[6] = {
                (p1.y - p1.w) / (d.w - d.y),  // clip y = w
                (p1.y + p1.w) / (-d.w - d.y), // clip y = -w
                (p1.x - p1.w) / (d.w - d.x),  // clip x = w
                (p1.x + p1.w) / (-d.w - d.x), // clip x = -w
                (p1.z + p1.w) / (-d.w - d.z), // clip z = -w
                -p1.z / d.z                   // clip z = 0
            };
            
            int count = 0;
            
            Point endpt1, endpt2;
            
            // check if one of the points is already in the region
            if (code1 == 0) {
                endpt1 = p1;
                ++count;
            }
            if (code2 == 0) {
                endpt1 = p2;
                ++count;
            }
            
            // get intersection with each of the 6 planes
            for (int j = 0; j < 6; ++j) {
                if (t[j] >= 0 && t[j] <= 1) {
                    Point intersect(p1.x + t[j] * d.x, p1.y + t[j] * d.y, p1.z + t[j] * d.z, p1.w + t[j] * d.w);

                    // check if intersection is inside the view volume
                    if (bitCode(intersect) != 0 && j < 5) {
                        continue;
                    }
                    
                    if (count == 0) {
                        endpt1 = intersect;
                    }
                    else {
                        endpt2 = intersect;
                    }
                    
                    ++count;
                    if (count >= 2) {
                        // push new endpoints to face
                        clippedFace.push_back(endpt1);
                        clippedFace.push_back(endpt2);
                        break;
                    }
                }
            }
        }
    }
    
    return clippedFace;
}

/**
 Calculate the VRP as some distance from the PRP along the line of sight
 */
Point calculateVRP(Point u, Point v, Point n) {
    return Translate4(planePosition.x, planePosition.y, planePosition.z) * R4(-u, -v, n) * db.prp();
}

/**
 Calculate the "sight line" between the plane position and the horizon line
 */
Point calculateSightLine() {
    return db.horizonMidpt() - planePosition;
}


/**
 get the BIG MATRIX to transform scene vertices to perspective canonical viewing volume
 */
Matrix4 calculateNper() {
    
    // for convenience's sake, we will let the VPN be parallel
    // to the plane's line of sight (DOP), in the opposite direction
    Point sightLine = calculateSightLine();

    Point n = -sightLine.normalize();
    Point u = db.vup().cross(n).normalize();
    Point v = n.cross(u).normalize();
    
    // calculate the vrp
    Point vrp = calculateVRP(u, v, n);

    // step 1: translate vrp to origin
    Translate4 T1(-vrp.x, -vrp.y, -vrp.z);
    
    // step 2: rotate vrc to align with wcs
    R4 R(u, v, n);
    
    // step 3: translate prp to the origin
    Point prp = db.prp();
    Translate4 T2(-prp.x, -prp.y, -prp.z);
    
    // step 4: shear to align with z axis
    // (for dop parallel to vpn, the shear is 0 and this step can be skipped)
    Point cw((db.right() + db.left()) / 2, (db.top() + db.bottom()) / 2, 0);
    Point dop = cw - prp;
    Shear4 Sh(-dop.x / dop.z, -dop.y / dop.z);
    
    // step 5: scale to canonical view volume
    Point vrp2 = Sh * -prp;
    double zmax = vrp2.z + db.back();
    double sz = 2 * vrp2.z / zmax;
    
    Scale4 S(sz / ( db.right() - db.left() ), sz / ( db.top() - db.bottom() ), -1 / zmax);
    
    // get zmin for future reference
    double zmin = -(vrp2.z + db.front()) / zmax;

    // step 6: (optional) transform perspective cvv to parallel cvv
    Matrix4 M;
    M.set(2,2, 1/(1+zmin));
    M.set(2,3, -zmin/(1+zmin));
    M.set(3,2, -1);
    M.set(3,3,0);

    return M * S * Sh * T2 * R * T1;
}

/* display function draws content on the screen.
 */
void display() {
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    
    Matrix4 nper = calculateNper();
    Matrix4 projectAndScale = Scale4(db.screenWidth(), db.screenHeight(), 0);
    
    // for each object on the scene
    for (Model * obj : objects) {
        // get vertices
        vector<vector<Point> > model = obj->getFaceVertices();

        // for each face
        for (vector<Point> &face : model) {
            // 1. transform all vertices into viewing volume
            //
            // Nper only needs to be calculated ONCE per display call,
            // OUTSIDE the for loop
            for (Point &p : face) {
                p = nper * p;
            }
            
            // 2. clip to viewing volume
            //
            // NB: since I transformed Nper to the parallel cvv (Nper'),
            // this clipping must take place in HOMOGENEOUS COORDINATES.
            //
            // Otherwise, the vertices are converted to Cartesian coordinates
            // (trivial, because w = 1 for Nper) and clipped in Cartesian space
            vector<Point> clippedFace = clip(face);

            
            // 3. project to window and scale to viewport
            //
            // Again, the projection is fairly trivial with Nper'
            // (z coordinate goes to 0). For the typical Nper-derived cvv,
            // projectAndScale is Scale * Mper, where Mper is the perspective
            // projection matrix.
            //
            // Remember that the CVV shrinks our points to a
            // 1x2x2 box/pyramid so we have to scale back up to our screen size.
            glBegin(GL_LINES);
            for (Point &p : clippedFace) {
                p = (projectAndScale * p).homogeneousToCartesian();
                glVertex2f(p.x, p.y);
            }
            glEnd();
        }
    }

    // swap buffers
    glutSwapBuffers();
}

void idle() {
    int t2 = glutGet(GLUT_ELAPSED_TIME);
    int dt = t2 - t;
    t = t2;
    
    // rotate radar dish
    db.radarPtr()->localTransform(Rotate4(-dt * 0.001, 'Y'));

    // animate plane position
    if (autopilot) {
        // if the plane is above the ground, descend
        if (planePosition.y > 5) {
            planePosition.y -= dt * 0.015;
        }
        else {
            planePosition.y = 5;
        }

        // if the plane is far away from the terminal, move forward
        if (planePosition.z > -100) {
            planePosition.z -= dt * 0.02;
        }
        else {
            planePosition.z = -100;
        }
        
        // keep the plane near the centerline of the runway
        if (planePosition.x > 0.1) {
            planePosition.x -= dt * 0.02;
        }
        else if (planePosition.x < -0.1) {
            planePosition.x += dt * 0.02;
        }
    }
    glutPostRedisplay();
}


void reshape(int w, int h) {
    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D((GLdouble) -w/2, (GLdouble) w/2, (GLdouble) -h/2, (GLdouble) h/2);
}

int main(int argc, char** argv) {
    // initialize glut & display window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(db.screenWidth(), db.screenHeight());
    glutCreateWindow("CS425 - Project 2 ");
    
    // initialize objects from database
    initializeObjects();
    t = glutGet(GLUT_ELAPSED_TIME);
    
    glClearColor(1,1,1,1);
        
    // keyboard function
    glutKeyboardFunc(handleKeyEvent);
    
    // display function
    glutDisplayFunc(display);
    
    // idle function
    glutIdleFunc(idle);
    
    // reshape function
    glutReshapeFunc(reshape);
    
    // loop
    glutMainLoop();
    
    return 0;
}
