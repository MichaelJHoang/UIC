#pragma once
#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "hitable.h"

vec3 randomInUnitSphere();
vec3 reflect(const vec3& v, const vec3& n);


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

		metal(const vec3& albedo) : albedo(albedo) {};

		virtual bool scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const
		{
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

			scattered = ray(rec.p, reflected);

			attenuation = albedo;

			return (dot(scattered.direction(), rec.normal) > 0);
		}
};


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
	} while (dot(p, p) >= 1.0);

	return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}


#endif