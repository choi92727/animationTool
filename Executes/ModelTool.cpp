#include "stdafx.h"
#include "ModelTool.h"
#include "../Objects/GameAnimationModel.h"
#include "../Objects/ToolsModel.h"
#include "../Model/ModelAnimPlayer.h"
#include "../Objects/Gizmo.h"
#include "../Objects/GizmoComponent.h"
#include "../Fbx/Exporter.h"


ModelTool::ModelTool(ExecuteValues * values)
	: Execute(values)
	, player(NULL)
	, currentSelectBone(-1)
{
	wstring matFile = L"";
	wstring meshFile = L"";

	ExportModel();

	//Grund
	matFile = Models + L"RPG/Character.material";
	meshFile = Models + L"RPG/Character.mesh";
	player = new ToolsModel(Models + L"RPG/", matFile, meshFile);
	player->AddClip(Models + L"RPG/Attack-Kick-L1.anim");
	component = new Gizmo::GizmoComponent(values);
}

ModelTool::~ModelTool()
{
	SAFE_DELETE(player);
}

void ModelTool::Update()
{
	if (player != NULL) player->Update();
	if (currentSelectBone != -1)component->Update();
}

void ModelTool::Render()
{
	if (player != NULL) player->Render();
	if (currentSelectBone != -1)component->Render();
}

void ModelTool::PostRender()
{
	if (values->GuiSettings->bShowModelWindow == true)
	{
		ImGui::Begin("Model Info", &values->GuiSettings->bShowModelWindow);
		if (ImGui::CollapsingHeader("ModelBone"))
		{
			
			ImGuiStyle& style = ImGui::GetStyle();
			style.IndentSpacing = 15.0f;
			
			CreateModelTrees(player->GetModel()->Bone(1));

			
		}
		if (ImGui::CollapsingHeader("SelectedBone"))
		{
			if (currentSelectBone != -1)
			{
				ModelBone* currentSelectedBone = player->GetModel()->Bone(currentSelectBone);
				//string current = String::ToString(currentSelectedBone->Name());
				ImGui::Text(String::ToString(currentSelectedBone->Name()).c_str());
				
			}
		}

		if (ImGui::CollapsingHeader("Animation"))
		{
			ControlAnimPlayer();
		}
		
		ImGui::End();
	}
}

void ModelTool::CreateModelTrees(ModelBone * bone)
{
	string name = String::ToString(bone->Name());
	UINT childCount = bone->ChildCount();
	int index = bone->Index();

	string sNumber = to_string(index) + ". ";
	string sNumName = sNumber + name;

	const char* cName = name.c_str();
	const char* cNumber = sNumber.c_str();
	const char* cNumberName = sNumName.c_str();


	if (childCount == 0)
	{
		ImGui::Indent();
		if (ImGui::Selectable(cNumberName))
			currentSelectBone = index;
		ImGui::Unindent();
	}
	else
	{
		if (ImGui::TreeNodeEx(cNumber, ImGuiTreeNodeFlags_OpenOnArrow))
		{
			ImGui::SameLine();
			if (ImGui::Selectable(cName))
			{
				
				currentSelectBone = index;
				targetMat = player->GetModel()->Bone(currentSelectBone)->AbsoluteTransform();
				D3DXVECTOR3 pos = { targetMat._41,targetMat._42,targetMat._43 };
				component->Position(pos);
				component->SetTarget(&player->GetModel()->Bone(index)->Transform());
			}

			for (size_t i = 0; i < childCount; i++)
			{
				ModelBone* child = bone->Child(i);
				CreateModelTrees(child);
			}
			ImGui::TreePop();
		}
	}
}

void ModelTool::ControlAnimPlayer()
{
}



D3DXMATRIX ModelTool::reculsiveBone_Transform(int index)
{
	D3DXMATRIX result;
	result = player->GetModel()->Bone(index)->Transform();
	if (player->GetModel()->Bone(index)->Parent() != NULL)
	{
		result = result* player->GetModel()->Bone(index)->Parent()->Transform() ;
	}
	return result;
}

void ModelTool::ExportModel()
{
	

	//Fbx::Exporter* exporter = new Fbx::Exporter(Assets + L"RPG_Character/RPG-Character.FBX");
	//exporter->ExportMaterial(Models + L"RPG/", L"Character");
	//exporter->ExportMeshData(Models + L"RPG/", L"Character");
	

	Fbx::Exporter* exporter = new Fbx::Exporter(Assets + L"RPG_Character/RPG-Character@Unarmed-Attack-Kick-L1.FBX");	
	exporter->ExportAnimation(Models + L"RPG/", L"Attack-Kick-L1");
	SAFE_DELETE(exporter);
	exporter = new Fbx::Exporter(Assets + L"RPG_Character/RPG-Character@Unarmed-Attack-Kick-R1.FBX");
	exporter->ExportAnimation(Models + L"RPG/", L"Attack-Kick-R1");
	SAFE_DELETE(exporter);
}

