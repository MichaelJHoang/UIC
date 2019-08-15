#pragma once
#ifndef CAMERAH
#define CAMERAH

#define _USE_MATH_DEFINES
#define randomDouble (rand() / (RAND_MAX + 1.0))

#include <math.h>

#include "ray.h"

vec3 randomInUnitDisk()
{
	vec3 p;

	do
	{
		p = 2.0 * vec3(randomDouble,
					   randomDouble,
					   0) 
					   - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);

	return p;
}



/*

	camera class to allow us how to see the scene

*/

class camera
{
	public:

		// camera properties
		vec3 origin;
		vec3 lowerLeftCorner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		float lensRadius;
		float t0; // open
		float t1; // close


		// vfov is top to bottom in degrees
		camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focusDist, float t0, float t1)
		{
			this->t0 = t0;
			this->t1 = t1;

			lensRadius = aperture / 2;

			float theta = vfov * M_PI / 180;

			// half height - height above the -z axis
			float halfHeight = tan(theta / 2);
			float halfWidth = aspect * halfHeight;

			origin = lookfrom;

			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			// think the lower left corner as (0, 0) in the first quadrant of a graph
			lowerLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;

			// the scene is horizontal by 4 units
			horizontal = 2 * halfWidth * focusDist * u;

			// vertical by 2
			vertical = 2 * halfHeight * focusDist * v;

			// and we're looking at the origin
			// origin = vec3(0.0, 0.0, 0.0);
		}



		ray getRay(float s, float t)
		{
			// return A + tb ~ ray::ray(A, tb)
			vec3 rd = lensRadius * randomInUnitDisk();
			vec3 offset = u * rd.x() + v * rd.y();

			float time = t0 + randomDouble * (t1 - t0);

			return ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset, time);
		}
};

#endif // !CAMERAH
