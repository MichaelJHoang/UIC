#pragma once
#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

#include <curand_kernel.h>

/*

	Vector vec3 class and vector related functions

*/

// vector class
class vec3
{
	public:

		float e[3] = { 0.0f, 0.0f, 0.0f };

		// constructors
		__host__ __device__ vec3()
		{
		}



		__host__ __device__ vec3(float e0, float e1, float e2)
		{
			e[0] = e0;
			e[1] = e1;
			e[2] = e2;
		}



		// basic getters
		__host__ __device__ inline float x() const { return e[0]; }
		__host__ __device__ inline float y() const { return e[1]; }
		__host__ __device__ inline float z() const { return e[2]; }
		__host__ __device__ inline float r() const { return e[0]; }
		__host__ __device__ inline float g() const { return e[1]; }
		__host__ __device__ inline float b() const { return e[2]; }



		// operator overloaders - which is relatively modern C++
		// and allows me to easily do matrix arithmetic
		__host__ __device__ inline const vec3& operator+() const { return *this; }

		__host__ __device__ inline vec3 operator-() const
		{
			return vec3(-e[0], -e[1], -e[2]);
		}

		__host__ __device__ inline float operator[] (int x) const
		{
			return e[x];
		}

		__host__ __device__ inline float& operator[] (int x)
		{
			return e[x];
		}

		__host__ __device__ inline vec3& operator+= (const vec3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];

			return *this;
		}

		__host__ __device__ inline vec3& operator-= (const vec3& v)
		{
			e[0] -= v.e[0];
			e[1] -= v.e[1];
			e[2] -= v.e[2];

			return *this;
		}

		__host__ __device__ inline vec3& operator*= (const vec3& v)
		{
			e[0] *= v.e[0];
			e[1] *= v.e[1];
			e[2] *= v.e[2];

			return *this;
		}

		__host__ __device__ inline vec3& operator/= (const vec3& v)
		{
			e[0] /= v.e[0];
			e[1] /= v.e[1];
			e[2] /= v.e[2];

			return *this;
		}

		__host__ __device__ inline vec3& operator*= (const float t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;

			return *this;
		}

		__host__ __device__ inline vec3& operator/= (const float t)
		{
			e[0] *= (1.0f / t);
			e[1] *= (1.0f / t);
			e[2] *= (1.0f / t);

			return *this;
		}



		// following the formula for getting the distance of a vector
		__host__ __device__ inline float length() const
		{
			return sqrt(e[0] * e[0] +
				e[1] * e[1] +
				e[2] * e[2]);
		}



		__host__ __device__ inline float squared_length() const
		{
			return this->length() * this->length();
		}
};



// basic matrix addition,
__host__ __device__ inline vec3 operator+ (const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] + v2.e[0],
		v1.e[1] + v2.e[1],
		v1.e[2] + v2.e[2]);
}

// subtraction,
__host__ __device__ inline vec3 operator- (const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] - v2.e[0],
		v1.e[1] - v2.e[1],
		v1.e[2] - v2.e[2]);
}

// multiplication,
__host__ __device__ inline vec3 operator* (const vec3& v, const float n)
{
	return vec3(v.e[0] * n,
		v.e[1] * n,
		v.e[2] * n);
}

__host__ __device__ inline vec3 operator* (const float n, const vec3& v)
{
	return vec3(v.e[0] * n,
		v.e[1] * n,
		v.e[2] * n);
}

__host__ __device__ inline vec3 operator* (const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] * v2.e[0],
		v1.e[1] * v2.e[1],
		v1.e[2] * v2.e[2]);
}

// and division
__host__ __device__ inline vec3 operator/ (const vec3& v, const float n)
{
	return vec3(v.e[0] / n,
		v.e[1] / n,
		v.e[2] / n);
}

__host__ __device__ inline vec3 operator/ (const float n, const vec3& v)
{
	return vec3(v.e[0] / n,
		v.e[1] / n,
		v.e[2] / n);
}

__host__ __device__ inline vec3 operator/ (const vec3& v1, const vec3& v2)
{
	return vec3(v1.e[0] / v2.e[0],
		v1.e[1] / v2.e[1],
		v1.e[2] / v2.e[2]);
}
// given a vector, return its unit vector
// making the unit vector in the same direction as the input vector
__host__ __device__ inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}



// dot product
__host__ __device__ inline float dot(const vec3& v1, const vec3& v2)
{
	return v1.e[0] * v2.e[0] +
		v1.e[1] * v2.e[1] +
		v1.e[2] * v2.e[2];
}



// cross product
__host__ __device__ inline vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}
/*

	END: Vector vec3 class and vector related functions

*/

#endif