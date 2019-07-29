#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace vec3
{
	class vec3
	{
		private:
			float e[3] = { 0, 0, 0 };

		public:
			vec3(float e0, float e1, float e2)
			{
				e[0] = e0;
				e[1] = e1;
				e[2] = e2;
			}

			inline float x() const { return e[0]; }
			inline float y() const { return e[1]; }
			inline float z() const { return e[2]; }
			inline float r() const { return e[0]; }
			inline float g() const { return e[1]; }
			inline float b() const { return e[2]; }

			inline const vec3& operator+() const { return *this; }

			inline vec3 operator-() const
			{
				return vec3(-e[0], -e[1], -e[2]);
			}

			inline float operator[] (int x) const
			{
				return e[x];
			}

			inline float& operator[] (int x)
			{
				return e[x];
			}
	};
}



int main()
{
	int nx = 200;
	int ny = 100;

	ofstream outfile;

	outfile.open("raytrace_output.ppm");

	// cout << "P3\n" << nx << " " << ny << "\n255\n";
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	for (int x = ny - 1; x >= 0; x--)
	{
		for (int y = 0; y < nx; y++)
		{
			float r = float(y) / float(nx);
			float g = float(x) / float(ny);
			float b = 0.2;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			// cout << ir << " " << ig << " " << ib << "\n";
			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	outfile.close();

	cout << "Done." << endl;

	return 0;
}