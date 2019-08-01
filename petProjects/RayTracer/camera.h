#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

namespace camera
{
	class camera
	{
		public:

			camera()
			{
				lowerLeftCorner = vec3::vec3(-2.0, -1.0, -1.0);
				horizontal = vec3::vec3(4.0, 0.0, 0.0);
				vertical = vec3::vec3(0.0, 2.0, 0.0);
				origin = vec3::vec3(0.0, 0.0, 0.0);
			}

			ray::ray getRay(float u, float v)
			{
				return ray::ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			}

			vec3::vec3 origin;
			vec3::vec3 lowerLeftCorner;
			vec3::vec3 horizontal;
			vec3::vec3 vertical;
	};
}

#endif // !CAMERAH
