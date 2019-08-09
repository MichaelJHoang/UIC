#pragma once
#ifndef RAYH
#define RAYH

#include "vec3.h"

/*

	Ray class and related functions, is a necessity because without it, there'd
	be no "ray" in RAYtracing.

*/
class ray
{
	private:

	public:

		vec3 A, B;

		/*
		
			constructors

		*/
		ray()
		{

		}



		ray(const vec3& a, const vec3& b)
		{
			A = a;
			B = b;
		}



		vec3 origin() const
		{
			return A;
		}



		vec3 direction() const
		{
			return B;
		}



		/*
		
			Forumla for a ray (also called a half-line) = A + tB
			A = origin
			B = direction
			t = distance between A and B

		*/
		vec3 point_at_parameter(float t) const
		{
			return A + t * B;
		}
};

#endif