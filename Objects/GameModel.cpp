#include "stdafx.h"
#include "GameModel.h"

GameModel::GameModel(wstring matFile, wstring meshFile)
	: velocity(0, 0, 0)
{
	model = new Model();
	model->ReadMaterial(matFile);
	model->ReadMesh(meshFile);

	shader = new Shader(Shaders + L"999_GameModel.hlsl", "VS_Bone");
	for (Material* material : model->Materials())
		material->SetShader(shader);

	boneBuffer = new BoneBuffer();
	renderBuffer = new RenderBuffer();
}

GameModel::~GameModel()
{
	SAFE_DELETE(renderBuffer);
	SAFE_DELETE(boneBuffer);

	SAFE_DELETE(shader);
	SAFE_DELETE(model);
}

void GameModel::Velocity(D3DXVECTOR3 & vec)
{
	velocity = vec;
}

D3DXVECTOR3 GameModel::Velocity()
{
	return velocity;
}

void GameModel::AddPosition(D3DXVECTOR3 & vec)
{
	D3DXVECTOR3 temp = Position() + vec;

	Position(temp);
}

void GameModel::CalcPosition()
{
	if (D3DXVec3Length(&velocity) <= 0.0f)
		return;

	
	D3DXVECTOR3 vec(0, 0, 0);

	if (velocity.z != 0.0f)
		vec += Direction() * velocity.z;

	if (velocity.y != 0.0f)
		vec += Up() * velocity.y;

	if (velocity.x != 0.0f)
		vec += Right() * velocity.x;

	AddPosition(vec * Time::Delta());
}

void GameModel::Update()
{
	CalcPosition();

	D3DXMATRIX transformed = Transformed();
	model->CopyAbsoluteBoneTo(transformed, boneTransforms);
}

void GameModel::Render()
{
	if (Visible() == false) return;

	if(boneTransforms.size() !=0)
	boneBuffer->SetBones(&boneTransforms[0], boneTransforms.size());
	boneBuffer->SetVSBuffer(2);

	for (ModelMesh* mesh : model->Meshes())
	{
		int index = mesh->ParentBoneIndex();

		renderBuffer->Data.BoneNumber = index;
		renderBuffer->SetVSBuffer(3);

		mesh->Render();
	}
}
