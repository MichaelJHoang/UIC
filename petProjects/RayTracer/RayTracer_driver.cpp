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
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>

// programmer-defined includes
#include "float.h"
#include "camera.h"
#include "material.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

#define drand48() (rand() / (RAND_MAX + 1.0))

// using this namespace to save myself from having to type and read alot.
using namespace std;

/*
	TODO: Comment
*/
vec3 color(const ray& r, hitable *world, int depth)
{
	hitRecord rec;

	if (world -> hit(r, 0.001, FLT_MAX, rec))
	{
		// TODO: comment
		ray scattered;

		vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3::vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unitDirection = unit_vector(r.direction());

		float t = 0.5 * (unitDirection.y() + 1.0);

		// linear interpolation = blendValue = (1-t)*startValue + t*endValue
		return (1.0 - t) * vec3::vec3(1.0, 1.0, 1.0) + t * vec3::vec3(0.5, 0.7, 1.0);
	}
}

void startRayTracingProgram()
{
	// scene dimensions
	int nx = 800;
	int ny = 400;
	int nz = 400;

	// as of current, the program writes to a ppm file.
	// maybe create an application window to display result?
	ofstream outfile;

	// look for this file to push into a NetPBM viewer
	outfile.open("raytrace_output.ppm");

	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	// creates a list of hitable objects
	hitable* list[5];

	float R = cos(M_PI / 4);

	// in this case, spheres.
	list[0] = new sphere(vec3(0, 0, -1), 
						 0.5, 
						 new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 
						 100, 
						 new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 
						 0.5, 
						 new metal(vec3(0.8, 0.6, 0.2), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 
						 0.5, 
						 new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), 
						 -0.45, 
						 new dielectric(1.5));

	hitable* world = new hitableList(list, 5);

	vec3 lookfrom(-2, 2, 1);
	vec3 lookat(0, 0, -1);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = .1;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, distToFocus);

	/*
		TODO: this section here runs too slow - need to multithread to prevent long compile times
	*/
	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			vec3 col(0, 0, 0);

			/*
				TODO: elaborate more?

				What this does is that it shoots rays into the scene and sees if there was anything hit.
				If so, return the color of the supposed hit object and anti-alias it to remove jaggies.
			*/
			for (int z = 0; z < nz; z++)
			{
				// anti-aliasing magic in these two lines
				// major runtime overhead, though - need to fix with multithreading or CUDA?
				float u = float(y + (rand() / (RAND_MAX + 1.0))) / float(nx);
				float v = float(x + (rand() / (RAND_MAX + 1.0))) / float(ny);

				ray r = cam.getRay(u, v);

				vec3 p = r.point_at_parameter(2.0);

				col += color(r, world, 0);
			}

			// write the pixel value to the ppm file
			col /= float(nz);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	outfile.close();

	std::cout << "Ray-Tracing complete." << endl;
}


/*

	Main

	TODO: implement threads.

*/
int main()
{
	std::cout << "Running the Ray-Tracing program, this might take awhile..." << endl;

	// time how long it takes for the thing to finish
	clock_t initialTime = clock();
	double duration = 0.0;

	/*
		TODO: implement multithreading. As of 7/31/2019, it takes roughly 5 minutes + several seconds to
		finish
	*/
	thread t(startRayTracingProgram);

	if (t.joinable())
	{
		t.join();
	}

	duration = (clock() - initialTime) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration: " << int(duration / 60) << " minutes and " << fmod(duration, 60) << " seconds." << endl;

	return 0;
}
/*

	END: Main

*/