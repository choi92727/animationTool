#include "stdafx.h"
#include "ModelAnimPlayer.h"
#include "Model.h"
#include "ModelMesh.h"
#include "ModelBone.h"
#include "ModelAnimClip.h"

ModelAnimPlayer::ModelAnimPlayer(Model * model)
	: model(model), mode(Mode::Play)
	, currentKeyframe(0), nextKeyframe(0)
	, frameTime(0), frameFactor(0)
	, bUseSlerp(true)
{
	shader = new Shader(Shaders + L"999_Animation.hlsl");

	vector<Material *>& materials = model->Materials();
	for (Material* material : materials)
		material->SetShader(shader);

	currentClip = model->Clip(0);

	boneAnimation.assign(model->BoneCount(), D3DXMATRIX());
	renderTransform.assign(model->BoneCount(), D3DXMATRIX());
}

ModelAnimPlayer::~ModelAnimPlayer()
{
	SAFE_DELETE(shader);
}

void ModelAnimPlayer::Update()
{
	if (currentClip == NULL || mode != Mode::Play)
		return;

	UpdateTime();
	UpdateBone();

	model->Buffer()->SetBones(&renderTransform[0], renderTransform.size());
}

void ModelAnimPlayer::UpdateTime()
{
	frameTime += Time::Delta();

	float invFrameRate = 1.0f / currentClip->FrameRate();
	while (frameTime > invFrameRate)
	{
		int keyframeCount = currentClip->TotalFrame();

		currentKeyframe = (currentKeyframe + 1) % keyframeCount;
		nextKeyframe = (currentKeyframe + 1) % keyframeCount;

		frameTime -= invFrameRate;
	}

	frameFactor = frameTime / invFrameRate;
}

void ModelAnimPlayer::UpdateBone()
{
	for (size_t i = 0; i < model->BoneCount(); i++)
	{
		ModelBone* bone = model->Bone(i);

		D3DXMATRIX matAnimation;
		D3DXMATRIX matParentAnimation;

		D3DXMATRIX matInvBindPose = bone->AbsoluteTransform();
		D3DXMatrixInverse(&matInvBindPose, NULL, &matInvBindPose);

		ModelKeyframe* frame = currentClip->Keyframe(bone->Name());
		if (frame == NULL) continue;

		if (bUseSlerp == true)
		{
			D3DXMATRIX S, R, T;

			ModelKeyframeData current = frame->Datas[currentKeyframe];
			ModelKeyframeData next = frame->Datas[nextKeyframe];


			D3DXVECTOR3 s1 = current.Scale;
			D3DXVECTOR3 s2 = next.Scale;

			D3DXVECTOR3 s;
			D3DXVec3Lerp(&s, &s1, &s2, frameFactor);
			D3DXMatrixScaling(&S, s.x, s.y, s.z);


			D3DXQUATERNION q1 = current.Rotation;
			D3DXQUATERNION q2 = next.Rotation;

			D3DXQUATERNION q;
			D3DXQuaternionSlerp(&q, &q1, &q2, frameFactor);
			D3DXMatrixRotationQuaternion(&R, &q);


			D3DXVECTOR3 t1 = current.Translation;
			D3DXVECTOR3 t2 = next.Translation;

			D3DXVECTOR3 t;
			D3DXVec3Lerp(&t, &t1, &t2, frameFactor);
			D3DXMatrixTranslation(&T, t.x, t.y, t.z);

			matAnimation = S * R * T;
		}
		else
		{
			matAnimation = frame->Datas[currentKeyframe].Transform;
		}

		int parentIndex = bone->ParentIndex();
		if (parentIndex < 0)
			D3DXMatrixIdentity(&matParentAnimation);
		else
			matParentAnimation = boneAnimation[parentIndex];

		boneAnimation[i] = matAnimation * matParentAnimation;
		renderTransform[i] = matInvBindPose * boneAnimation[i];
	}
}

void ModelAnimPlayer::Render()
{
	model->Buffer()->SetVSBuffer(2);

	for (ModelMesh* mesh : model->Meshes())
		mesh->Render();
}