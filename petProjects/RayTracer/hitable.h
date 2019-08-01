#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

typedef struct hit_record
{
	float t;
	vec3::vec3 p;
	vec3::vec3 normal;
}hitRecord;

/*

	abstract class hitable

*/
namespace hitable
{ 
	class hitable
	{
		public:

			/*
		
				there's a min and max - otherwise rays can go forever
		
			*/
			virtual bool hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const = 0;
	};
}

#endif
