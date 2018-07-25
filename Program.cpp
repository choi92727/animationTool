#include "stdafx.h"
#include "Program.h"

#include "./Viewer/FirstPerson.h"

#include "./Executes/ExportMesh.h"
#include "./Executes/ExportAnim.h"
#include "./Executes/DrawModel.h"
#include "./Executes/ExeGui.h"
#include "./Executes/ModelTool.h"

Program::Program()
{
	States::Create();
	Textures::Create();


	D3DDesc desc;
	D3D::GetDesc(&desc);

	values = new ExecuteValues();
	values->ViewProjection = new ViewProjectionBuffer();
	values->Perspective = new Perspective(desc.Width, desc.Height);
	values->Viewport = new Viewport(desc.Width, desc.Height);
	values->GuiSettings = new GuiSettings();
	values->GlobalLight = new LightBuffer();

	values->MainCamera = new FirstPerson(100);
	values->MainCamera->SetPosition(0, 0, -5);
	values->MainCamera->SetRotationDegree(0, 0);

	values->JsonRoot = new Json::Value();
	Json::ReadData(L"LevelEditor.json", values->JsonRoot);


	executes.push_back(new ExportMesh(values));
	executes.push_back(new ExportAnim(values));
	//executes.push_back(new DrawModel(values));
	executes.push_back(new ModelTool(values));
	executes.push_back(new ExeGui(values));
}

Program::~Program()
{
	for (Execute* exe : executes)
		SAFE_DELETE(exe);

	Json::WriteData(L"LevelEditor.json", values->JsonRoot);
	SAFE_DELETE(values->JsonRoot);
	
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values->GlobalLight);
	SAFE_DELETE(values->ViewProjection);
	SAFE_DELETE(values->Perspective);
	SAFE_DELETE(values->Viewport);
	SAFE_DELETE(values->GuiSettings);
	SAFE_DELETE(values);


	Textures::Delete();
	States::Delete();
}

void Program::Update()
{
	values->MainCamera->Update();

	for (Execute* exe : executes)
		exe->Update();
}

void Program::PreRender()
{
	
}

void Program::Render()
{
	D3D::Get()->SetRenderTarget();

	SetGlobalBuffers();

	for (Execute* exe : executes)
		exe->Render();
}

void Program::PostRender()
{
	for (Execute* exe : executes)
		exe->PostRender();
}

void Program::ResizeScreen()
{
	D3DDesc desc;
	D3D::GetDesc(&desc);

	values->Perspective->Set(desc.Width, desc.Height);
	values->Viewport->Set(desc.Width, desc.Height);

	for (Execute* exe : executes)
		exe->ResizeScreen();
}

void Program::SetGlobalBuffers()
{
	D3DXMATRIX view, projection;
	values->MainCamera->GetMatrix(&view);
	values->Perspective->GetMatrix(&projection);

	values->ViewProjection->SetView(view);
	values->ViewProjection->SetProjection(projection);
	values->ViewProjection->SetVSBuffer(0);

	values->GlobalLight->SetPSBuffer(0);
}
