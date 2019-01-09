/*
 * File: jhoang6_cs425proj1.cpp
 * Author: Jon-Michael Hoang
 *
 * Date: September 20th, 2018
 *
 * OS: Windows 10 64-bit
 * Compiler: Visual Studio 2017
 *
 * Press 'W' to toggle forward and 'A' to toggle back
 */


// all the headers and/or libraries are stored up here
#include "pch.h" // always have this one first

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>

#ifdef GLUT_fileCheck
#include <GLUT/glut.h>
#else
#include <GL\glut.h>
#endif

using namespace std;

// global variables to allow the display of either
// the name, the unfilled picture, or the filled
// picture
int drawName = 0, drawPicture = 1, drawPicture_filled = 2;

// global variable to keep track of the pages/what is drawn
// if == 0, drawName
// if == 1, drawPicture
// if == 2, drawPicture_filled
unsigned int page = 0;


// output code by Mark Kilgard
// designate where the object is drawn on the window
void output(int x, int y) { glRasterPos2f(x, y); }


// assign certain keys that the user will be able to use to interact
// with the program
// have if statements to make sure page is either 0, 1, or 2
// increase or decrease the page number with the 
// corresponding keys
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;

		case 'a':
			if (page != 0)
				page--;
			break;

		case 'w':
			if (page != 2)
				page++;
			break;
	}
}


