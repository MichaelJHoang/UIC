#pragma once
#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

class material;

typedef struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
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
		virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const = 0;
};

#endif
