#pragma once
#include "BoneTransform.h"

class Animation
{
public:
	Animation();
	uint32_t GetNumBones() const;
	uint32_t GetNumFrames() const;
	float GetLength() const;
	static Animation* StaticLoad(const WCHAR* fileName, class AssetManager* pAssetManager);
	bool Load(const WCHAR* fileName);
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;


private:
	uint32_t mBones;
	uint32_t mFrames;
	float mAnimationLength = 0.0f;
	std::vector<std::vector<BoneTransform>> mAnimData;
};

