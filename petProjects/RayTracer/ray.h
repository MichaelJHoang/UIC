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

		// used for motion blur
		// think cameras: the shutter opens to take a picture then closes - any movement within that interval
		// would produce motion blurs in the picture
		float t;

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
			t = 0;
		}



		ray(const vec3& a, const vec3& b, float time)
		{
			A = a;
			B = b;
			t = time;
		}



		inline vec3 origin() const
		{
			return A;
		}



		inline vec3 direction() const
		{
			return B;
		}

		

		inline float time() const
		{
			return t;
		}

		/*
		
			Forumla for a ray (also called a half-line) = A + tB
			A = origin
			B = direction
			t = distance between A and B

		*/
		inline vec3 point_at_parameter(float tDist) const
		{
			return A + tDist * B;
		}
};

#endif