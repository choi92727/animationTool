#pragma once
#include "./Framework/Bounding/BoundingBox.h"
#include "./Framework/Bounding/BoundingSphere.h"

namespace Gizmo
{
	class Gizmo;

	enum class EGizmoMode
	{
		Scale = 0, Rotate, Translate
	};

	enum class EGizmoAxis
	{
		None = -1, X, Y, Z,
		XY, ZX, YZ,
	};

	class GizmoComponent
	{
	public:
		GizmoComponent(ExecuteValues* values);
		~GizmoComponent();

		void Update();
		void Render();
		void PostRender();

		void Position(const D3DXVECTOR3& value) { position = value; }
		void SetTarget(D3DXMATRIX* target) { this->target = target; }
		void Transform(D3DXMATRIX& val) { gizmoWorld = val; }
		void OutsideWorld(D3DXMATRIX& val) { outsideWorld = val; }
		D3DXMATRIX TransformDelta();
	private:
		//Initialize
		void Init();

		//Draw
		void Draw2D();
		void Draw3D();
		void DrawBounding();

		//Create
		void Create2D();
		void Create3D();
		void CreateBoundings();

		//Reset
		void ResetHighlight();
		void ResetMouseValues();
		void ResetDeltas();
		void ResetScaleGizmo();

		//Mouse
		void MouseCollision();
		void Pressing();
		Ray ConvertMouseToRay(D3DXMATRIX& world);

		//ResizeWorldScale
		void ResizeWorldScale();
	private:
		//Gizmos
		D3DXMATRIX geometryWorld[3];
		D3DXCOLOR colors[3];
		vector<Gizmo *> quads;
		vector<Gizmo *> lines;
		vector<Gizmo *> scales, rotates, translates;
		vector<Gizmo *> boxes;
		vector<Gizmo *> spheres;

		//Boundings		
		class BoundingBox* xAxisBox, *yAxisBox, *zAxisBox;
		class BoundingBox* xyAxisBox, *yzAxisBox, *xzAxisBox;
		class BoundingSphere* xSphere, *ySphere, *zSphere;
		bool bDrawBounding;

		//Line
		const float LINE_LENGTH = 3.0f;
		const float LINE_OFFSET = 1.0f;

		//Enum
		EGizmoMode activeMode;
		EGizmoAxis activeAxis;

		//MousePos
		Vector3 intersectPosition, lastIntersectPosition, delta;
		D3DXVECTOR3 curMousePos, lastMousePos;
		bool bMousePressed;

		//Transform
		D3DXMATRIX outsideWorld;
		D3DXMATRIX gizmoWorld;
		D3DXVECTOR3 scale, rotate, position;
		D3DXMATRIX scaleMat, rotMat, posMat;
		D3DXQUATERNION rotQuat;
		const float ROTATE_WEIGHT = 10.0f;
		const float SCALE_WEIGHT = 0.1f;
		const float RESIZE_RATIO = 30.0f;

		//Deltas
		D3DXVECTOR3 translationDelta, scaleDelta;
		D3DXMATRIX rotationDelta;

		//States
		ID3D11RasterizerState* rasterizer[2];
		ID3D11DepthStencilState* depthStencilState[2];

		//GlobalValue
		ExecuteValues* values;

		//Target
		D3DXMATRIX* target;
	};
}