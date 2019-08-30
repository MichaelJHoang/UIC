#pragma once
#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

// tell the C++ compiler that the pointer is to a class
class material;

typedef struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;

	// when a ray hits a surface, the pointer will be set to point at the material pointer
	// the object was given initially in main()
	// when the color() method gets this struct, it can call member functions of the material
	// pointer to find out what ray, if any, is scattered.
	material* mat_ptr;
}hitRecord;



/*

	abstract class hitable

*/
class hitable
{
	public:

		/*

			there's a min and max - otherwise rays can go forever

		*/
		__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const = 0;
};

#endif
