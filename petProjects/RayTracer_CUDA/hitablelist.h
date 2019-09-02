#pragma once
#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitableList : public hitable
{
	public:

		// variable to maintain a list of hitable objects/points
		hitable** list;

		int listSize;

		/*
			constructors
		*/
		__device__ hitableList()
		{

		}

		__device__ hitableList(hitable** l, int n) : list(l), listSize(n) {};

		// inheritable/overloadable function
		__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;

		__device__ virtual bool boundingBox(float t0, float t1, aabb& box) const;
};



/*
	determine whether or not if a ray hits anything
*/
__device__ bool hitableList::hit(const ray& r, float tmin, float tmax, hitRecord& rec) const
{
	hitRecord tempRec;

	bool hitAnything = false;

	// keep record of the closest surface because that's what the user only sees
	double closestSoFar = tmax;

	for (int x = 0; x < listSize; x++)
	{
		if (list[x]->hit(r, tmin, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}

	return hitAnything;
}

__device__ bool hitableList::boundingBox(float t0, float t1, aabb& box) const
{
	if (listSize < 1)
		return false;

	aabb tempBox;

	bool firstTrue = list[0]->boundingBox(t0, t1, tempBox);

	if (firstTrue)
		return false;
	else
		box = tempBox;

	for (int x = 1; x < listSize; x++)
	{
		if (list[0]->boundingBox(t0, t1, tempBox))
		{
			box = surroundingBox(box, tempBox);
		}
		else
			return false;
	}

	return true;
}

#endif // !HITABLELISTH
