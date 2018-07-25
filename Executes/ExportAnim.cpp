#include "stdafx.h"
#include "ExportAnim.h"
#include "./Fbx/XmlToAnim.h"

ExportAnim::ExportAnim(ExecuteValues* values)
	: Execute(values)
{
	Fbx::XmlToAnim* anim = NULL;

	vector<wstring> list;
	Path::GetFiles(&list, Assets + L"Bone/Players/Grund/", L"*.Animation", false);

	for (wstring file : list)
	{
		wstring name = Path::GetFileNameWithoutExtension(file);

		anim = new Fbx::XmlToAnim(file);
		anim->ExportAnimation(Models + L"Grund/", name);
		SAFE_DELETE(anim);
	}
}

ExportAnim::~ExportAnim()
{
	
}

void ExportAnim::Update()
{
	
}

void ExportAnim::Render()
{
	
}

void ExportAnim::PostRender()
{

}
