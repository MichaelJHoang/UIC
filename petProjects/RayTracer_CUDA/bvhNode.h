#pragma once
#ifndef BVHNODEH
#define BVHNODEH

#include "aabb.h"
#include "hitablelist.h"
#include "curand_kernel.h"

class bvhNode : public hitable
{
	public:

		hitable* left;
		hitable* right;
		aabb box;

		__device__ bvhNode()
		{

		}

		__device__ bvhNode(hitable** l, int n, float t0, float t1, curandState* randState);

		__device__ virtual bool hit(const ray& r, float tmin, float tmax, hitRecord& rec) const;
		
		__device__ virtual bool boundingBox(float t0, float t1, aabb& box) const;
};

__device__ bool bvhNode::boundingBox(float t0, float t1, aabb& box) const 
{
	box = this->box;

	return true;
}

__device__ bool bvhNode::hit(const ray& r, float tmin, float tmax, hitRecord& rec) const
{
	if (box.hit(r, tmin, tmax))
	{
		hitRecord leftRec, rightRec;

		bool leftHit = left->hit(r, tmin, tmax, leftRec);
		bool rightHit = right->hit(r, tmin, tmax, rightRec);

		if (leftHit && rightHit)
		{
			if (leftRec.t < rightRec.t)
				rec = leftRec;
			else
				rec = rightRec;

			return true;
		}
		else if (leftHit)
		{
			rec = leftRec;
			return true;
		}
		else if (rightHit)
		{
			rec = rightRec;
			return true;
		}
		else return false;
	}
	else
		return false;
}



__device__ bvhNode::bvhNode(hitable** list, int n, float t0, float t1, curandState *randState)
{
	int axis = int(3 * curand_uniform(randState));

	if (axis == 0)
		qsort(list, n, sizeof(hitable*), boxXCompare);
	else if (axis == 1)
		qsort(list, n, sizeof(hitable*), boxYCompare);
	else
		qsort(list, n, sizeof(hitable*), boxZCompare);

	if (n == 1)
	{
		left = right = list[0];
	}
	else if (n == 2)
	{
		left = list[0];
		right = list[1];
	}
	else
	{
		left = new bvhNode(list, n / 2, t0, t1);
		right = new bvhNode(list + n / 2, n - n / 2, t0, t1);
	}

	aabb leftBox, rightBox;

	if (!left->boundingBox(t0, t1, leftBox) || !right->boundingBox(t0, t1, rightBox))
		std::cerr << std::endl << "There is no bounding box in the BVH Node constructor" << std::endl;

	box = surroundingBox(leftBox, rightBox);
}



__device__ int boxXCompare(const void* a, const void* b)
{
	aabb leftBox, rightBox;

	hitable* ah = *(hitable * *)a;
	hitable* bh = *(hitable * *)b;

	if (!ah->boundingBox(0, 0, leftBox) || !bh->boundingBox(0, 0, rightBox))
		std::cerr << std::endl << "There is no bounding box in the BVH Node constructor" << std::endl;

	if (leftBox.min().x() - rightBox.min().x() < 0.0f)
	{
		return -1;
	}

	else return 1;
}



__device__ int boxYCompare(const void* a, const void* b)
{
	aabb leftBox, rightBox;

	hitable* ah = *(hitable * *)a;
	hitable* bh = *(hitable * *)b;

	if (!ah->boundingBox(0, 0, leftBox) || !bh->boundingBox(0, 0, rightBox))
		std::cerr << std::endl << "There is no bounding box in the BVH Node constructor" << std::endl;

	if (leftBox.min().y() - rightBox.min().y() < 0.0f)
	{
		return -1;
	}

	else return 1;
}



__device__ int boxZCompare(const void* a, const void* b)
{
	aabb leftBox, rightBox;

	hitable* ah = *(hitable * *)a;
	hitable* bh = *(hitable * *)b;

	if (!ah->boundingBox(0, 0, leftBox) || !bh->boundingBox(0, 0, rightBox))
		std::cerr << std::endl << "There is no bounding box in the BVH Node constructor" << std::endl;

	if (leftBox.min().z() - rightBox.min().z() < 0.0f)
	{
		return -1;
	}
	else return 1;
}
#endif // !BVHNODEH
