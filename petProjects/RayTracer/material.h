#pragma once
#ifndef MATERIALH
#define MATERIALH

#include <stdio.h>
#include <math.h>

#include "ray.h"
#include "hitable.h"

// TODO: put this somewhere else?
vec3 randomInUnitSphere()
{
	vec3 p;

	do
	{
		p = 2.0 * vec3((rand() / (RAND_MAX + 1.0)),
			(rand() / (RAND_MAX + 1.0)),
			(rand() / (RAND_MAX + 1.0)))
			- vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);

	return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);

	float dt = dot(uv, n);

	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);

		return true;
	}

	return false;
}

float schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);

	r0 = r0 * r0;

	return r0 + (1 - r0) * pow((1 - cosine), 5);
}






class material
{
	public:

		virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};



class lambertian : public material
{
	public:

		vec3 albedo;

		lambertian(const vec3& v) : albedo(v) {};

		virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const
		{
			vec3 target = rec.p + rec.normal + randomInUnitSphere();

			scattered = ray(rec.p, target - rec.p);

			attenuation = albedo;

			return true;
		}
};



class metal : public material
{
	public:

		vec3 albedo;
		float fuzz;

		metal(const vec3& albedo) : albedo(albedo)
		{
			fuzz = 0;
		}

		metal(const vec3& albedo, float f) : albedo(albedo), fuzz(f) 
		{
			if (f < 1)
				fuzz = f;
			else
				fuzz = 1;
		};

		virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const
		{
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

			scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere());

			attenuation = albedo;

			return (dot(scattered.direction(), rec.normal) > 0);
		}
};

class dielectric : public material
{
	public:
		
		float ref_idx;

		dielectric(float ref_idx) : ref_idx(ref_idx) {};

		virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const
		{
			vec3 outwardNormal;
			vec3 reflected = reflect(r_in.direction(), rec.normal);

			float ni_over_nt;

			attenuation = vec3(1.0, 1.0, 1.0);

			vec3 refracted;

			float reflectProb;
			float cosine;

			if (dot(r_in.direction(), rec.normal) > 0)
			{
				outwardNormal = -rec.normal;

				ni_over_nt = ref_idx;

				cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
				cosine = sqrt(1.0 - ref_idx * ref_idx * (1 - cosine * cosine));
			}
			else
			{
				outwardNormal = rec.normal;

				ni_over_nt = (1.0 / ref_idx);

				cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
			}

			if (refract(r_in.direction(), outwardNormal, ni_over_nt, refracted))
			{
				reflectProb = schlick(cosine, ref_idx);
			}
			else
			{
				reflectProb = 1.0;
			}

			if ((rand() / (RAND_MAX + 1.0)) < reflectProb)
			{
				scattered = ray(rec.p, reflected);
			}
			else
			{
				scattered = ray(rec.p, refracted);
			}

			return true;
		}
};
#endif