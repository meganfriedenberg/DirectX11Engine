#include "stdafx.h"
#include "CollisionBox.h"
#include "jsonUtil.h"
#include "Physics.h"
#include "RenderObj.h"

CollisionBox::CollisionBox()
{

}

CollisionBox::CollisionBox(RenderObj* pObj, Physics* p) : Component(pObj)
{
	phy = p;
	phy->AddObj(this);

}
CollisionBox::~CollisionBox()
{
	phy->RemoveObj(this);
}


void CollisionBox::LoadProperties(const rapidjson::Value& properties)
{

	Vector3 maxC;
	GetVectorFromJSON(properties, "max", maxC);

	Vector3 minC;
	GetVectorFromJSON(properties, "min", minC);

	cb.maxCorner = maxC;
	cb.minCorner = minC;

}

const Physics::AABB CollisionBox::GetAABB() const
{
	Physics::AABB copy = this->cb;
	//Apply the scale
	Vector3 sc = this->mObj->structPerObj.floatMatrix.GetScale();
	copy.maxCorner = copy.maxCorner * sc;
	copy.minCorner = copy.minCorner * sc;

	//Translate!
	Vector3 tr = this->mObj->structPerObj.floatMatrix.GetTranslation();
	copy.maxCorner = copy.maxCorner + tr;
	copy.minCorner = copy.minCorner + tr;

	return copy;

}