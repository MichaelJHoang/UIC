#pragma once
#ifndef CUBEH
#define CUBEH

#include "hitable.h"

class cube : public hitable
{
	public:

		vec3 center;
		material* mat;

		__device__ cube()
		{

		}

		__device__ cube(int x, int y)
		{

		}

		__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;
};

#endif