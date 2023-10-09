#pragma once
#include "component.h"
#include "engineMath.h"

class Game;

class FollowCam : public Component
{
public:
    FollowCam(RenderObj* pObj, Game* pGame);

    void LoadProperties(const rapidjson::Value& properties, class AssetManager* pAssetManager);

    void Update(float deltaTime) override;

private:
    Vector3 position = Vector3(-200.0, 0.0, 100.0);
    Vector3 mOffset = Vector3(-200, 0, 100);
    Game* mGame;
    Matrix4 mat;

    float horizonDist = 60.0f;
    float targetOff = 50.0f;
    float const zComp = 70.0f;
    float mPitchAngle = 0.0f;
    float mPitchSpeed = 0.0f;
    float mRotation = 0.0f;
};