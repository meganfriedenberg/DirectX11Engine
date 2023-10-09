#include "stdafx.h"
#include "Skeleton.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include "jsonUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

Skeleton::Skeleton()
{

}

void Skeleton::ComputeGlobalInvBindPose()
{
	for (int i = 0; i < GetNumBones(); i++)
	{
		Bone currBone = GetBone(i);
		if (currBone.mParentIndex >= 0) // it has a valid parent index
		{
			// need to do child * parent
			Matrix4 child = currBone.mLocalBindPose.toMatrix();
			Matrix4 parent = mGlobalInvBindPoseMat[currBone.mParentIndex];
			mGlobalInvBindPoseMat[i] = child * parent;
		}
		else
		{
			mGlobalInvBindPoseMat[i] = currBone.mLocalBindPose.toMatrix();
		}
	}

	for (int i = 0; i < GetNumBones(); i++)
	{
		mGlobalInvBindPoseMat[i].Invert();
	}

}
size_t Skeleton::GetNumBones() const
{
	return mBones.size();
}
const Skeleton::Bone& Skeleton::GetBone(size_t idx) const
{
	return mBones[idx];
}
const std::vector<Skeleton::Bone>& Skeleton::GetBones() const
{
	return mBones;
}
const std::vector<Matrix4>& Skeleton::GetGlobalInvBindPoses() const
{
	return mGlobalInvBindPoseMat;
}
Skeleton* Skeleton::StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager)
{
	Skeleton* s = new Skeleton();

	if (false == s->Load(fileName))
	{
		return s;
	}
	return s; // Return a new skele if the load fails
}
bool Skeleton::Load(const WCHAR* fileName)
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
		DbgAssert(false, "Unable to open Skele file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itpskel" ||
		ver != 1)
	{
		DbgAssert(false, "Skeleton File Incorrect Version");
		return false;
	}

	// Get the bone count
	int totalBones;
	GetIntFromJSON(doc, "bonecount", totalBones);

	const rapidjson::Value& bones = doc["bones"];
	if (!bones.IsArray() || bones.Size() != totalBones)
	{
		DbgAssert(false, "Skeleton File Invalid Bones Array Format");
		return false;
	}

	for (int i = 0; i < totalBones; i++) // Loop thru all the bones in the file
	{
		std::string name = "";
		GetStringFromJSON(bones[i], "name", name);
		int index;
		GetIntFromJSON(bones[i], "parent", index);

		const rapidjson::Value& bindPose = bones[i]["bindpose"];
		Vector3 translation;
		Quaternion rotation;
		GetVectorFromJSON(bindPose, "trans", translation);
		GetQuaternionFromJSON(bindPose, "rot", rotation);

		Bone currBone;
		currBone.mName = name;
		currBone.mParentIndex = index;
		currBone.mLocalBindPose.mRotation = rotation;
		currBone.mLocalBindPose.mTranslate = translation;
		mBones.push_back(currBone);
		mGlobalInvBindPoseMat.push_back(Matrix4::Identity * ((Matrix4::CreateTranslation(Vector3::Zero))));

	}

	ComputeGlobalInvBindPose();

	return true;
}