#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

/*

	camera class to allow us how to see the scene

*/
namespace camera
{
	class camera
	{
		public:

			// camera properties
			vec3::vec3 origin;
			vec3::vec3 lowerLeftCorner;
			vec3::vec3 horizontal;
			vec3::vec3 vertical;

			camera()
			{
				// think the lower left corner as (0, 0) in the first quadrant of a graph
				lowerLeftCorner = vec3::vec3(-2.0, -1.0, -1.0);

				// the scene is horizontal by 4 units
				horizontal = vec3::vec3(4.0, 0.0, 0.0);

				// vertical by 2
				vertical = vec3::vec3(0.0, 2.0, 0.0);

				// and we're looking at the origin
				origin = vec3::vec3(0.0, 0.0, 0.0);
			}

			ray::ray getRay(float u, float v)
			{
				// return A + tb ~ ray::ray(A, tb)
				return ray::ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			}
	};
}

#endif // !CAMERAH
