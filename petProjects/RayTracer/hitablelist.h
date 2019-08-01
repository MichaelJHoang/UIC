#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

namespace hitableList
{
	class hitableList : public hitable::hitable
	{
		public:

			hitable** list;

			int listSize = 0;

			hitableList()
			{

			}

			hitableList(hitable** l, int n) : list(l), listSize(n) {};

			virtual bool hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const;
	};
}

bool hitableList::hitableList::hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const
{
	hitRecord tempRec;

	bool hitAnything = false;

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

#endif // !HITABLELISTH
