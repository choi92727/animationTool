#pragma once
#include "../Interfaces/ICloneable.h"

class ModelMesh : public ICloneable
{
public:
	friend class Model;
	friend class Models;

public:
	void Clone(void** clone);

	void SetWorld(D3DXMATRIX& world)
	{
		worldBuffer->SetMatrix(world);
	}

	void Render();

	wstring Name() { return name; }

	int ParentBoneIndex() { return parentBoneIndex; }
	class ModelBone* ParentBone() { return parentBone; }

private:
	void Binding();

private:
	ModelMesh();
	~ModelMesh();

	wstring name;

	int parentBoneIndex;
	class ModelBone* parentBone;

	WorldBuffer* worldBuffer;
	vector<class ModelMeshPart *> meshParts;
};