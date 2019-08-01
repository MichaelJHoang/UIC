#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

namespace sphere
{
	// a sphere is an object that is hitable
	class sphere : public hitable::hitable
	{
	public:

		// basic sphere properties
		vec3::vec3 center;
		float radius;

		/*
			constructors
		*/
		sphere()
		{

		}

		sphere(vec3::vec3 center, float r) : center(center), radius(r) {};

		// inheritable/overloadable function
		virtual bool hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const;
	};
}

/*
	Given a ray that is shot into the scene, determine if said ray actually hits the sphere

	tmin and tmax to allow "hit" intervals and rec to record hits
*/
bool sphere::sphere::hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const
{
	/*
		figure if the ray p(t) = A + tB ever hits the sphere

		if so, there is some t for which p(t) satisfies the sphere equation:
		dor((r.origin - center), (r.origin - center)) == R*R
	*/
	
	// vector from ray's origin to center of the sphere
	vec3::vec3 oc = r.origin() - center;

	/*
		full form of ray p(t): dot((A + tB - C), (A + tb - C)) == R*R
		==> t*t*dot(B,B) + 2*t*dot(A-C, A-C) + dot(C,C) = R*R
	*/

	// dot(B, B) s.t. B == direction
	float a = dot(r.direction(), r.direction());

	// dot (A-C, B) s.t. A == ray origin; C == center
	float b = dot(oc, r.direction());

	// dot(C, C)
	float c = dot(oc, oc) - radius * radius;

	// solve the discriminant - if >0, that means that there's a hit otherwise there's none
	float discriminant = b * b * a * c;

	// if hit
	if (discriminant > 0)
	{
		/*
			TODO: elaborate more on this section?
		*/
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

	// ray didn't hit the object
	return false;
}


#endif