
#pragma once
namespace Gizmo
{
	class GizmoComponent;
}
class ModelTool : public Execute
{
public:
	ModelTool(ExecuteValues* values);
	~ModelTool();

	void Update();

	void PreRender() {}
	void Render();
	void PostRender();

	void ResizeScreen() {}


private:
	void CreateModelTrees(class ModelBone* bone);
	void ControlAnimPlayer();
	D3DXMATRIX reculsiveBone_Transform(int index);

	void ExportModel();
private:
	int currentSelectBone;
	D3DXMATRIX targetMat;
	
	class ToolsModel* player;
	class Exporter* exporter;
	Gizmo::GizmoComponent* component;
};