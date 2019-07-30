/*
 *
 *	Author: Jon-Michael Hoang
 *	
 *	What this is: This is a ray tracer program that I developed based off of a textbook.
 *				  What ray tracing is is that it's an algorithm in computer graphics that enables
 *				  one to render life-like light and shadows.
 *
 *	How to use this: Simply compile and go to the directory of this program to find a
 *					 "raytrace_output.ppm" file, toss it into a NetPBM viewer and see the results
 *					 The reason as to why I'm doing this is because it allows for faster computation.
 *
 */

// standard libraries used for this project
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

// 
#include "ray.h"

// using this namespace to save myself from having to type and read alot.
using namespace std;

bool hitSphere(const vec3::vec3& center, float radius, const ray::ray& r)
{
	vec3::vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;
	
	return (discriminant > 0);
}

vec3::vec3 color(const ray::ray& r)
{
	if (hitSphere(vec3::vec3(0, 0, -1), 0.5, r))
		return vec3::vec3(1, 0, 0);

	vec3::vec3 unitDirection = unit_vector(r.direction());;

	float t = .5 * (unitDirection.y() + 1.0);

	return (1.0 - t) * vec3::vec3(1.0, 1.0, 1.0) + t * vec3::vec3(0.5, 0.7, 1.0);
}


/*

	Main

*/
int main()
{
	int nx = 200;
	int ny = 100;

	ofstream outfile;

	outfile.open("raytrace_output.ppm");

	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3::vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
	vec3::vec3 horizontal(4.0, 0.0, 0.0);
	vec3::vec3 vertical(0.0, 2.0, 0.0);
	vec3::vec3 origin(0.0, 0.0, 0.0);

	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			float u = float(y) / float(nx);
			float v = float(x) / float(ny);
			
			ray::ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

			vec3::vec3 col = color(r);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	outfile.close();

	cout << "Done." << endl;

	return 0;
}
/*

	END: Main

*/