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
#include <thread>
#include <ctime>

// programmer-defined includes
#include "sphere.h"
#include "hitablelist.h"
#include "float.h"
#include "camera.h"

// using this namespace to save myself from having to type and read alot.
using namespace std;

/*
	TODO: Comment
*/
vec3::vec3 randomInUnitSphere()
{
	vec3::vec3 p;

	do
	{
		p = 2.0 * vec3::vec3((rand() / (RAND_MAX + 1.0)), 
							 (rand() / (RAND_MAX + 1.0)), 
							 (rand() / (RAND_MAX + 1.0))) 
							 - vec3::vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);

	return p;
}

vec3::vec3 color(const ray::ray& r, hitable::hitable *world)
{
	hitRecord rec;

	if (world -> hit(r, 0.0, FLT_MAX, rec))
	{
		// TODO: comment
		vec3::vec3 target = rec.p + rec.normal + randomInUnitSphere();

		return 0.5 * color(ray::ray(rec.p, target - rec.p), world);
	}
	else
	{
		vec3::vec3 unitDirection = unit_vector(r.direction());

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
	hitable::hitable* list[2];

	// in this case, spheres.
	list[0] = new sphere::sphere(vec3::vec3(0, 0, -1.0), 0.5);
	list[1] = new sphere::sphere(vec3::vec3(0, -100.5, -1.0), 100);

	hitable::hitable* world = new hitableList::hitableList(list, 2);

	// set where the user is looking at into the scene
	camera::camera cam;

	/*
		TODO: this section here runs too slow - need to multithread to prevent long compile times
	*/
	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			vec3::vec3 col(0, 0, 0);

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

				ray::ray r = cam.getRay(u, v);

				vec3::vec3 p = r.point_at_parameter(2.0);

				col += color(r, world);
			}

			// write the pixel value to the ppm file
			col /= float(nz);

			col = vec3::vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

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
	std::cout << "Starting the Ray-Tracing program..." << endl;

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