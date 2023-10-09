#pragma once
#include "Component.h"
#include "RenderObj.h"
class SimpleRotate : public Component, public RenderObj
{
public:
	SimpleRotate(RenderObj* pObj, class Game* pGame);
	~SimpleRotate();

	void LoadProperties(const rapidjson::Value& properties) override;
	void Update(float deltaTime);

private:
	class RenderObj* parent;
	float speedRate = 0.0f;
	float mRotation = 0.0f;
};
