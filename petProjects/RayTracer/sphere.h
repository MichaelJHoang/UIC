#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

namespace sphere
{
	class sphere : public hitable::hitable
	{
	public:

		vec3::vec3 center;
		float radius;

		sphere()
		{

		}

		sphere(vec3::vec3 center, float r) : center(center), radius(r) {};

		virtual bool hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const;

	};
}

bool sphere::sphere::hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const
{
	vec3::vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b * a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;

		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;

			return true;
		}

		temp = (-b + sqrt(b * b - a * c)) / a;

		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;

			return true;
		}
	}

	return false;
}


#endif