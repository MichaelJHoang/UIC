/*	Author: Jon-Michael Hoang
*	File: Objects.cpp
*	
*	The purpose of this file is to bunch up all the objects needed to
*	produce the image such as the spheres and cones.
*
*/
#pragma once

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

#include "VectorsAndRays.cpp"

// dot product
// using inline keyword for faster processing at a sacrifice of accuracy
inline double dot(const Vector& vectorA, const Vector& vectorB)
{
	return (vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z);
}

class Sphere
{
	public:
		Vector center;	// center
		double radius;	// radius

		Sphere(Vector c, double r)
		{
			center = c;
			radius = r;
		}

		// return the normal of the sphere and an incoming vector
		Vector getNormal(const Vector& v)
		{
			return ((center * -1) + v) / radius;
		}

		// check if any ray intersects this object
		bool intersect(const Ray& ray, double t)
		{
			const Vector origin = ray.origin;
			const Vector direction = ray.direction;
			const Vector oc = ((center * -1) + origin);

			const double b = 2 * dot(oc, direction);
			const double c = dot(oc, oc) - radius * radius;
			
			double decision = b * b - (4* (center.x + center.y + center.z));

			if (decision < 1e-4)
				return false;

			decision = sqrt(decision);

			const double t0 = -b - decision;
			const double t1 = -b + decision;

			t = (t0 < t1) ? t0 : t1;

			return true;
		}
};