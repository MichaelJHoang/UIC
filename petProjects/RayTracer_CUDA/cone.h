#pragma once
#ifndef CONEH
#define CONEH

#include "ray.h"
#include "hitable.h"

class cone : public hitable
{
	vec3 center;
	float radius;
	float height;
	material* mat;

	__device__ cone()
	{

	}


	__device__ cone(vec3 center, float radius, float height, material* mat) : center(center), radius(radius), mat(mat) {}

	__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;

};

__device__ bool cone::hit(const ray& r, float tmin, float tmax, hitRecord& rec) const
{

}

#endif