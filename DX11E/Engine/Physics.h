#pragma once
#include <engineMath.h>
class Physics
{
public:
	class AABB
	{
	public:
		AABB();
		AABB(Vector3 min, Vector3 max);
		static bool UnitTestAABB();
		Vector3 minCorner;
		Vector3 maxCorner;
	private:

	};

	class LineSegment
	{
	public:
		LineSegment();
		LineSegment(Vector3 st, Vector3 end);
		static bool UnitTestRayCast();
		Vector3 startingPoint;
		Vector3 endingPoint;
	private:

	};
	struct TestAABB
	{
		AABB a;
		AABB b;
		AABB overlap;
	};
	struct TestSegment
	{
		AABB box;
		LineSegment segment;
		bool hit;
		Vector3 point;
	};

	static bool Intersect(const AABB& a, const AABB& b, AABB* pOverlap = nullptr);
	static bool Intersect(const LineSegment& segment, const AABB& box, Vector3* pHitPoint = nullptr);
	static bool UnitTest();

	void AddObj(const class CollisionBox* pObj) { collBoxes.push_back(pObj); };
	void RemoveObj(const class CollisionBox* pObj);

	bool RayCast(const LineSegment& segment, Vector3* pHitPoint = nullptr);



private:
	std::vector<const class CollisionBox*> collBoxes;
};

