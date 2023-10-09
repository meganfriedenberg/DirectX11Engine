#include "stdafx.h"
#include "Character.h"
#include "Game.h"
#include "assetManager.h"
#include "RenderObj.h"
#include "Skeleton.h"
#include "SkinnedObj.h"
#include <jsonUtil.h>
#include "stringUtil.h"
#include "JobManager.h"

Character::Character(SkinnedObj* pObj, Game* pGame) : Component(pObj)
{
	mGame = pGame;
	mSkele = new Skeleton();
	mSkinnedObj = pObj;
}

void Character::LoadProperties(const rapidjson::Value& properties)
{
	std::wstring skeleFile;
	GetWStringFromJSON(properties, "skeleton", skeleFile);
	mSkele->Load((skeleFile.c_str())); // check to see if it initialized or not

	const rapidjson::Value& animationArray = properties["animations"];
	if (!animationArray.IsArray())
	{
		DbgAssert(false, "Level File Invalid Animations Array Format");
	}
	for (int i = 0; i < (int)animationArray.Size(); i++)
	{
		const rapidjson::Value& currPair = animationArray[i];
		Animation* a = new Animation();
		std::string animFile = currPair[1].GetString();
		std::wstring fileName;
		StringUtil::String2WString(fileName, animFile);
		a->Load(fileName.c_str());
		std::string shortName = currPair[0].GetString();
		mAnimations[shortName] = a;
	}
}
Character::AnimationJob::AnimationJob(Character* c)
{
	parentCharacter = c;
}

bool Character::SetAnim(const std::string& animName)
{
	std::unordered_map<std::string, const class Animation*>::const_iterator it;
	it = mAnimations.find(animName);
	if (it == mAnimations.end())
	{
		return false; // Animation didn't exist
	}
	else
	{
		this->mCurrAnimTime = 0.0f; // Reset timer
		this->mCurrAnimation = it->second; // Set to be the current animation
	}

	return true;
}

void Character::UpdateAnim(float deltaTime)
{
	this->mCurrAnimTime += deltaTime;
	while (mCurrAnimTime > this->mCurrAnimation->GetLength())
	{
		this->mCurrAnimTime = mCurrAnimTime - this->mCurrAnimation->GetLength(); // Wrap the animation if it goes over
		if (this->mCurrAnimTime < 0)
		{
			this->mCurrAnimTime = 0.0f;
		}
	}

	auto aJob = new AnimationJob(this);
	aJob->currTime = this->mCurrAnimTime;
	mGame->GetJM()->AddJob((Job*)aJob);

}
void Character::Update(float deltaTime)
{
	if (mCurrAnimation == nullptr)
	{
		SetAnim("run");
	}
	UpdateAnim(deltaTime);
}

Character::AnimationJob::AnimationJob()
{
	parentCharacter = nullptr;
}

Character::AnimationJob::~AnimationJob()
{
	
}
void Character::AnimationJob::DoIt()
{
	std::vector<Matrix4> outP;
	parentCharacter->mCurrAnimation->GetGlobalPoseAtTime(outP, parentCharacter->mSkele, currTime); // There is one for every bone
	std::vector<Matrix4> invBindP = parentCharacter->mSkele->GetGlobalInvBindPoses(); // There is one for every bone, zero if it wasn't file specified

	for (int i = 0; i < outP.size(); i++)
	{
		parentCharacter->mSkinnedObj->skc.c_skinMatrix[i] = invBindP[i] * outP[i]; // combine the matrices
	}
}
