#pragma once
#include "BoneTransform.h"
class Skeleton
{
public:
	Skeleton();
	struct Bone
	{
		BoneTransform mLocalBindPose;
		std::string mName;
		int mParentIndex;

	};

	size_t GetNumBones() const;
	const Bone& GetBone(size_t idx) const;
	const std::vector<Bone>& GetBones() const;
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const;
	static Skeleton* StaticLoad(const WCHAR* fileName, class AssetManager* pAssetManager);
	bool Load(const WCHAR* fileName);
	
private:
	std::vector<Bone> mBones;
	std::vector<Matrix4> mGlobalInvBindPoseMat; 
	void ComputeGlobalInvBindPose();
};

