#include "stdafx.h"
#include "Component.h"

Component::Component()
{

}
Component::Component(class RenderObj* pObj)
{
	mObj = pObj;
}
Component::~Component()
{

}
void Component::LoadProperties(const rapidjson::Value& properties)
{

}
void Component::Update(float deltaTime)
{

}