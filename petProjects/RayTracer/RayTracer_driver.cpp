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
#include <omp.h>

// programmer-defined includes
#include "float.h"
#include "camera.h"
#include "material.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

// using this namespace to save myself from having to type and read alot.
using namespace std;

#define randomDouble (rand() / (RAND_MAX + 1.0))

/*
	TODO: Comment
*/
vec3 color(const ray& r, hitable *world, int depth)
{
	hitRecord rec;

	// ignore hits that are very near to 0
	if (world -> hit(r, 0.01, FLT_MAX, rec))
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
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unitDirection = unit_vector(r.direction());

		float t = 0.5 * (unitDirection.y() + 1.0);

		// linear interpolation = blendValue = (1-t)*startValue + t*endValue
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}


hitable* randomScene()
{
	int n = 100;

	hitable** list = new hitable * [n + 1];

	list[0] = new sphere(vec3(0, -1000, 0), 
		                 1000, 
		                 new lambertian(vec3(0.5, 0.5, 0.5)));

	int x = 1;

	for (int a = -10; a < 10; a++)
	{
		for (int b = -10; b < 10; b++)
		{
			float chooseMat = randomDouble;

			vec3 center(a + 0.9 * randomDouble,
						0.2,
						b + 0.9 * randomDouble);

			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				// diffuse
				if (chooseMat < 0.8)
				{
					list[x++] = new movingSphere(center, 
												 center + vec3(0, 0.5 * randomDouble, 0), 
												 0.0, 1.0, 0.2,
												 new lambertian(vec3(randomDouble * randomDouble, 
																	 randomDouble * randomDouble, 
																	 randomDouble * randomDouble)));
				}
				// metal
				else if (chooseMat < 0.95)
				{
					list[x++] = new sphere(center, 
										   0.2, 
										   new metal(vec3(0.5 * (1 + randomDouble), 
														  0.5 * (1 + randomDouble), 
														  0.5 * (1 + randomDouble)), 
														  0.5 * randomDouble));
				}
				// glass
				else
				{
					list[x++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[x++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[x++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[x++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitableList(list, x);
}





void startRayTracingProgram()
{
	// scene dimensions
	int nx = 400;
	int ny = 200;
	int nz = 200;

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

	world = randomScene();

	/*
	vec3 lookfrom(-2, 2, 1);
	vec3 lookat(0, 0, -1);
	float distToFocus = (lookfrom - lookat).length();
	float aperture = .1;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, distToFocus, 0.0, 1.0);
	*/

	vec3 lookfrom(15, 5, 7);
	vec3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);

	float distToFocus = 10.0;
	float aperture = 0.0;

	camera cam(lookfrom, 
			   lookat, 
			   vup,
		       20, 
		       float(nx) / float(ny), 
		       aperture, 
		       distToFocus, 
		       0.0, 
		       1.0);

	/*
		TODO: this section here runs too slow - need to multithread to prevent long compile times
	*/
	// scans through each pixel, shooting rays out of them and computing what color is seen in the direction
	// of the rays
	// the ray is shot from the "eye" to a pixel through which it computes the ray intersections and then
	// computing as to what color is to be seen at said intersection point
	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			// color vector
			vec3 col(0, 0, 0);

			/*
				TODO: elaborate more?

				What this does is that it shoots rays into the scene and sees if there was anything hit.
				If so, return the color of the supposed hit object and anti-alias it to remove jaggies.
			*/
			for (int z = 0; z < nz; z++)
			{
				// used to blend the foreground with the background for antialiasing
				float u = float(y + randomDouble) / float(nx);
				float v = float(x + randomDouble) / float(ny);

				ray r = cam.getRay(u, v);

				vec3 p = r.point_at_parameter(2.0);

				col += color(r, world, 0);
			}

			// manipulate the gamma to get the desired lighting
			col /= float(nz);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			// write the pixel value to the ppm file
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
		TODO: implement multithreading.
	*/

	thread badThread(startRayTracingProgram);

	if (badThread.joinable())
	{
		badThread.join();
	}

	duration = (clock() - initialTime) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration: " << int(duration / 60) << " minutes and " << fmod(duration, 60) << " seconds." << endl;

	return 0;
}
/*

	END: Main

*/