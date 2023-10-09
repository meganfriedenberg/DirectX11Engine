#pragma once
#include "Component.h"
#include "Job.h"
class Character : public Component
{
public:
	Character(class SkinnedObj* pObj, class Game* pGame);
	void LoadProperties(const rapidjson::Value& properties) override;
	bool SetAnim(const std::string& animName);
	void UpdateAnim(float deltaTime);
	void Update(float deltaTime) override;
	float GetAnimTime() { return mCurrAnimTime; }
	RenderObj* GetObj() { return mObj; }

	class AnimationJob : Job // Character has access now but still inherited from job to override the virtual
	{ 
	public:
		AnimationJob();
		AnimationJob(Character* c);
		~AnimationJob();
		void DoIt() override;

		Character* parentCharacter;
		float currTime = 0.0f;
	private:
	};


private:
	class SkinnedObj* mSkinnedObj;
	class Skeleton* mSkele;
	std::unordered_map<std::string, const class Animation*> mAnimations;
	float mCurrAnimTime = 0.0f;
	const Animation* mCurrAnimation;
	class Game* mGame;
};

