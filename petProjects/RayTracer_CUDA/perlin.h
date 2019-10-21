#pragma once
#ifndef PERLINH
#define PERLINH

#include "hitable.h"

class perlin
{
	public:

		static float* randomFloat;
		static int* permX, *permY, *permZ;
		static curandState* randState;

		__device__ perlin() {}

		__device__ float noise(const vec3& p) const
		{
			float u = p.x() - floor(p.x());
			float v = p.y() - floor(p.y());
			float w = p.z() - floor(p.z());

			int i = int(4 * p.x()) & 255;
			int j = int(4 * p.y()) & 255;
			int k = int(4 * p.z()) & 255;

			return randomFloat[permX[i] ^ permY[j] ^ permZ[k]];
		}
};



__device__ static float* perlinGenerate(curandState *randState)
{
	float* p = new float[256];
	
	for (int x = 0; x < 256; ++x)
	{
		p[x] = curand_uniform(randState);
	}

	return p;
}



__device__ void permute(int* p, int n, curandState *randState)
{
	for (int x = n - 1; x > 0; x--)
	{
		int target = int(curand_uniform(randState) * (x + 1));
		int temp = p[x];
		p[x] = p[target];
		p[target] = temp;
	}

	return;
}



__device__ static int* perlinGeneratePerm(curandState *randState)
{
	int* p = new int[256];

	for (int x = 0; x < 256; x++)
	{
		p[x] = x;
	}

	permute(p, 256, randState);

	return p;
}

float* perlin::randomFloat = perlinGenerate(perlin::randState);
int* perlin::permX = perlinGeneratePerm(perlin::randState);
int* perlin::permY = perlinGeneratePerm(perlin::randState);
int* perlin::permZ = perlinGeneratePerm(perlin::randState);

#endif