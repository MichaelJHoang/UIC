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
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// 
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"

// using this namespace to save myself from having to type and read alot.
using namespace std;

vec3::vec3 color(const ray::ray& r, hitable::hitable *world)
{
	hitRecord rec;

	if (world -> hit(r, 0.0, FLT_MAX, rec))
	{
		return 0.5 * vec3::vec3(rec.normal.x() + 1, 
								rec.normal.y() + 1, 
								rec.normal.z() + 1);
	}
	else
	{
		vec3::vec3 unitDirection = unit_vector(r.direction());

		float t = 0.5 * (unitDirection.y() + 1.0);

		return (1.0 - t) * vec3::vec3(1.0, 1.0, 1.0) + t * vec3::vec3(0.5, 0.7, 1.0);
	}
}


/*

	Main

	TODO: implement threads.

*/
int main()
{
	int nx = 800;
	int ny = 400;
	int nz = 400;

	ofstream outfile;

	outfile.open("raytrace_output.ppm");

	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	/*
	vec3::vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
	vec3::vec3 horizontal(4.0, 0.0, 0.0);
	vec3::vec3 vertical(0.0, 2.0, 0.0);
	vec3::vec3 origin(0.0, 0.0, 0.0);
	*/
	

	hitable::hitable* list[2];

	list[0] = new sphere::sphere(vec3::vec3(0, 0, -1.0), 0.5);
	list[1] = new sphere::sphere(vec3::vec3(0, -100.5, -1.0), 100);

	hitable::hitable* world = new hitableList::hitableList(list, 2);

	camera::camera cam;

	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			vec3::vec3 col(0, 0, 0);

			for (int z = 0; z < nz; z++)
			{
				float u = float(y + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(x + (rand() / (RAND_MAX + 1.0))) / float(ny);

				ray::ray r = cam.getRay(u, v);

				vec3::vec3 p = r.point_at_parameter(2.0);

				col += color(r, world);
			}
			
			//ray::ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

			//vec3::vec3 p = r.point_at_parameter(2.0);
			//vec3::vec3 col = color(r, world);

			col /= float(nz);

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