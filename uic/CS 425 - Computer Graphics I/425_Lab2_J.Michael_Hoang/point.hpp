#pragma once

#include "pch.h"

#include <iostream>
#include <vector>
#include <cmath>

#if defined file_Check
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Point
{
private:
	
	vector <float> point;

public:

	// default constructor
	Point()
	{
		point = { 0, 0, 0, 0 };
	}

	// given a homogenous point as a constructor...
	Point(float x, float y, float z, float w)
	{
		point = { x, y, z, w };
	}

	// given a cartesian point...
	Point(float x, float y, float z)
	{
		point = { x, y, z, 1 };	// having w = 1 for easy math
	}

	// given a vector of ints...
	Point(vector <float> something)
	{
		if (something.size() == 4)
			point = { something[0], something[1], something[2], something[3] };
		else
			point = { something[0], something[1], something[2] };
	}

	float distanceFrom(Point &other)
	{
		return sqrt(pow(other[0] - point[0], 2) + pow(other[1] - point[1], 2) + pow(other[2] - point[2], 2));
	}

	Point toCartesian(Point &htc) // homogenous to cartesian
	{
		if (htc[3] == 0)
		{
			return htc;
		}
		else
		{
			Point newPoint = { htc[0] / htc[3], htc[1] / htc[3], htc[2] / htc[3] };
			return newPoint;
		}
	}

	Point toHomogenous(Point &cth, float w) // cartesian to homogenous with a given w
	{
		Point newPoint = { cth[0] * w, cth[1] * w, cth[2] * w, w };
		return newPoint;
	}

	float operator[] (int x) // operator overload to access the point
	{
		return point[x];
	}

	void set(int at, float num) // set a value [ num ] at a given index [ at ] 
	{
		point[at] = num;
	}
};