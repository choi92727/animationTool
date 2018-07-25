#pragma once
#include "../Objects/GameAnimationModel.h"
class ToolsModel: public GameAnimationModel
{
public:
	enum class LowerAction;
	enum class UpperAction;

public:
	ToolsModel(wstring animPath, wstring matFile, wstring meshFile);
	~ToolsModel();

	void Update();
	void Render();

private:
	

	

	
};