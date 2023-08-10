#pragma once

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#include "VectorsAndRays.cpp"
#include "Objects.cpp"

#if defined file_Check
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//#include "..\proj3_database.txt"

using namespace std;

// specified dimensions for the window
int windowWidth = 400;
int windowHeight = 400;


// decide the color and make sure it doesn't go above and beyond 255 - which is the max
// or down and below 0 - which is the minimum
// therefore, "clamping" down the colors
void clamp(Vector& col)
{

	col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
	col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
	col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 400, 400);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// basic colors
	Vector white(255, 255, 255);
	Vector black(0, 0, 0);
	Vector red(255, 0, 0);
	Vector green(0, 255, 0);
	Vector blue(0, 0, 255);

	// lights and sphere
	Sphere sphere(Vector(-10.0, -12.0, -30.0), 8.0);
	Sphere ambientLight(Vector(0.1, 0.2, 0.1), 1.0);
	Sphere pointLight1(Vector(-20.0, 120.0, 40.0), 1.0);
	Sphere pointLight2(Vector(20.0, 100.0, -100.0), 1.0);

	double dt = 0.0;	// differential

	Vector pixelColor(white);

	//for each pixel
	for (int y = 0; y < windowHeight; y++)
		for (int x = 0; x < windowWidth; x++)
		{
			pixelColor = white;

			// send a ray through each pixel
			Ray ray(Vector(x, y, 0), Vector(0, 0, 1));

			// check for intersections
			if (sphere.intersect(ray, dt))
			{
				Vector pi = ray.origin + ray.direction;	
				Vector lightVector = ambientLight.center - pi;	// distance from ambient light to origin and its direction
				Vector normalVector = sphere.getNormal(pi);	// produce the normal as a result

				dt = dot(lightVector.normalize(), normalVector.normalize());	// differential

				pixelColor = (pixelColor * dt) * .5;	// account color with differential
				clamp(pixelColor);	// clamp it down
			}

			// now draw the point in
			glBegin(GL_POINTS);
				glColor3i(pixelColor.x, pixelColor.y, pixelColor.z);
				glVertex2d(x, y);
			glEnd();
		}

	// swap buffers
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	/* set the viewport */
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	/* Matrix for projection transformation */
	glMatrixMode(GL_PROJECTION);

	/* replaces the current matrix with the identity matrix */
	glLoadIdentity();

	/* Define a 2d orthographic projection matrix */
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);	// left, right, bottom, top
}

int main(int argc, char *argv[])
{
	// handle any exceptions
	try
	{
		/* deal with any GLUT command Line options */
		glutInit(&argc, argv);

		/* create an output window */
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

		glutInitWindowSize(windowWidth, windowHeight);

		glutCreateWindow("CS 425 - Project 3");

		/* specify clear values for the color buffers */
		glClearColor(1.0, 1.0, 1.0, 1.0);

		/* assign the display function */
		glutDisplayFunc(display);

		/* assign the idle function */
		glutIdleFunc(display);

		/* sets the reshape callback for the current window */
		glutReshapeFunc(reshape);

		// loop
		glutMainLoop();

		//ifstream file;

		//file.open("proj3_database.txt");
	}
	// print out any caught exceptions for debugging
	catch (exception e)
	{
		cout << e.what() << endl;
	}

	return (EXIT_SUCCESS);
}