#include "stdafx.h"
#include "ToolsModel.h"

ToolsModel::ToolsModel(wstring animPath, wstring matFile, wstring meshFile)
	: GameAnimationModel(matFile, meshFile)
{

	
}

ToolsModel::~ToolsModel()
{
}

void ToolsModel::Update()
{
	

	GameAnimationModel::Update();
}

void ToolsModel::Render()
{
	GameAnimationModel::Render();
}

