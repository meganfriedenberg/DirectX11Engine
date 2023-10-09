#pragma once
#include "Component.h"
#include "Lights.h"
class PointLight : public Component
{
public:
	PointLight(class RenderObj* pObj, class Game* pGame);
	void LoadProperties(const rapidjson::Value& properties) override;
	void Update(float deltaTime) override;
	~PointLight();

	Lights::PointLightData* mLightData;
	class Game* mGame;
};

