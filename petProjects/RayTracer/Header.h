#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable.h"

namespace material
{
	class material
	{
		public:

			virtual bool scatter(const ray::ray& r_in, const hitRecord& rec, vec3::vec3& attenuation, ray::ray& scattered) const = 0;
	};
}

#endif