// draws a point on the window at a given (x, y) coordinate
void drawPixel(int x, int y)
{
	glColor3f(0.0, 0.0, 0.0);	// default point color

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


// draws a grey point on the window at a given (x, y) coordinate
void drawPixel_grey(int x, int y)
{
	glColor3f(.5, .5, .5);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


// draws a red point on the window at a given (x, y) coordinate
void drawPixel_red(int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


// draws a green point on the window at a given (x, y) coordinate
void drawPixel_green(int x, int y)
{
	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


// draws a blue point on the window at a given (x, y) coordinate
void drawPixel_blue(int x, int y)
{
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


// function to draw a line based on Bresenham's Algorithm
void drawLine(float x0, float y0, float x1, float y1)
{
	// initialize all variables to 0...or else who knows
	// what values the compiler and machine will give them
	float x = 0, y = 0,		// temp holders
		dx = 0, dy = 0,		// delta variables
		decision = 0;		// decision variable

	dx = x1 - x0; dy = y1 - y0;	// determine deltas

	// invert delta so that it can go the other way
	// and not just East or NorthEast, etc.,
	// provided the statement is true
	dx = (dx < 0) ? -dx : dx;
	dy = (dy < 0) ? -dy : dy;

	// also allow the use of going multiple directions
	float incrementX = 1;	// X incrementer
	float incrementY = 1; // Y incrementer

	incrementX = (x0 > x1) ? -1 : 1;	// invert the increment if x0 > x1
	incrementY = (y0 > y1) ? -1 : 1;	//						if y0 > y1

	x = x0; y = y0; // dump into temp holders

	drawPixel(x, y);	// draw the first point

	// run the following algorithm if delta x > delta y
	if (dx > dy)
	{
		// calculating the next decision(s)
		decision = 2 * dy - dx;

		// loop algorithm to calculate the points on the line and then draw them in
		for (float loopCounter = 0; loopCounter < dx; loopCounter++)
		{
			if (decision >= 0)
			{
				y += incrementY;
				decision += 2 * (dy - dx);	// next pixel @ (x + n,  y + n); n integer
			}
			else
				decision += 2 * dy;	// next pixel @ (x + n,  y); n integer

			x += incrementX;

			drawPixel(x, y);	// now draw the new pixel in
		}
	}
	// run the following algorithm if delta y > delta x
	else
	{
		// calculating the next decision(s)
		decision = 2 * dx - dy;

		// loop algorithm to calculate the points on the line and then draw them in
		for (float loopCounter = 0; loopCounter < dy; loopCounter++)
		{
			if (decision >= 0)
			{
				x += incrementX;
				decision += 2 * (dx - dy);	// next pixel @ (x + n,  y + n); n integer
			}
			else
				decision += 2 * dx;	// next pixel @ (x,  y + n); n integer

			y += incrementY;

			drawPixel(x, y);	// now draw the new pixel in
		}
	}
}


// function to draw a circle based on page 82-85 of [Computer Graphics: Principles and Practice
// SECOND EDITION IN C] by Foley et. al.
void drawCircle(int centerX, int centerY, int radius, int fillFlag)
{
	int x = 0, y = radius;
	int decision = 3 / 2 - radius;

	while (x <= y)
	{
		// eight way symmetry of the circle
		// only need to compute 45 degrees of it
		// and the rest falls through
		drawPixel(centerX + x, centerY + y);
		drawPixel(centerX + x, centerY - y);
		drawPixel(centerX - x, centerY + y);
		drawPixel(centerX - x, centerY - y);
		drawPixel(centerX + y, centerY + x);
		drawPixel(centerX - y, centerY + x);
		drawPixel(centerX + y, centerY - x);
		drawPixel(centerX - y, centerY - x);

		// algorithm to fill in the circle
		if (fillFlag)
		{ 
			for (int y = -radius; y <= radius; y++)
				for (int x = -radius; x <= radius; x++)
					if (x * x + y * y <= radius * radius)
						drawPixel_blue(centerX + x, centerY + y);
		}

		// midpoint circle algorithm
		if (decision < 0)
			decision += (2 * x) + 3;
		else
		{
			decision += (2 * (x - y)) + 5;
			y--;
		}
		x++;
	}
}


// function to draw a rectangle derived from the drawLine() function
void drawRectangle(int x0, int y0, int x1, int y1)
{
	/* Solid Rectangle
	for (int y = y0; y <= y1; y++)
		for (int x = x0; x <= x1; x++)
			drawPixel(x, y);
	*/

	// right-hand rule
	//storeEdge(x0, y0, x1, y1);
	drawLine(x1, y0, x0, y0);	// top-right to top-left
	drawLine(x0, y0, x0, y1);	// top-left to bottom-left
	drawLine(x0, y1, x1, y1);	// bottom-left to bottom-right
	drawLine(x1, y1, x1, y0);	// bottom-right to top-right
}


// using the drawLine() function, draw the 3 sides of a triangle
// by connecting their vertices
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	drawLine(x0, y0, x1, y1);
	drawLine(x1, y1, x2, y2);
	drawLine(x2, y2, x0, y0);
}


// using the drawLine() function, draw the 3 sides of a triangle
// by connecting their vertices and attempting to draw in between
void drawTriangle_colored(int x0, int y0, int x1, int y1, int x2, int y2)
{
	drawLine(x0, y0, x1, y1);
	drawLine(x1, y1, x2, y2);
	drawLine(x2, y2, x0, y0);

	int left = x0, right = x0;
	int slopeLeft = (y1 - y0) / (x1 - x0);
	int slopeRight = (y2 - y0) / (x2 - x0);

	// start from top and scan until it reaches the bottom of the triangle
	for (int count = y0; count != y1 + 1; count--)
	{
		drawLine(left--, count, right++, count);
	}
}


// function to draw an ellipse based on the ellipse midpoint algorithm
void drawEllipse(int centerX, int centerY, int radiusX, int radiusY)
{
	int x = 0, y = radiusY;
	int pen = 0;

	pen = (radiusY * radiusY) - (radiusX * radiusX * radiusY) + ((radiusX * radiusX) / 4);

	while ((2 * radiusY * radiusY * x) < (2 * radiusX * radiusX * y))
	{
		// draw the arcs of the ellipse
		drawPixel(centerX + x, centerY + y);
		drawPixel(centerX + x, centerY - y);
		drawPixel(centerX - x, centerY + y);
		drawPixel(centerX - x, centerY - y);

		if (pen < 0)
		{
			x++;
			pen = pen + (2 * radiusY * radiusY * x) + (radiusY * radiusY);
		}
		else
		{
			x++;
			y--;
			pen = pen + (2 * radiusY * radiusY * x + radiusY * radiusY) - (2 * radiusX * radiusX * y);
		}
	}

	pen = ((float)x + 0.5) * ((float)x + 0.5) * radiusY * radiusY +
		(y - 1) * (y - 1) * radiusX * radiusX - radiusX * radiusX *
		radiusY * radiusY;

	while (y >= 0)
	{
		drawPixel(centerX + x, centerY + y);
		drawPixel(centerX + x, centerY - y);
		drawPixel(centerX - x, centerY + y);
		drawPixel(centerX - x, centerY - y);

		if (pen <= 0)
		{
			x++;
			y--;
			pen = pen + (2 * radiusY * radiusY * x) - (2 * radiusX * radiusX * y) + (radiusX * radiusX);
		}
		else
		{
			y--;
			pen = pen - (2 * radiusX * radiusX * y) + (radiusX * radiusX);
		}

	}
}


void detectEdge(int x0, int y0, int x1, int y1, int* leftEdge, int* rightEdge)
{
	int mx, x, temp;

	if ((y1 - y0) < 0)	// if second point is below the first point, swap those values
	{
		temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;
	}

	if ((y1 - y0) != 0)	// if denominator is zero, there is no slope
		mx = (x1 - x0) / (y1 - y0);
	else
		mx = x1 - x0;	// ...which implies that it's horizontal

	x = x0;

	for (int i = y0; i < y1; i++)
	{
		if (x < leftEdge[i])
			leftEdge[i] = x;
		if (x > rightEdge[i])
			rightEdge[i] = x;

		x += mx;
	}
}


void scanFill(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
	int leftEdge[800], rightEdge[800];

	for (int i = 0; i < 800; i++)	// initialize every value in the arrays
	{
		leftEdge[i] = 800;
		rightEdge[i] = 0;
	}

	detectEdge(x0, y0, x1, y1, leftEdge, rightEdge);
	detectEdge(x1, y1, x2, y2, leftEdge, rightEdge);
	detectEdge(x2, y2, x3, y3, leftEdge, rightEdge);
	detectEdge(x3, y3, x0, y0, leftEdge, rightEdge);

	for (int j = 0; j < 800; j++)
	{
		if (leftEdge[j] <= rightEdge[j])
			for (int i = leftEdge[j]; i < rightEdge[j]; i++)
				drawPixel_grey(i, j);
	}
}


// function to determine what is drawn and how it is drawn
void display()
{
	// clear screen to clear color
	glClear(GL_COLOR_BUFFER_BIT);

	if (page == drawName)
	{
		// each line of drawLine() in this block represents
		// a character stroke in my name
		// "MICHAEL HOANG"

		/* START FIRST NAME */
		// M
		drawLine(100, 700, 100, 600);
		drawLine(100, 700, 150, 650);
		drawLine(150, 650, 200, 700);
		drawLine(200, 700, 200, 600);

		// I
		drawLine(225, 700, 225, 600);

		// C
		drawLine(250, 700, 250, 600);
		drawLine(250, 700, 300, 700);
		drawLine(250, 600, 300, 600);

		// H
		drawLine(325, 700, 325, 600);
		drawLine(375, 700, 375, 600);
		drawLine(325, 650, 375, 650);

		// A
		drawLine(400, 700, 400, 600);
		drawLine(450, 700, 450, 600);
		drawLine(400, 700, 450, 700);
		drawLine(400, 650, 450, 650);
		
		// E
		drawLine(475, 700, 475, 600);
		drawLine(475, 700, 525, 700);
		drawLine(475, 650, 525, 650);
		drawLine(475, 600, 525, 600);

		// L
		drawLine(550, 700, 550, 600);
		drawLine(550, 600, 600, 600);
		/* END FIRST NAME */

		/* START LAST NAME */
		// H
		drawLine(100, 400, 100, 300);
		drawLine(150, 400, 150, 300);
		drawLine(100, 350, 150, 350);

		// O
		drawLine(175, 400, 175, 300);
		drawLine(225, 400, 225, 300);
		drawLine(175, 400, 225, 400);
		drawLine(175, 300, 225, 300);

		// A
		drawLine(250, 400, 250, 300);
		drawLine(300, 400, 300, 300);
		drawLine(250, 400, 300, 400);
		drawLine(250, 350, 300, 350);

		// N
		drawLine(325, 400, 325, 300);
		drawLine(375, 400, 375, 300);
		drawLine(325, 400, 375, 300);

		// G
		drawLine(400, 400, 400, 300);
		drawLine(400, 400, 450, 400);
		drawLine(400, 300, 450, 300);
		drawLine(450, 300, 450, 350);
		drawLine(450, 350, 425, 350);

		/* END LAST NAME */
	}
	else if (page == drawPicture)
	{
		drawRectangle(200, 700, 600, 100);	// head
		drawRectangle(133, 550, 200, 400);	// left ear
		drawRectangle(600, 550, 666, 400);	// right ear
		drawTriangle(250, 790, 200, 700, 300, 700);	// left horn
		drawTriangle(550, 790, 500, 700, 600, 700);	// right horn
		drawTriangle(400, 465, 350, 360, 450, 360);	// nose
		drawCircle(300, 500, 50, 0);	// left eye
		drawCircle(500, 500, 50, 0);	// right eye
		drawEllipse(400, 250, 100, 40);	// mouth
	}
	else if (page == drawPicture_filled)
	{
		drawRectangle(200, 700, 600, 100);	// head
		scanFill(200, 700, 200, 100, 600, 100, 600, 700);
		drawRectangle(133, 550, 200, 400);	// left ear
		scanFill(133, 550, 133, 400, 200, 400, 200, 550);
		drawRectangle(600, 550, 666, 400);	// right ear
		scanFill(600, 550, 600, 400, 666, 400, 666, 550);
		drawTriangle_colored(250, 790, 200, 700, 300, 700);	// left horn
		drawTriangle_colored(550, 790, 500, 700, 600, 700);	// right horn
		drawTriangle_colored(400, 465, 350, 360, 450, 360);	// nose
		drawCircle(300, 500, 50, 1);	// left eye
		drawCircle(500, 500, 50, 1);	// right eye
		drawEllipse(400, 250, 100, 40);	// mouth
	}
	else
	{
		//cout << "UNABLE TO DISPLAY ANYTHING...EXITING..." << endl;
		exit(EXIT_FAILURE); // if this line gets triggered, this indicates that
							// something is wrong with the code/input, etc.
	}

	// swap buffers
	glutSwapBuffers();
}


// reshape
void reshape(int width, int height)
{
	// set viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // lower-left corner

	// matrix for projection transformation
	glMatrixMode(GL_PROJECTION);

	// replace current matrix with ID matrix
	glLoadIdentity();

	// define 2D orthographic projection matrix
	gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height); // left, right, bottom, top
}


// main
int main(int argc, char **argv)
{
	int input;
	cout << " HELLO WORLD ";
	cin >> input;

	// allows for any GLUT cmd line

	glutInit(&argc, argv);

	// create an output window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 800);
	
	// create and name the window
	glutCreateWindow("CS 425 - Program 1: Scan-Conversion");

	// default color buffer
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// allow userInput via keyboard
	glutKeyboardFunc(keyboard);

	// assign display
	glutDisplayFunc(display);

	// assign idle
	glutIdleFunc(display);

	// set the reshape callback for the current window
	glutReshapeFunc(reshape);

	// enter GLUT event processing loop
	glutMainLoop();

	return (EXIT_SUCCESS);
}