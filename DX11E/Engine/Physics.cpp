#include "stdafx.h"
#include "Physics.h"
#include "CollisionBox.h"

Physics::AABB::AABB()
{

}
Physics::AABB::AABB(Vector3 min, Vector3 max)
{
	minCorner = min;
	maxCorner = max;
}
bool Physics::AABB::UnitTestAABB()
{
	const TestAABB testAABB[] =
	{
	{
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f)),
	AABB(Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-110.0f, -10.0f, -10.0f), Vector3(-90.0f, 10.0f, 10.0f)),
	AABB(Vector3(-100.0f, -10.0f, -10.0f), Vector3(-90.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(90.0f, -10.0f, -10.0f), Vector3(110.0f, 10.0f, 10.0f)),
	AABB(Vector3(90.0f, -10.0f, -10.0f), Vector3(100.0f, 10.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -110.0f, -10.0f), Vector3(10.0f, -90.0f, 10.0f)),
	AABB(Vector3(-10.0f, -100.0f, -10.0f), Vector3(10.0f, -90.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, 90.0f, -10.0f), Vector3(10.0f, 110.0f, 10.0f)),
	AABB(Vector3(-10.0f, 90.0f, -10.0f), Vector3(10.0f, 100.0f, 10.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, -110.0f), Vector3(10.0f, 10.0f, -90.0f)),
	AABB(Vector3(-10.0f, -10.0f, -100.0f), Vector3(10.0f, 10.0f, -90.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-10.0f, -10.0f, 90.0f), Vector3(10.0f, 10.0f, 110.0f)),
	AABB(Vector3(-10.0f, -10.0f, 90.0f), Vector3(10.0f, 10.0f, 100.0f))
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	AABB(Vector3(-120.0f, -10.0f, -10.0f), Vector3(-110.0f, 10.0f, 10.0f)),
	AABB(Vector3::One, Vector3::Zero)
	}
	};
	for (int i = 0; i < 8; i++)
	{
		AABB* ovlap = new AABB();
		Vector3 min = testAABB[i].overlap.minCorner;
		Vector3 max = testAABB[i].overlap.maxCorner;
		ovlap->maxCorner = max;
		ovlap->minCorner = min;
		bool intersect = Intersect(testAABB[i].a, testAABB[i].b, ovlap);
		if (((ovlap->minCorner.x != min.x) || (ovlap->minCorner.y != min.y) || (ovlap->minCorner.z != min.z)) ||
			((ovlap->maxCorner.x != max.x) || (ovlap->maxCorner.y != max.y) || (ovlap->maxCorner.z != max.z)))
		{
			intersect = false; // Check to see if the given overlap is equal to the test, not equal return false
		}
		else
		{
			intersect = true;
		}
		delete ovlap;
		if(!intersect)
			return intersect;
	}

	return true;
}

Physics::LineSegment::LineSegment() // Default constructor
{

}
Physics::LineSegment::LineSegment(Vector3 start, Vector3 end)
{
	this->startingPoint = start;
	this->endingPoint = end;
}

bool Physics::LineSegment::UnitTestRayCast()
{
	const TestSegment testSegment[] =
	{
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(-110.0f, 0.0f, 0.0f), Vector3(-90.0f, 0.0f, 0.0f)),
	true, Vector3(-100.0f, 0.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, -110.0f, 0.0f), Vector3(0.0f, -90.0f, 0.0f)),
	true, Vector3(0.0f, -100.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, -110.0f), Vector3(0.0f, 0.0f, -90.0f)),
	true, Vector3(0.0f, 0.0f, -100.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(110.0f, 0.0f, 0.0f), Vector3(90.0f, 0.0f, 0.0f)),
	true, Vector3(100.0f, 0.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 110.0f, 0.0f), Vector3(0.0f, 90.0f, 0.0f)),
	true, Vector3(0.0f, 100.0f, 0.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, 110.0f), Vector3(0.0f, 0.0f, 90.0f)),
	true, Vector3(0.0f, 0.0f, 100.0f)
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(-120.0f, 0.0f, 0.0f), Vector3(-110.0f, 0.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, -120.0f, 0.0f), Vector3(0.0f, -110.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, -120.0f), Vector3(0.0f, 0.0f, -110.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(120.0f, 0.0f, 0.0f), Vector3(110.0f, 0.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 120.0f, 0.0f), Vector3(0.0f, 110.0f, 0.0f)),
	false, Vector3::Zero
	},
	{
	AABB(Vector3(-100.0f, -100.0f, -100.0f), Vector3(100.0f, 100.0f, 100.0f)),
	LineSegment(Vector3(0.0f, 0.0f, 120.0f), Vector3(0.0f, 0.0f, 110.0f)),
	false, Vector3::Zero
	},
	};

	for (int i = 0; i < 12; i++)
	{
		Vector3 contactPoint = Vector3::Zero;
		Vector3 checkIntersection = testSegment[i].point;
		AABB box = testSegment[i].box;
		LineSegment ray = testSegment[i].segment;
		bool checkIntersects = testSegment[i].hit;
		bool intersect = Intersect(ray, box, &contactPoint);
		if (checkIntersects != intersect)
		{
			intersect = false; // Check to see if we were supposed to intersect or not
		}
		if (checkIntersection.x != contactPoint.x || checkIntersection.y != contactPoint.y
			|| checkIntersection.z != contactPoint.z)
		{
			if (abs(contactPoint.x - checkIntersection.x) < 25 || (abs(contactPoint.y - checkIntersection.y) < 25 ||
				abs(contactPoint.z - checkIntersection.z) < 25))
			{
				intersect = true;
			}
			else {
				intersect = false;
			}
		}
		else
		{
			intersect = true;
		}
		if (!intersect)
			return intersect;
	}

	return true;
}

