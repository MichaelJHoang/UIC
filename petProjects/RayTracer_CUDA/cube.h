#pragma once
#ifndef CUBEH
#define CUBEH

#include "hitable.h"

class cube : public hitable
{
	public:

		vec3 center;
		material* mat;

		vec3 bounds[2];

		__device__ cube()
		{

		}

		__device__ cube(const vec3& min, const vec3& max)
		{
			bounds[0] = min;
			bounds[1] = max;
		}

		__device__ virtual bool hit(const ray& r, float t0, float t1, hitRecord& rec) const;
};

// http://www.cs.utah.edu/~awilliam/box/box.pdf
__device__ bool cube::hit(const ray& r, float t0, float t1, hitRecord& rec) const
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	if (r.direction().x() >= 0)
	{

	}
}
#endif