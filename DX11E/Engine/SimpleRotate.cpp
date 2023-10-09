#include "stdafx.h"
#include "SimpleRotate.h"
#include <jsonUtil.h>
#include "stringUtil.h"

SimpleRotate::SimpleRotate(RenderObj* pObj, class Game* pGame)
{
	parent = pObj;
}
SimpleRotate::~SimpleRotate()
{

}

void SimpleRotate::LoadProperties(const rapidjson::Value& properties)
{
	float speed;
	GetFloatFromJSON(properties, "speed", speed);

	speedRate = speed;

}
void SimpleRotate::Update(float deltaTime)
{
	mRotation = (speedRate * deltaTime);
	Matrix4 rotate = Matrix4::CreateRotationZ(mRotation);
	parent->structPerObj.floatMatrix = rotate * parent->structPerObj.floatMatrix;
}