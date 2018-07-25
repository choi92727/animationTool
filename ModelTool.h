#pragma once

class ModelTool : public Execute
{
public:
	ModelTool(ExecuteValues* values);
	~ModelTool();

	void Update();

	void PreRender() {}
	void Render();
	void PostRender();

	void ResizeScreen() {}


private:
	class GameSkyBox* skyBox;
	class GameWorld* world;
	class GameAnimationModel* grund;
	class GamePlayer* player;
};