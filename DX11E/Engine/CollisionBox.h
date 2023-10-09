#pragma once
#include "Component.h"
#include "Physics.h"
class CollisionBox : public Component
{
public:
	CollisionBox();
	CollisionBox(RenderObj* pObj, Physics* p);
	~CollisionBox();
	void LoadProperties(const rapidjson::Value& properties) override;
	const Physics::AABB GetAABB() const;

private:
	Physics::AABB cb;
	class Physics* phy;
};

