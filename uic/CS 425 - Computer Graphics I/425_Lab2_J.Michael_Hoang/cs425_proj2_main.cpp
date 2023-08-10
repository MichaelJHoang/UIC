/*
 *
 *
 *	Author: Jon-Michael Hoang | jhoang6
 *	CS 425: Project 2 
 *	File:   main.cpp
 *	Due:    11/2/18
 *
 *	Specs: Windows 10 with Visual Studios 2017
 *
 *
 *
 */

#include "pch.h"
#include "matrix.hpp"

#include <iostream>
#include <vector>
#include <cmath>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

// current matrix
Matrix currentMatrix = Matrix();

// [ Point ] class may not represent a point ... e.g. VUP and VPN
vector <Point> FCP = { Point(.700,.700,.10), Point(-.700,.700,.10), Point(-.700,-.700,.10), Point(.700,-.700,.10) }; // dimensions of the front clipping plane
vector <Point> BCP = { Point(.900,.900,-.100), Point(-.900,.900,-.100), Point(-.900,-.900,-.100), Point(.900,-.900,-.100) }; // dimensions of the back clipping plane
vector <Point> viewPlane = { Point(.650,.650,-.50), Point(-.650,.650,-.50), Point(-.650,-.650,-.50), Point(.650,-.650,-.50) }; // dimensions of the view plane
Point VRP = Point(0, 0, -.100); // calculate VRP based on PRP and viewPlane position -> translate
Point VPN = Point(0, 0, 1);
Point VUP = Point(0, 1, 0);
Point PRP = Point(.400, .400, .10);  // defined

// objects for the scene

// horizon
Point horizonLeft = { -1.0, 0.0, -.99 };	// left point of the horizon
Point horizonRight = { 1.0, 0.0, -.99 };	// right point of the horizon

// back wall
vector <Point> backWall = { Point(.600,.600,-.99),
							Point(-.600,.600,-.99),
							Point(-.600,0.0,-.99),
							Point(.600,0.0,-.99), };

// road
vector <Point> road = { Point(.250, .250, -.80),	// back of road
						Point(-.250, .250, -.80),
						Point(-.250, -.250, .20),	// front of road
						Point(.250, -.250, .20) };

int t;
float theta = 0;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;

		case 'w':
			PRP.set(1, PRP[1] + 10);
			break;

		case 'a':
			PRP.set(0, PRP[0] - 10);
			break;

		case 's':
			PRP.set(1, PRP[1] - 10);
			break;

		case 'd':
			PRP.set(0, PRP[0] + 10);
			break;

		case 'f':
			PRP.set(2, PRP[2] - 10);
			break;

		case 'v':
			PRP.set(2, PRP[2] + 10);
			break;
	}
}

void idle() 
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);

	int dt = currentTime - t;
	t = currentTime;

	theta += dt * 0.0021;

	glutPostRedisplay();
}

void draw(float x, float y, float z)
{
	glVertex3f(x, y, z);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0, 0, 0);

	// draw back clipping plane
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < BCP.size(); x++)
	{
		draw(BCP[x][0], BCP[x][1], BCP[x][2]);
	}
	glEnd();

	// draw front clipping plane
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < FCP.size(); x++)
	{
		draw(FCP[x][0], FCP[x][1], FCP[x][2]);
	}
	glEnd();

	// draw view plane
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < viewPlane.size(); x++)
	{
		draw(viewPlane[x][0], viewPlane[x][1], viewPlane[x][2]);
	}
	glEnd();
	
	// draw horizon
	glBegin(GL_LINE_LOOP);
	draw(horizonLeft[0], horizonLeft[1], horizonLeft[2]);
	draw(horizonRight[0], horizonRight[1], horizonRight[2]);
	glEnd();

	// draw back wall
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < backWall.size(); x++)
	{
		draw(backWall[x][0], backWall[x][1], backWall[x][2]);
	}
	glEnd();

	// draw road
	glBegin(GL_LINE_LOOP);
	for (int x = 0; x < road.size(); x++)
	{
		draw(road[x][0], road[x][1], road[x][2]);
	}
	glEnd();

	glutSwapBuffers();
}

void frustum(Matrix &inputMatrix, 
			 float left, float right,
			 float bottom, float top,
			 float znear, float zfar)
{
	Matrix newMatrix = Matrix();
	newMatrix.set(0, 0, (2.0 * znear) / (right - left));
	newMatrix.set(0, 2, (right + left) / (right - left));
	newMatrix.set(1, 1, (2 * znear) / (top - bottom));
	newMatrix.set(1, 2, (top + bottom) / (top - bottom));
	newMatrix.set(2, 2, -(zfar + znear) / (zfar - znear));
	newMatrix.set(2, 3, -(2 * zfar*znear) / (zfar - znear));
	newMatrix.set(3, 2, -1);

	inputMatrix = newMatrix;
}

// currentMatrix -> perspective matrix with this function and the one above
void perspective(Matrix &inputMatrix, float fovy, float aspectRatio, float znear, float zfar)
{
	float xmax, ymax;

	ymax = znear * tanf(fovy * 3.14 / 360.00);
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio;

	xmax = ymax * aspectRatio;

	frustum(inputMatrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

// reshape
void reshape(int width, int height)
{
	// set viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // lower-left corner

	currentMatrix.toIdentity();	// reset the current matrix to ID matrix
	perspective(currentMatrix, 60, 1.00, 10, -100);	// set current matrix to perspective matrix
}

void initGL()
{
	// default color buffer
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0f);		   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
}

int main(int argc, char **argv)
{
	// allows for any GLUT cmd line

	glutInit(&argc, argv);

	// create an output window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);

	// create and name the window
	glutCreateWindow("CS 425 - Program 2: Perspective Projection");

	// allow userInput via keyboard
	glutKeyboardFunc(keyboard);

	// assign display
	glutDisplayFunc(display);

	// assign idle
	//glutIdleFunc(idle);

	// set the reshape callback for the current window
	glutReshapeFunc(reshape);

	initGL();

	// enter GLUT event processing loop
	glutMainLoop();

	return (EXIT_SUCCESS);
}