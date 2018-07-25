#pragma once

class ModelAnimPlayer
{
public:
	enum class Mode
	{
		Play = 0, Pause, Stop,
	};

	ModelAnimPlayer(class Model* model);
	~ModelAnimPlayer();

	void SetMode(Mode value) { mode = value; }
	Mode GetMode() { return mode; }

	void Update();
	void Render();

private:
	void UpdateTime();
	void UpdateBone();

private:
	Shader* shader;

	class Model* model;
	class ModelAnimClip* currentClip;


	Mode mode;
	bool bUseSlerp;

	int currentKeyframe;
	int nextKeyframe;

	float frameTime; //현재 프레임으로부터 경과시간
	float frameFactor; //현재 프레임과 다음 프레임 사이의 보간값
	
	vector<D3DXMATRIX> boneAnimation; //본이 애니메이션 계산된 행렬
	vector<D3DXMATRIX> renderTransform; //스키닝이 계산된 렌더용 행렬
};