#include "stdafx.h"
#include "Animation.h"
#include "BoneTransform.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include "jsonUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <Skeleton.h>

Animation::Animation()
{
	mAnimationLength = 0.0f;
	mBones = 0;
	mFrames = 0;
}
uint32_t Animation::GetNumBones() const
{
	return mBones;
}
uint32_t Animation::GetNumFrames() const
{
	return mFrames;
}
float Animation::GetLength() const
{
	return mAnimationLength;
}
void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses,
	const Skeleton* inSkeleton, float inTime) const
{

	float currFrameRate = (GetLength() / (GetNumFrames() - 1));
	int currTime = std::floor((inTime) / currFrameRate);
	int roundedUp = (std::ceil((inTime) / currFrameRate));
	float ratio = currTime / roundedUp;
	while (currTime >= GetNumFrames() && roundedUp >= GetNumFrames())
	{
		currTime -= GetNumFrames();
		roundedUp -= GetNumFrames();
		if (currTime < 0)
		{
			currTime = 0;
			roundedUp = 0;
		}
	}
	outPoses.resize(inSkeleton->GetNumBones());
	for (int i = 0; i < GetNumBones(); i++)
	{
		Matrix4 bMatrix;
		if (this->mAnimData[i].size() != 0)
		{
			BoneTransform interpolated = BoneTransform::Interpolate(mAnimData[i][currTime], mAnimData[i][roundedUp], ratio);
			bMatrix = interpolated.toMatrix();
			if (inSkeleton->GetBone(i).mParentIndex != -1) // If the current bone has a parent
			{ // combine the current matrix with the parent
					bMatrix *= outPoses[inSkeleton->GetBone(i).mParentIndex];
			}
		}
		else
		{ // Empty keyframe
			Matrix4 bMatrix = Matrix4::Identity;
		}

		outPoses[i] = bMatrix;
	}
}



Animation* Animation::StaticLoad(const WCHAR* fileName, class AssetManager* pAssetManager)
{
	Animation* a = new Animation();

	if (false == a->Load(fileName))
	{
		return a;
	}
	return a; // Return a new animation if the load fails
}
bool Animation::Load(const WCHAR* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		DbgAssert(false, "Unable to open Animation file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itpanim" ||
		ver != 2)
	{
		DbgAssert(false, "Animation File Incorrect Version");
		return false;
	}

	const rapidjson::Value& sequence = doc["sequence"]; // object containing everything

	// Get the animation frames count
	int frames;
	GetIntFromJSON(sequence, "frames", frames);
	mFrames = uint32_t(frames);

	// Get the animation length
	float len;
	GetFloatFromJSON(sequence, "length", len);
	mAnimationLength = len;

	// Get the bone count
	int bones;
	GetIntFromJSON(sequence, "bonecount", bones);
	mBones = uint32_t(bones);

	// so not all bones have a track to them. so how to handle bone indexes that have none?
	// since we have a vector of vector<boneTransforms>, will push_back an empty boneTransform
	// so at least, all indexes of bones will be in order, you know a bone has no track if its vector<boneTransform>
	// is empty.

	// initialize to all empty vectors, but now every index has a vector<BoneTransform>
	for (int i = 0; i < mBones; i++)
	{
		std::vector<BoneTransform> bt;
		mAnimData.push_back(bt);
	}

	const rapidjson::Value& tracks = sequence["tracks"];
	if (!tracks.IsArray())
	{
		DbgAssert(false, "Animation File Invalid Tracks Array Format");
		return false;
	}

	for (int i = 0; i < tracks.Size(); i++) // Loop thru all the bone indexes
	{
		int boneIndex;
		GetIntFromJSON(tracks[i], "bone", boneIndex); // know which bone to edit in the bone vector
		// chance that we skip indicies so we must do this step
		
		const rapidjson::Value& transforms = tracks[i]["transforms"];
		if (!transforms.IsArray())
		{
			DbgAssert(false, "Animation File Invalid Transforms Array Format");
			return false;
		}

		for (int j = 0; j < transforms.Size(); j++)
		{
			Vector3 translation;
			Quaternion rotation;
			GetVectorFromJSON(transforms[j], "trans", translation);
			GetQuaternionFromJSON(transforms[j], "rot", rotation);

			BoneTransform bt;
			bt.mRotation = rotation;
			bt.mTranslate = translation;

			mAnimData[boneIndex].push_back(bt); // for this bone Index, push_back this BoneTransform
		}
	}

	return true;


}