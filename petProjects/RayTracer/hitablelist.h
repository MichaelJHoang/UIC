#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

namespace hitableList
{
	class hitableList : public hitable::hitable
	{
		public:

			// variable to maintain a list of hitable objects/points
			hitable** list;

			int listSize = 0;

			/*
				constructors
			*/
			hitableList()
			{

			}

			hitableList(hitable** l, int n) : list(l), listSize(n) {};

			// inheritable/overloadable function
			virtual bool hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const;
	};
}

/*
	determine whether or not if a ray hits anything
*/
bool hitableList::hitableList::hit(const ray::ray& r, float tmin, float tmax, hitRecord& rec) const
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

#endif // !HITABLELISTH
