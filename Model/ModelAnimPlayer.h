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

	float frameTime; //���� ���������κ��� ����ð�
	float frameFactor; //���� �����Ӱ� ���� ������ ������ ������
	
	vector<D3DXMATRIX> boneAnimation; //���� �ִϸ��̼� ���� ���
	vector<D3DXMATRIX> renderTransform; //��Ű���� ���� ������ ���
};