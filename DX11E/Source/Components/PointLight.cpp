#include "stdafx.h"
#include "PointLight.h"
#include "Game.h"
#include "RenderObj.h"
#include <jsonUtil.cpp>

PointLight::PointLight(RenderObj* pObj, class Game* pGame) : Component(pObj)
{
	mGame = pGame;
	mLightData = mGame->AllocateLight();
}
PointLight::~PointLight()
{
	delete mLightData;
}
void PointLight::LoadProperties(const rapidjson::Value& properties)
{
	Vector3 lightC;
	GetVectorFromJSON(properties, "lightColor", lightC);

	float innerRad = 0;
	GetFloatFromJSON(properties, "innerRadius", innerRad);

	float outerRad = 0;
	GetFloatFromJSON(properties, "outerRadius", outerRad);

	mLightData->lightColor = lightC;
	mLightData->innerRadius = innerRad;
	mLightData->outerRadius = outerRad;
}
void PointLight::Update(float deltaTime)
{
	mLightData->position = mObj->structPerObj.floatMatrix.GetTranslation();
}