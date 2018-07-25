#pragma once
#include "GameModel.h"

class GameSkyBox : public GameModel
{
public:
	GameSkyBox(wstring matFile, wstring meshFile);
	~GameSkyBox();
};