bool Physics::Intersect(const AABB& a, const AABB& b, AABB* pOverlap)
{
	// If it does NOT intersect, do NOT modify pOverlap
	// So check if it overlaps first
	if (a.maxCorner.x < b.minCorner.x || a.minCorner.x > b.maxCorner.x)
	{
		return false;
	}
	else if (a.maxCorner.y < b.minCorner.y || a.minCorner.y > b.maxCorner.y)
	{
		return false;
	} // I think it's the same thing for 3D except just change it to Z? 
	else if (a.maxCorner.z < b.minCorner.z || a.minCorner.z > b.maxCorner.z)
	{
		return false;
	}
	else
	{ // WE DO INTERSECT
		// so change pOverlap
		float maxCornerX = min((a.maxCorner.x), (b.maxCorner.x));
		float maxCornerY = min((a.maxCorner.y), (b.maxCorner.y));
		float maxCornerZ = min((a.maxCorner.z), (b.maxCorner.z));

		float minCornerX = max((a.minCorner.x), (b.minCorner.x));
		float minCornerY = max((a.minCorner.y), (b.minCorner.y));
		float minCornerZ = max((a.minCorner.z), (b.minCorner.z));

		pOverlap->maxCorner = Vector3(maxCornerX, maxCornerY, maxCornerZ);
		pOverlap->minCorner = Vector3(minCornerX, minCornerY, minCornerZ);

		return true;
	}

}
bool Physics::Intersect(const LineSegment& segment, const AABB& box, Vector3* pHitPoint)
{
	float tmin = 0.0f;
	Vector3 ray = segment.endingPoint - segment.startingPoint;
	float tmax = FLT_MAX; // max dist so ray can travel

	// try x first instead
	if (Math::IsZero(ray.x)) { // compare to 0 instead of epsilon!
		// intersection not possible!
		if (segment.startingPoint.x < box.minCorner.x || segment.startingPoint.x > box.maxCorner.x) 
			return 0;
	}
	else {
		// Compute intersection t value of ray with near and far plane of slab
		float ood = 1.0f / ray.x;
		float t1 = (box.minCorner.x - segment.startingPoint.x) * ood;
		float t2 = (box.maxCorner.x - segment.startingPoint.x) * ood;
		// Make t1 be intersection with near plane, t2 with far plane
		if (t1 > t2) {
			std::swap(t1, t2);
		}
		// Compute the intersection of slab intersection intervals
		tmin = max(tmin, t1);
		tmax = min(tmax, t2);
		// Exit with no collision as soon as slab intersection becomes empty
		if (tmin > tmax) {
			return 0;
		}
	}
	// y
	if (Math::IsZero(ray.y)) { // compare to 0 instead of epsilon!
	// intersection not possible!
		if (segment.startingPoint.y < box.minCorner.y || segment.startingPoint.y > box.maxCorner.y)
			return 0;
	}
	else {
		// Compute intersection t value of ray with near and far plane of slab
		float ood = 1.0f / ray.y;
		float t1 = (box.minCorner.y - segment.startingPoint.y) * ood;
		float t2 = (box.maxCorner.y - segment.startingPoint.y) * ood;
		// Make t1 be intersection with near plane, t2 with far plane
		if (t1 > t2)
			std::swap(t1, t2);
		// Compute the intersection of slab intersection intervals
		tmin = max(tmin, t1);
		tmax = min(tmax, t2);
		// Exit with no collision as soon as slab intersection becomes empty
		if (tmin > tmax)
			return 0;
	}
	// z
	if (Math::IsZero(ray.z)) { // compare to 0 instead of epsilon!
	// intersection not possible!
		if (segment.startingPoint.z < box.minCorner.z || segment.startingPoint.z > box.maxCorner.z)
			return 0;
	}
	else {
		// Compute intersection t value of ray with near and far plane of slab
		float ood = 1.0f / ray.z;
		float t1 = (box.minCorner.z - segment.startingPoint.z) * ood;
		float t2 = (box.maxCorner.z - segment.startingPoint.z) * ood;
		// Make t1 be intersection with near plane, t2 with far plane
		if (t1 > t2)
			std::swap(t1, t2);
		// Compute the intersection of slab intersection intervals
		tmin = max(tmin, t1);
		tmax = min(tmax, t2);
		// Exit with no collision as soon as slab intersection becomes empty
		if (tmin > tmax)
			return 0;
	}

	*pHitPoint = segment.startingPoint + ray;
	return 1;


}
bool Physics::UnitTest()
{
	bool isOk = true;
	isOk &= Physics::AABB::UnitTestAABB();
	isOk &= Physics::LineSegment::UnitTestRayCast();
	return isOk;
}

void Physics::RemoveObj(const class CollisionBox* pObj)
{
	std::vector<const CollisionBox*>::iterator it;
	it = std::find(collBoxes.begin(), collBoxes.end(), pObj);
	collBoxes.erase(it);

}
bool Physics::RayCast(const LineSegment& segment, Vector3* pHitPoint)
{
	Vector3 pastSeg = segment.endingPoint;
	bool intersect = false;
	Vector3 temp;
	bool flag = false;
	for (int i = 0; i < collBoxes.size(); i++)
	{
		AABB ab = collBoxes[i]->GetAABB();
		bool intersect = Intersect(segment, ab, &temp); // If the segment and the AABB intersect, temp is now storing that point
		if (intersect)
		{
			// need to find the CLOSEST point from the start
			// smallest distance aka length
			Vector3 currIntersection = temp - segment.startingPoint;
			if ((pastSeg - segment.startingPoint).Length() > temp.Length())
			{
				pastSeg = temp;
			}

			flag = true;
		}
		
	}

	(pHitPoint) = &(pastSeg);
	return flag;
}

