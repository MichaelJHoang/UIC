#pragma once
#ifndef AABBH
#define AABBH

#include "ray.h"

__device__ inline float ffmin(float a, float b)
{
	return a < b ? a : b;
}

__device__ inline float ffmax(float a, float b)
{
	return a > b ? a : b;
}

class aabb
{
	public:

		vec3 minimum, maximum;

		__device__ aabb()
		{

		}

		__device__ aabb(const vec3& a, const vec3& b) : minimum(a), maximum(b) {}

		__device__ vec3 min() const
		{
			return minimum;
		}

		__device__ vec3 max() const
		{
			return maximum;
		}

		/*
			__device__ bool hit(const ray& r, float tmin, float tmax) const
			{
				for (int x = 0; x < 3; x++)
				{
					float t0 = ffmin((minimum[x] - r.origin[x]) / r.direction()[x],
									 (maximum[x] - r.origin()[x]) / r.direction()[x]);

					float t1 = ffmax((minimum[x] - r.origin[x]) / r.direction()[x],
									 (maximum[x] - r.origin()[x]) / r.direction()[x]);

					tmin = ffmax(t0, tmin);
					tmax = ffmin(t1, tmax);

					if (tmax <= tmin)
						return false;
				}

				return true;
			}
		*/

		__device__ bool hit(const ray& r, float tmin, float tmax) const;
};



__device__ inline bool aabb::hit(const ray& r, float tmin, float tmax) const
{
	for (int x = 0; x < 3; x++)
	{
		float inverseD = 1.0f / r.direction()[x];

		float t0 = (min()[x] - r.origin()[x]) * inverseD;
		float t1 = (max()[x] - r.origin()[x]) * inverseD;

		if (inverseD < 0.0f)
		{
			std::swap(t0, t1);
		}

		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;

		if (tmax <= tmin)
			return false;
	}

	return true;
}

__device__ aabb surroundingBox(aabb box0, aabb box1)
{
	vec3 small(fmin(box0.min().x(), box1.min().x()),
			   fmin(box0.min().y(), box1.min().y()),
			   fmin(box0.min().z(), box1.min().z()));

	vec3 big(fmax(box0.max().x(), box1.max().x()),
			 fmax(box0.min().y(), box1.min().y()),
			 fmax(box0.max().z(), box1.max().z()));
}


#endif