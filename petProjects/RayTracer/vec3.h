#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

/*

	Vector vec3 class and vector related functions

*/
// vec3 namespace to prevent clashing with other, potential vec3 libraries or something
namespace vec3
{
	// vector class
	class vec3
	{
		private:


		public:

			float e[3] = { 0, 0, 0 };

			// constructors
			vec3()
			{
			}

			vec3(float e0, float e1, float e2)
			{
				e[0] = e0;
				e[1] = e1;
				e[2] = e2;
			}

			// basic getters
			inline float x() const { return e[0]; }
			inline float y() const { return e[1]; }
			inline float z() const { return e[2]; }
			inline float r() const { return e[0]; }
			inline float g() const { return e[1]; }
			inline float b() const { return e[2]; }

			// operator overloaders - which is relatively modern C++
			// and allows me to easily do matrix arithmetic
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

			inline vec3& operator+= (const vec3& v)
			{
				e[0] += v.e[0];
				e[1] += v.e[1];
				e[2] += v.e[2];

				return *this;
			}

			inline vec3& operator-= (const vec3& v)
			{
				e[0] -= v.e[0];
				e[1] -= v.e[1];
				e[2] -= v.e[2];

				return *this;
			}

			inline vec3& operator*= (const vec3& v)
			{
				e[0] *= v.e[0];
				e[1] *= v.e[1];
				e[2] *= v.e[2];

				return *this;
			}

			inline vec3& operator/= (const vec3& v)
			{
				e[0] /= v.e[0];
				e[1] /= v.e[1];
				e[2] /= v.e[2];

				return *this;
			}

			inline vec3& operator*= (const float t)
			{
				e[0] *= t;
				e[1] *= t;
				e[2] *= t;

				return *this;
			}

			inline vec3& operator/= (const float t)
			{
				e[0] *= (1.0 / t);
				e[1] *= (1.0 / t);
				e[2] *= (1.0 / t);

				return *this;
			}



			// following the formula for getting the distance of a vector
			inline float length() const
			{
				return sqrt(e[0] * e[0] +
							e[1] * e[1] +
							e[2] * e[2]);
			}

			inline float squared_length() const
			{
				return this->length() * this->length();
			}

			// retrieve a normed vector space, which is basically a vector of length 1
			inline void make_unit_vector();
	};
}

// basic matrix addition,
inline vec3::vec3 operator+ (const vec3::vec3& v1, const vec3::vec3& v2)
{
	return vec3::vec3(v1.e[0] + v2.e[0],
					  v1.e[1] + v2.e[1],
					  v1.e[2] + v2.e[2]);
}

// subtraction,
inline vec3::vec3 operator- (const vec3::vec3& v1, const vec3::vec3& v2)
{
	return vec3::vec3(v1.e[0] - v2.e[0],
					  v1.e[1] - v2.e[1],
					  v1.e[2] - v2.e[2]);
}

// multiplication,
inline vec3::vec3 operator* (const vec3::vec3& v, const float n)
{
	return vec3::vec3(v.e[0] * n,
					  v.e[1] * n,
					  v.e[2] * n);
}

inline vec3::vec3 operator* (const float n, const vec3::vec3& v)
{
	return vec3::vec3(v.e[0] * n,
					  v.e[1] * n,
					  v.e[2] * n);
}

// and division
inline vec3::vec3 operator/ (const vec3::vec3& v, const float n)
{
	return vec3::vec3(v.e[0] / n,
					  v.e[1] / n,
					  v.e[2] / n);
}

inline vec3::vec3 operator/ (const float n, const vec3::vec3& v)
{
	return vec3::vec3(v.e[0] / n,
					  v.e[1] / n,
					  v.e[2] / n);
}

// given a vector, return its unit vector
// making the unit vector in the same direction as the input vector
inline vec3::vec3 unit_vector(vec3::vec3 v)
{
	return v / v.length();
}

// dot product
inline float dot(const vec3::vec3& v1, const vec3::vec3& v2)
{
	return v1.e[0] * v2.e[0] +
		   v1.e[1] * v2.e[1] +
		   v1.e[2] * v2.e[2];
}

// cross product
inline vec3::vec3 cross(const vec3::vec3& v1, const vec3::vec3& v2)
{
	return vec3::vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
					 (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
					 (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}
/*

	END: Vector vec3 class and vector related functions

*/

#endif