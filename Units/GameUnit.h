#pragma once
#include "../Objects/GameAnimationModel.h"

class GameUnit : public GameAnimationModel
{
public:
	GameUnit(wstring matFile, wstring meshFile);
	virtual ~GameUnit();

	virtual void Update();
	virtual void Render();
};