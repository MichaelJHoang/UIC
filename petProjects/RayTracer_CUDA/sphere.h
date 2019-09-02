#pragma once
#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

// a sphere is an object that is hitable
class sphere : public hitable
{
	public:

		// basic sphere properties
		vec3 center;
		float radius;
		material* mat;

		/*
			constructors
		*/
		__device__ sphere()
		{

		}

		__device__ sphere(vec3 center, float r, material* mat) : center(center), radius(r), mat(mat) {};

		// inheritable/overloadable function
		__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;

		__device__ bool sphere::boundingBox(float t0, float t1, aabb& box) const;
};



/*
	Given a ray that is shot into the scene, determine if said ray actually hits the sphere

	tmin and tmax to allow "hit" intervals and rec to record hits
*/
__device__ bool sphere::hit(const ray& r, float tmin, float tmax, hitRecord& rec) const
{
	/*
		figure if the ray p(t) = A + tB ever hits the sphere

		if so, there is some t for which p(t) satisfies the sphere equation:
		dor((r.origin - center), (r.origin - center)) == R*R
	*/

	// vector from ray's origin subtracted from the center of the sphere
	// to produce a vector that is perpendicular to the surface and pointing out
	vec3 oc = r.origin() - center;

	/*
		full form of ray p(t): dot((A + tB - C), (A + tb - C)) == R*R
		== dot((point - center), (point - center))
		==> t*t*dot(B,B) + 2*t*dot(A-C, A-C) + dot(C,C) = R*R
	*/

	// dot(B, B) s.t. B == direction
	float a = dot(r.direction(), r.direction());

	// dot (A-C, B) s.t. A == ray origin; C == center
	float b = dot(oc, r.direction());

	// dot(C, C)
	float c = dot(oc, oc) - radius * radius;

	// solve the discriminant - if >0, that means that there's a hit otherwise there's none
	float discriminant = b * b - a * c;

	// if hit
	if (discriminant > 0)
	{
		/*
			TODO: elaborate more on this section?
		*/
		// solve "t" with the quadratic formula
		float temp = (-b - sqrt(discriminant)) / a;

		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;

			// id the material of the sphere
			rec.mat_ptr = mat;

			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;

		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;

			// id the material of the sphere
			rec.mat_ptr = mat;

			return true;
		}
	}

	// ray didn't hit the object
	return false;
}



__device__ bool sphere::boundingBox(float t0, float t1, aabb& box) const
{
	box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));

	return true;
}
#endif