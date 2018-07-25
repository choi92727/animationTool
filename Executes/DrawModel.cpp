#include "stdafx.h"
#include "DrawModel.h"
#include "../Objects/GameSkyBox.h"
#include "../Objects/GameWorld.h"
#include "../Objects/GameAnimationModel.h"
#include "../Units/GamePlayer.h"

DrawModel::DrawModel(ExecuteValues* values)
	: Execute(values)
	, skyBox(NULL), world(NULL), grund(NULL)
	, player(NULL)
{
	CreateEnvironment();
	//CreateAnimationModel();
	CreatePlayer();
}

DrawModel::~DrawModel()
{
	SAFE_DELETE(player);
	SAFE_DELETE(grund);
	SAFE_DELETE(world);
	SAFE_DELETE(skyBox);
}

void DrawModel::Update()
{
	if (skyBox != NULL) skyBox->Update();
	if (world != NULL) world->Update();
	if (grund != NULL) grund->Update();
	if (player != NULL) player->Update();
}

void DrawModel::Render()
{
	if (skyBox != NULL) skyBox->Render();
	if (world != NULL) world->Render();
	if (grund != NULL) grund->Render();
	if (player != NULL) player->Render();
}

void DrawModel::PostRender()
{
	if (values->GuiSettings->bShowModelWindow == true)
	{
		ImGui::Begin("Model Info", &values->GuiSettings->bShowModelWindow);
		int boneCount;
		boneCount = player->GetModel()->BoneCount();
		vector<string> boneNames;

		for (int i = 0; i < boneCount; i++)
		{
			boneNames.push_back(String::ToString(player->GetModel()->Bone(i)->Name()));
		}
		
		static const char* current_Clip = NULL;
		if (ImGui::BeginCombo("Anim Clip", current_Clip)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < boneNames.size(); n++)
			{
				bool is_selected = (current_Clip == boneNames[n].c_str()); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(boneNames[n].c_str(), is_selected))
					current_Clip = boneNames[n].c_str();
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
			}
			ImGui::EndCombo();
		}

		if (current_Clip != NULL)
		{

		}
		
		

		ImGui::End();
	}
}

void DrawModel::CreateEnvironment()
{
	wstring matFile = L"";
	wstring meshFile = L"";

	//World
	matFile = Models + L"Stage1/France.material";
	meshFile = Models + L"Stage1/France.mesh";
	world = new GameWorld(matFile, meshFile);

	//SkyBox
	matFile = Models + L"Stage1/France_Sky.material";
	meshFile = Models + L"Stage1/France_Sky.mesh";
	skyBox = new GameSkyBox(matFile, meshFile);
	skyBox->Position(D3DXVECTOR3(0, 20, 0));
}

void DrawModel::CreateAnimationModel()
{
	wstring matFile = L"";
	wstring meshFile = L"";

	//Grund
	matFile = Models + L"Grund/Grund.material";
	meshFile = Models + L"Grund/Grund.mesh";
	grund = new GameAnimationModel(matFile, meshFile);

	grund->AddClip(Models + L"Grund/Low_Idle.anim");
	grund->AddClip(Models + L"Grund/Up_Idle.anim");
	grund->AddClip(Models + L"Grund/Low_Run.anim");
	grund->AddClip(Models + L"Grund/Up_Run.anim");
	grund->AddClip(Models + L"Grund/Up_AttackFrontBase.anim");

	grund->Play(0, 0, 0, 1, AnimationPlayMode::Repeat);
	grund->Play(1, 0, 0, 1, AnimationPlayMode::Repeat);
}

void DrawModel::CreatePlayer()
{
	wstring matFile = L"";
	wstring meshFile = L"";

	//Grund
	matFile = Models + L"Grund/Grund.material";
	meshFile = Models + L"Grund/Grund.mesh";
	player = new GamePlayer(Models + L"Grund/", matFile, meshFile);
}
