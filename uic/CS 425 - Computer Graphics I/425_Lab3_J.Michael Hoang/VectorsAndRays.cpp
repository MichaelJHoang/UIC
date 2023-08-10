/*	Author: Jon-Michael Hoang
*	File: VectorsAndRays.cpp
*	
*	This file contains the classes used to make rays and vectors specifically
*	for this project
*/

#pragma once

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#if defined file_Check
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Vector
{
	public:
		double x, y, z;
		
		// defining a vector
		Vector()
		{
			x = y = z = 0;
		}

		Vector(double a, double b, double c)
		{
			x = a;
			y = b;
			z = c;
		}

		// operator overloaders to allow linear algebrea-like arithmetic
		Vector operator+ (const Vector& v)
		{
			return Vector(x + v.x, y + v.y, z + v.z);
		}

		Vector operator- (const Vector& v)
		{
			return Vector(x - v.x, y - v.y, z - v.z);
		}

		Vector operator* (double d)
		{
			return Vector(x * d, y * d, z * d);
		}

		Vector operator/ (double d)
		{
			return Vector(x / d, y / d, z / d);
		}

		Vector normalize()
		{
			double SQRT = sqrt(x * x + y * y + z * z);
			return Vector(x / SQRT, y / SQRT, z / SQRT);
		}

		double scalar()
		{
			return sqrt(x * x + y * y + z * z);
		}
};

class Ray
{
	public:
		Vector origin;
		Vector direction;

		Ray(Vector o, Vector d)
		{
			origin = o;
			direction = d;
		}
};