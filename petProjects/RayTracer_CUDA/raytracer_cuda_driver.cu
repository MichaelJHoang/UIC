/*
 *
 *	Author: Jon-Michael Hoang
 *
 *	What this is: This is a ray tracer program that I developed based off of some textbooks, papers and blogs (citations coming soon).
 *				  What ray tracing is is that it's an algorithm in computer graphics that enables
 *				  one to render life-like light and shadows.
 *
 *	How to use this: Simply compile and go to the directory of this program to find a
 *					 "raytrace_output.ppm" file, toss it into a NetPBM viewer and see the results
 *					 The reason as to why I'm doing this is because it allows for faster computation.
 *					 However, I will later find a way to use this with OpenGL.
 *
 */

#pragma once

// standard libraries used for this project
#include <iostream>
#include <time.h>
#include <fstream>

// CUDA libraries used for this project
#include <curand_kernel.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// programmer-defined includes
#include "vec3.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include "hitable.h"
#include "hitablelist.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"
#include "movingSphere.h"

// TODO: probably have glut work?
#include "GL\freeglut.h"

using namespace std;

// every CUDA API call that is made will return an error code that should be checked
// in this function, catch it and handle it
#define checkCudaErrors(val) checkCuda((val), #val, __FILE__, __LINE__)

void checkCuda(cudaError_t result,
			   char const* const function,
			   const char* const file,
			   int const line)
{
	if (result)
	{
		cerr << "CUDA error = " << static_cast<unsigned int> (result)
			 << " at " << file << ": " << line
			 << " [" << function << "] \n";

		// make sure to call the device reset before exiting
		cudaDeviceReset();

		exit(99);
	}
}



__global__ void randInit(curandState* randState)
{
	if (threadIdx.x == 0 && blockIdx.x == 0)
		curand_init(1337, 0, 0, randState);
}



/*
	TODO: Comment
*/
__device__ vec3 color(const ray& r, hitable** world, int depth, curandState *randState)
{
	ray currentRay = r;
	vec3 currentAttenuation = vec3(1.0f, 1.0f, 1.0f);

	// 50 iterations
	for (int x = 0; x < 50; x++)
	{
		hitRecord rec;

		if ((*world)->hit(currentRay, 0.01f, FLT_MAX, rec))
		{
			ray scattered;
			vec3 attenuation;

			if (rec.mat_ptr->scatter(currentRay, rec, attenuation, scattered, randState))
			{
				currentAttenuation *= attenuation;

				currentRay = scattered;
			}
			else
				return vec3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			vec3 unitDirection = unit_vector(currentRay.direction());

			float t = 0.5f * (unitDirection.y() + 1.0f);

			// make the background with
			// linear interpolation
			vec3 c = (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);

			return currentAttenuation * c;
		}
	}

	return vec3(0.0f, 0.0f, 0.0f);
}



__global__ void renderInit(int xMax, int yMax, curandState* randState)
{
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;

	if ((x >= xMax) || (y >= yMax))
		return;

	int pixelIndex = y * xMax + x;

	// threads have the same seed with different sequences and no offsets
	curand_init(1337, pixelIndex, 0, &randState[pixelIndex]);
}



__global__ void render(vec3* fb, int xMax, int yMax, int numSamples, camera **cam, hitable **world, curandState *randState)
{
	// identify the coordinates of each thread in the image so 
	// the program knows how to calculate the final color
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;

	if ((x >= xMax) || (y >= yMax))
		return;

	int pixelIndex = y * xMax + x;

	curandState thisRandState = randState[pixelIndex];

	vec3 col(0.0f, 0.0f, 0.0f);

	for (int sample = 0; sample < numSamples; sample++)
	{
		float u = float(x + curand_uniform(&thisRandState)) / float(xMax);
		float v = float(y + curand_uniform(&thisRandState)) / float(yMax);

		ray r = (*cam)->getRay(u, v, &thisRandState);

		col += color(r, world, 0, &thisRandState);
	}

	randState[pixelIndex] = thisRandState;

	col /= float(numSamples);

	fb[pixelIndex] = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
}



__global__ void randomScene(hitable** list, hitable** world, camera** cam, int nx, int ny, curandState* randState) 
{
	if (threadIdx.x == 0 && blockIdx.x == 0)
	{
		curandState* thisRandState = randState;

		theTexture* checker = new checkerTexture(new constantTexture(vec3(.0f, .0f, .0f)),
							  new constantTexture(vec3(.9f, .9f, .9f)));

		list[0] = new sphere(vec3(0.0f, -1000.0f, -1), 1000.0f,
				  new lambertian(checker));

		int x = 1;

		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				float chooseMat = curand_uniform(thisRandState);

				vec3 center(a + .9f * curand_uniform(thisRandState),
							.2f,
							b + .9f * curand_uniform(thisRandState));

				// diffuse
				if (chooseMat < .8f)
				{
					list[x++] = new movingSphere(center,
												 center + vec3(0.0f, .5f * curand_uniform(thisRandState), 0.0f),
												 0.0f, 1.0f, .2f,
												 new lambertian(vec3(
												 curand_uniform(thisRandState) * curand_uniform(thisRandState),
												 curand_uniform(thisRandState) * curand_uniform(thisRandState),
												 curand_uniform(thisRandState) * curand_uniform(thisRandState))));
				}
				// metal
				else if (chooseMat < .95f)
				{
					list[x++] = new sphere(center,
										   .2f,
										   new metal (vec3(.5f * (1.0f + curand_uniform(thisRandState)),
														   .5f * (1.0f + curand_uniform(thisRandState)),
														   .5f * (1.0f + curand_uniform(thisRandState)))));
				}
				// glass
				else
				{
					list[x++] = new sphere(center, .2f, new dielectric(1.5f));
				}
			}
		}

		list[x++] = new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f));
		list[x++] = new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(vec3(0.4f, 0.2f, 0.1f)));
		list[x++] = new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));

		randState = thisRandState;

		*world = new hitableList(list, 22 * 22 + 1 + 3);

		vec3 lookfrom(13.0f, 2.0f, 3.0f);
		vec3 lookat(0.0f, 0.0f, 0.0f);
		vec3 vup(0.0f, 1.0f, 0.0f);

		float distToFocus = 10.0f;
		float aperture = 0.0f;

		*cam = new camera(lookfrom, 
						  lookat, 
						  vup, 
						  30.0f, 
						  float(nx) / float(ny), 
						  aperture, 
						  distToFocus, 
						  0.0f, 1.0f);
	}
}



