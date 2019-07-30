#ifndef RAYH
#define RAYH

#include "vec3.h"

/*

	Ray class and related functions

*/
namespace ray
{
	class ray
	{
	private:

	public:

		vec3::vec3 A, B;

		ray()
		{

		}

		ray(const vec3::vec3& a, const vec3::vec3& b)
		{
			A = a;
			B = b;
		}

		vec3::vec3 origin() const
		{
			return A;
		}

		vec3::vec3 direction() const
		{
			return B;
		}

		vec3::vec3 point_at_parameter(float t) const
		{
			return A + t * B;
		}
	};
}

#endif