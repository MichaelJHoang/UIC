#pragma once
#ifndef AABBH
#define AABBH

#include "ray.h"

inline float ffmin(float a, float b)
{
	return a < b ? a : b;
}

inline float ffmax(float a, float b)
{
	return a < b ? a : b;
}



class aabb
{
	public:

		vec3 minimum, maximum;

		aabb()
		{

		}

		aabb(const vec3& a, const vec3& b) : minimum(a), maximum(b) {};

		inline vec3 min() const
		{
			return minimum;
		}

		inline vec3 max() const
		{
			return maximum;
		}
};

#endif // !AABBH
