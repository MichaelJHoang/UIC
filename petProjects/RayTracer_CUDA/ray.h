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
	public:

		vec3 A, B;

		// used for motion blur
		// think cameras: the shutter opens to take a picture then closes - any movement within that interval
		// would produce motion blurs in the picture
		float t;

		/*

			constructors

		*/
		__device__ ray()
		{

		}



		__device__ ray(const vec3& a, const vec3& b)
		{
			A = a;
			B = b;
			t = 0;
		}



		__device__ ray(const vec3& a, const vec3& b, float time)
		{
			A = a;
			B = b;
			t = time;
		}



		__device__ inline vec3 origin() const
		{
			return A;
		}



		__device__ inline vec3 direction() const
		{
			return B;
		}



		__device__ inline float time() const
		{
			return t;
		}

		/*

			Formula for a ray (also called a half-line) = A + tB
			A = origin
			B = direction
			t = distance between A and B

		*/
		__device__ inline vec3 point_at_parameter(float tDist) const
		{
			return A + tDist * B;
		}
};

#endif