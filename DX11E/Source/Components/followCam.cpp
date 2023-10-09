#include "stdafx.h"
#include "camera.h"
#include "components\followCam.h"
#include "game.h"
#include "jsonUtil.h"
#include "renderObj.h"
#include "stringUtil.h"
#include "assetManager.h"


FollowCam::FollowCam(RenderObj* pObj, Game* pGame)
    : Component(pObj)
    , mGame(pGame)
{
	mat = mObj->structPerObj.floatMatrix;
	mat = Matrix4::CreateRotationX(Math::PiOver2) * mat;	//mrwTODO this 90 rotation accounts for the orientation of the model :(
}

void FollowCam::LoadProperties(const rapidjson::Value& properties, AssetManager* pAssetManager)
{
    //Component::LoadProperties(properties);
    GetVectorFromJSON(properties, "offset", this->mOffset);
}

void FollowCam::Update(float deltaTime)
{
    Camera* pCamera = mGame->GetCamera();

    //mOffset = Vector3(-200, 0, 100);
    //Matrix4 mat = Matrix4::CreateTranslation(mObj->structPerObj.floatMatrix.GetTranslation() + mOffset);
    Matrix4 mat = Matrix4::CreateTranslation(mOffset) * Matrix4::CreateRotationY(this->mPitchAngle) * Matrix4::CreateRotationZ(this->mRotation);
    mat.Invert();
    pCamera->SetWorldToCam(mat);

    //this->mPitchAngle += this->mPitchSpeed * deltaTime;

    //if (mPitchAngle > Math::PiOver2 / 2.0f) { //max for looking up
    //    mPitchAngle = Math::PiOver2 / 2.0f;
    //}
    //if (mPitchAngle < -Math::PiOver2 / 2.0f) { //min for looking down
    //    mPitchAngle = -Math::PiOver2 / 2.0f;
    //}

    //Matrix4 pitchRotate = Matrix4::CreateRotationY(this->mPitchAngle);
    //Matrix4 yawRotate = Matrix4::CreateRotationZ(mRotation); //yaw corresponds to z, gabriel the cp helped explain this to me
    //Matrix4 combinedRotate = pitchRotate * yawRotate;

    ////then transform the vector3 <1,0,0> to get the camera's forward vec
    //Vector3 xVec = Vector3(1.0f, 0, 0);
    //Vector3 newForward = Vector3::Transform(xVec, combinedRotate);

    //Vector3 targetPos = position + newForward;
    //Matrix4 lookAt = Matrix4::CreateLookAt(position, targetPos, Vector3::UnitZ);
    bool leadingEdge = true;
    if (mGame->IsKeyHeld(VK_UP) && leadingEdge)
    {
        mOffset.x = mOffset.x + 5;
        leadingEdge = false;
    }

    if (mGame->IsKeyHeld(VK_DOWN) && leadingEdge)
    {
        mOffset.x = mOffset.x - 5;
    }
    if (mGame->IsKeyHeld(VK_RIGHT) && leadingEdge)
    {
        mOffset.y = mOffset.y + 5;
    }
    if (mGame->IsKeyHeld(VK_LEFT) && leadingEdge)
    {
        mOffset.y = mOffset.y - 5;
    }
    if (mGame->IsKeyHeld('T'))
    {
        mPitchAngle += .05;
        if (mPitchAngle > Math::PiOver2 / 2.0f + .7)
        {
            mPitchAngle = Math::PiOver2 / 2.0f + .7;
        }
    }
    if (mGame->IsKeyHeld('G'))
    {
        mPitchAngle -= .05;
        if (mPitchAngle < -Math::PiOver2 / 2.0f - 1.1)
        {
            mPitchAngle = -Math::PiOver2 / 2.0f - 1.1;
        }
    }
    if (mGame->IsKeyHeld('F'))
    {
        mRotation -= 0.01;
    }
    if (mGame->IsKeyHeld('H'))
    {
        mRotation += 0.008;
    }
    Matrix4 yawRotate = Matrix4::CreateRotationZ(mRotation);
    Vector3 xVec = Vector3(1.0f, 0, 0);
    Vector3 newForward = Vector3::Transform(xVec, yawRotate);
    //mat.Invert();
    //pCamera->SetWorldToCam(lookAt);

}