#pragma once

class DrawModel : public Execute
{
public:
	DrawModel(ExecuteValues* values);
	~DrawModel();

	void Update();

	void PreRender() {}
	void Render();
	void PostRender();

	void ResizeScreen() {}

private:
	void CreateEnvironment();
	void CreateAnimationModel();
	void CreatePlayer();

private:
	class GameSkyBox* skyBox;
	class GameWorld* world;
	class GameAnimationModel* grund;
	class GamePlayer* player;
};