__global__ void freeWorld(hitable** list, hitable** world, camera** cam) 
{
	for (int x = 0; x < 22 * 22 + 4; x++) 
	{
		delete ((sphere*)list[x])->mat;
		delete list[x];
	}
	delete* world;
	delete* cam;
}



__host__ void startRayTracingProgram()
{
	// scene dimensions
	int nx = 800;
	int ny = 400;

	// number of samples per pixel
	int numSamples = 400;

	// divide the work on the GPU into tx x ty blocks of threads
	int tx = 16;
	int ty = 16;

	// as of current, the program writes to a ppm file.
	// maybe create an application window to display result?
	ofstream outfile("raytrace_cuda_output.ppm");
	//outfile.open("raytrace_cuda_output.ppm");

	// allocate numPixels sized frame buffer on the host to hold the RGB values calculated
	// by the GPU
	int numPixels = nx * ny;
	size_t fbSize = numPixels * sizeof(vec3);

	// allocate frame buffer
	vec3* frameBuffer;

	// allocate unified memory
	checkCudaErrors(cudaMallocManaged((void**)& frameBuffer, fbSize));

	// allocate randomState
	curandState* randState;
	checkCudaErrors(cudaMalloc((void**)&randState, numPixels * sizeof(curandState)));

	curandState* randState2;
	checkCudaErrors(cudaMalloc((void**)&randState2, sizeof(curandState)));

	// 2nd random state initialized for world creation
	randInit << <1, 1 >> > (randState2);

	checkCudaErrors(cudaGetLastError());
	// let the CPU know that the GPU is done
	checkCudaErrors(cudaDeviceSynchronize());

	//
	// allocate scene's objects onto the GPU with cudaMalloc
	//

	// creates a list of hitable objects
	hitable** list;
	int numHitables = 22 * 22 + 1 + 3;

	checkCudaErrors(cudaMalloc((void**) & list, numHitables * sizeof(hitable*)));

	// creates the world that will contain the objects
	hitable** world;

	checkCudaErrors(cudaMalloc((void**)& world, sizeof(hitable*)));

	// and the camera that would allow use to look at the world in a certain
	// camera angle
	camera** cam;
	
	checkCudaErrors(cudaMalloc((void**)& cam, sizeof(camera*)));

	randomScene << <1, 1 >> > (list, world, cam, nx, ny, randState2);

	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	// render the buffer
	dim3 blocks(nx / tx + 1, ny / ty + 1);
	dim3 threads(tx, ty);

	renderInit << <blocks, threads >> > (nx, ny, randState);

	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	render << <blocks, threads >> > (frameBuffer, nx, ny, numSamples, cam, world, randState);

	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	outfile << "P3\n"
			<< nx << " "
			<< ny << " "
			<< "\n255\n";

	cerr << "P3\n"
		<< nx << " "
		<< ny << " "
		<< "\n255\n";

	// output the frame buffer into the ppm file
	for (int y = ny - 1; y >= 0; y--)
	{
		for (int x = 0; x < nx; x++)
		{
			size_t pixelIndex = y * nx + x;

			int ir = int(255.99f * frameBuffer[pixelIndex].r());
			int ig = int(255.99f * frameBuffer[pixelIndex].g());
			int ib = int(255.99f * frameBuffer[pixelIndex].b());

			outfile << ir << " "
					<< ig << " "
					<< ib << "\n";

			cerr << ir << " "
				<< ig << " "
				<< ib << "\n";
		}
	}

	// clean up
	checkCudaErrors(cudaDeviceSynchronize());

	//freeWorld << <1, 1 >> > (list, world, cam);

	// TODO: somehow, freeing up these causes a seg-fault;
	//       need to fix.

	try
	{
		checkCudaErrors(cudaFree(cam));
		checkCudaErrors(cudaFree(world));
		checkCudaErrors(cudaFree(list));
		checkCudaErrors(cudaFree(randState));
		checkCudaErrors(cudaFree(randState2));
		checkCudaErrors(cudaFree(frameBuffer));
	}
	catch (exception e)
	{
		cout << endl << e.what() << endl;
	}

	outfile.close();

	cout << "Ray-Tracing complete" << endl;

	cudaDeviceReset();
}



/*

	Main

*/
int main(int argc, char** argv)
{
	std::cout << "Running the Ray-Tracing program, this might take awhile..." << endl;

	// time how long it takes for the thing to finish
	clock_t initialTime = clock();
	double duration = 0.0;

	startRayTracingProgram();

	duration = (clock() - initialTime) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration: " << int(duration / 60) << " minutes and " << fmod(duration, 60) << " seconds." << endl;

	//system("xdg-open raytrace_cuda_output.ppm");

	return 0;
}
/*

	END: Main

*/