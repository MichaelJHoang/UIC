#pragma once

#include "pch.h"
#include "point.hpp"

#include <iostream>
#include <vector>
#include <cmath>

#if defined file_Check
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Matrix
{
	private:
		vector <Point> matrix;

	public:
		// an empty matrix
		Matrix()
		{
			matrix = { Point(0, 0, 0, 0), Point(0, 0, 0, 0), Point(0, 0, 0, 0), Point(0, 0, 0, 0) };
		}

		Matrix(vector <float> p1, vector <float> p2, vector <float> p3, vector <float> p4)
		{
			matrix = { Point(p1), Point(p2), Point(p3), Point(p4) };
		}

		Point operator[] (int x) // operator overload operation which allows the use of matrix[][]
		{						 // to access an integer of a specific point
			return matrix[x];
		}

		// multiply a matrix with a given point
		Point multiply(Point &input)
		{
			float x, y, z, w;

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					if (row == 0)
						x += matrix[row][col] * input[col];
					else if (row == 1)
						y += matrix[row][col] * input[col];
					else if (row == 2)
						z += matrix[row][col] * input[col];
					else if (row == 3)
						w += matrix[row][col] * input[col];
					else
					{
						cout << "THERE IS AN ERROR WITH MULTIPLICATION" << endl;
						return input;
					}
				}
			}

			return Point(x, y, z, w);
		}

		// convert the matrix into a scale matrix
		void toScale(float x, float y, float z)
		{
			matrix = { Point(x,0,0,0), 
				       Point(0,y,0,0), 
				       Point(0,0,z,0), 
				       Point(0,0,0,1) };
		}

		// convert the matrix into a translation matrix
		void toTranslate(float x, float y, float z)
		{
			matrix = { Point(0,0,0,x),
					   Point(0,0,0,y),
					   Point(0,0,0,z),
					   Point(0,0,0,1) };
		}

		// convert the matrix into a rotation matrix
		void toRotate(int theta, char axis) // rotate a [theta] about the [axis] axis
		{
			switch (axis)
			{
				case 'x':
					matrix = { Point(1,          0,           0, 0),
							   Point(0, cos(theta), -sin(theta), 0),
							   Point(0, sin(theta),  cos(theta), 0),
							   Point(0,          0,           0, 1) };
					break;

				case 'y':
					matrix = { Point(cos(theta),  0, sin(theta), 0),
							   Point(0,           1,          0, 0),
							   Point(-sin(theta), 0, cos(theta), 0),
							   Point(0,           0,          0, 1) };
					break;

				case 'z':
					matrix = { Point(cos(theta), sin(theta), 0, 0),
							   Point(sin(theta), cos(theta), 0, 0),
							   Point(0,                   0, 1, 0),
							   Point(0,                   0, 0, 1) };
					break;

				default:
					cout << "CANNOT CONVERT TO ROTATION MATRIX" << endl;
			}
		}

		// convert the matrix into the perspective projection matrix
		void toPerspectiveProjection(float d)
		{
			matrix = { Point(1, 0,       0, 0),
					   Point(0, 1,       0, 0),
					   Point(0, 0,       1, 0),
					   Point(0, 0,-(1 / d), 0) };
		}

		// convert/reset to identity matrix
		void toIdentity()
		{
			matrix = { Point(1,0,0,0),
					   Point(0,1,0,0),
					   Point(0,0,1,0),
					   Point(0,0,0,1) };
		}

		// set a value [num] @ matrix[x][y]
		// have to do this because operator overloading
		// does not allow me to manipulate values at
		// specific addresses based on a return statment
		void set(int x, int y, float num)
		{
			matrix[x].set(y, num);
		}

		// operator overload [ * ] to allow multiplication of [N x N] and [N x N] matrices
		Matrix operator* (Matrix &otherMatrix)
		{
			Matrix newMatrix = Matrix();

			for (int x = 0; x < 4; x++)
				for (int y = 0; y < 4; y++)
					for (int z = 0; z < 4; z++)
						newMatrix.set(x, y, matrix[x][z] * otherMatrix[z][y]);

			return newMatrix;
		}
};