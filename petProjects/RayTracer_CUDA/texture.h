#pragma once
#ifndef TEXTUREH
#define TEXTUREH

#include "ray.h"


class theTexture
{
	public:

		__device__ theTexture()
		{

		}

		__device__ virtual vec3 value(float u, float v, const vec3& p) const = 0;
};



class constantTexture : public theTexture
{
	public:

		vec3 color;

		__device__ constantTexture()
		{

		}

		__device__ constantTexture(vec3 color) : color(color) {}

		__device__ virtual vec3 value(float u, float v, const vec3& p) const
		{
			return color;
		}
};



class checkerTexture : public theTexture
{
	public:

		theTexture* odd;
		theTexture* even;

		__device__ checkerTexture()
		{

		}

		__device__ checkerTexture(theTexture* texture0, theTexture* texture1) : even(texture0), odd(texture1) {}

		__device__ virtual vec3 value(float u, float v, const vec3& p) const
		{
			float sines = sin(10.0f * p.x()) * sin(10.0f * p.y()) * sin(10.0f * p.z());

			if (sines < 0)
				return odd->value(u, v, p);
			else
				return even->value(u, v, p);
		}
};

#endif