#pragma once
#include "GameModel.h"
#include "AnimationClip.h"

class GameAnimationModel : public GameModel
{
public:
	GameAnimationModel(wstring meshFile, wstring matFile);
	virtual ~GameAnimationModel();

	UINT AddClip(wstring file);
	UINT AddClip(AnimationClip* clip);
	void RemoveClip(UINT index);
	void ClearClip();
	
	AnimationClip* GetClip(UINT index);

	bool Play(UINT index, AnimationPlayMode mode);
	bool Play(UINT index, float startTime, float blendTime, float speed, AnimationPlayMode mode);

	float GetPlayTime(wstring boneName);
	Model* GetModel() { return model; }

	virtual void Update();
	virtual void Render();

protected:
	struct AnimationBlender* GetBlenderFromBoneName(wstring name);

protected:
	vector<AnimationClip *> clips;
	vector<struct AnimationBlender *> blenders;
};