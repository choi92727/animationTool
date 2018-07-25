#include "stdafx.h"
#include "ExportMesh.h"
#include "./Fbx/Exporter.h"

ExportMesh::ExportMesh(ExecuteValues* values)
	: Execute(values)
{
	Fbx::Exporter* exporter = NULL;

	//Grund
	exporter = new Fbx::Exporter(Assets + L"Grund/Grund.fbx", true);
	exporter->ExportMaterial(Models + L"Grund/", L"Grund");
	exporter->ExportMeshData(Models + L"Grund/", L"Grund");
	SAFE_DELETE(exporter);

	//France
	/*exporter = new Fbx::Exporter(Assets + L"Map/Stage1/France.fbx");
	exporter->ExportMaterial(Models + L"Stage1/", L"France");
	exporter->ExportMeshData(Models + L"Stage1/", L"France");
	SAFE_DELETE(exporter);*/

	//France_Sky
	/*exporter = new Fbx::Exporter(Assets + L"Map/Stage1/France_Sky.fbx");
	exporter->ExportMaterial(Models + L"Stage1/", L"France_Sky");
	exporter->ExportMeshData(Models + L"Stage1/", L"France_Sky");
	SAFE_DELETE(exporter);*/
}

ExportMesh::~ExportMesh()
{
	
}

void ExportMesh::Update()
{
	
}

void ExportMesh::Render()
{
	
}

void ExportMesh::PostRender()
{

}
