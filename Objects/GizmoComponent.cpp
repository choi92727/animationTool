#include "stdafx.h"
#include "GizmoComponent.h"
#include "./Framework/Core/Matrix.h"
#include "./Framework/Core/Vector3.h"
#include "./Framework/Bounding/Ray.h"
#include "./Framework/Core/Plane.h"

#include "Gizmo.h"


Gizmo::GizmoComponent::GizmoComponent(ExecuteValues* values)
	:values(values)
{
	Init();
}

Gizmo::GizmoComponent::~GizmoComponent()
{
	SAFE_RELEASE(rasterizer[0]);
	SAFE_RELEASE(rasterizer[1]);

	SAFE_RELEASE(depthStencilState[0]);
	SAFE_RELEASE(depthStencilState[1]);

	for (Gizmo* gizmo : quads)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : lines)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : scales)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : rotates)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : translates)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : boxes)
		SAFE_DELETE(gizmo);
	for (Gizmo* gizmo : spheres)
		SAFE_DELETE(gizmo);
}

D3DXMATRIX Gizmo::GizmoComponent::TransformDelta()
{
	scaleDelta *= SCALE_WEIGHT;
	D3DXMATRIX S, T, T2;

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&T);
	D3DXMatrixIdentity(&T2);

	//Inverse
	D3DXMATRIX invRot;
	D3DXMatrixInverse(&invRot, NULL, &rotMat);

	D3DXMATRIX invPos;
	D3DXMatrixTranslation(&T2, position.x, position.y, position.z);
	D3DXMatrixInverse(&invPos, NULL, &T2);

	D3DXVECTOR3 tempScale = { 1,1,1 };
	if (scaleDelta != D3DXVECTOR3(0, 0, 0))
	{
		tempScale += scaleDelta;
		D3DXMatrixScaling(&S, tempScale.x, tempScale.y, tempScale.z);

		//축방향으로 스케일하기 위해
		S = invPos*invRot*S*rotMat*T2;
	}

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	if (rotationDelta != identity)
	{
		//모델 중심으로 회전
		rotationDelta = invPos*rotationDelta*T2;
	}

	if (translationDelta != D3DXVECTOR3(0, 0, 0))
	{
		//이동값은 방향구해서 가져왔으니 바로계산
		D3DXMatrixTranslation(&T, translationDelta.x, translationDelta.y, translationDelta.z);
		translationDelta = { 0,0,0 };
	}

	D3DXMATRIX ret = S* rotationDelta* T;
	D3DXMatrixIdentity(&rotationDelta);
	return ret;

}

void Gizmo::GizmoComponent::Init()
{
	{
		D3D11_RASTERIZER_DESC desc;
		States::GetRasterizerDesc(&desc);
		States::CreateRasterizer(&desc, &rasterizer[0]);

		desc.CullMode = D3D11_CULL_NONE;
		States::CreateRasterizer(&desc, &rasterizer[1]);
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc;
		States::GetDepthStencilDesc(&desc);
		States::CreateDepthStencil(&desc, &depthStencilState[0]);

		desc.DepthEnable = false;
		States::CreateDepthStencil(&desc, &depthStencilState[1]);
	}

	target = NULL;
	D3DXMatrixIdentity(&gizmoWorld);
	D3DXMatrixIdentity(&outsideWorld);

	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&posMat);

	D3DXQuaternionIdentity(&rotQuat);

	scale = { 1,1,1 };
	rotate = { 0,0,0 };
	position = { 0,0,0 };

	ResetMouseValues();
	ResetDeltas();

	bMousePressed = false;
	bDrawBounding = false;
	activeMode = EGizmoMode::Translate;
	activeAxis = EGizmoAxis::None;

	colors[0] = D3DXCOLOR(1, 0, 0, 1);
	colors[1] = D3DXCOLOR(0, 1, 0, 1);
	colors[2] = D3DXCOLOR(0, 0, 1, 1);

	geometryWorld[0] = Matrix::CreateWorld(Vector3(LINE_LENGTH, 0, 0), Vector3::Left, Vector3::Up).ToD3DXMATRIX();
	geometryWorld[1] = Matrix::CreateWorld(Vector3(0, LINE_LENGTH, 0), Vector3::Down, Vector3::Left).ToD3DXMATRIX();
	geometryWorld[2] = Matrix::CreateWorld(Vector3(0, 0, LINE_LENGTH), Vector3::Forward, Vector3::Up).ToD3DXMATRIX();

	Create2D();
	Create3D();
	CreateBoundings();
}

void Gizmo::GizmoComponent::MouseCollision()
{
	float* distance = NULL;
	float sphereDist = 0;
	Ray ray = ConvertMouseToRay(gizmoWorld);

	if (xAxisBox->Intersects(ray, distance) || xSphere->Intersects(ray, sphereDist))
		activeAxis = EGizmoAxis::X;
	else if (yAxisBox->Intersects(ray, distance) || ySphere->Intersects(ray, sphereDist))
		activeAxis = EGizmoAxis::Y;
	else if (zAxisBox->Intersects(ray, distance) || zSphere->Intersects(ray, sphereDist))
		activeAxis = EGizmoAxis::Z;
	else if (xyAxisBox->Intersects(ray, distance))
		activeAxis = EGizmoAxis::XY;
	else if (xzAxisBox->Intersects(ray, distance))
		activeAxis = EGizmoAxis::ZX;
	else if (yzAxisBox->Intersects(ray, distance))
		activeAxis = EGizmoAxis::YZ;
	else
		activeAxis = EGizmoAxis::None;

	SAFE_DELETE(distance);

	//highlight color
	ResetHighlight();
	switch (activeAxis)
	{
	case EGizmoAxis::None:
		break;
	case EGizmoAxis::X:
	case EGizmoAxis::Y:
	case EGizmoAxis::Z:
	{
		int index = (int)activeAxis;
		lines[index]->bHighlight = true;
		scales[index]->bHighlight = true;
		rotates[index]->bHighlight = true;
		translates[index]->bHighlight = true;
	}
	break;
	case EGizmoAxis::XY:
		quads[0]->bHighlight = true;
		break;
	case EGizmoAxis::ZX:
		quads[1]->bHighlight = true;
		break;
	case EGizmoAxis::YZ:
		quads[2]->bHighlight = true;
		break;
	}
}

void Gizmo::GizmoComponent::Pressing()
{
	D3DXVECTOR3 tempPos;
	D3DXMATRIX invRot;
	D3DXMatrixInverse(&invRot, NULL, &rotMat);
	D3DXVec3TransformCoord(&tempPos, &position, &invRot);
	Vector3 tempPos2 = { tempPos.x, tempPos.y, tempPos.z };

	//Collision Plane
	Plane planeXY = Plane(Vector3::Forward, -tempPos2.Z);
	Plane planeYZ = Plane(Vector3::Left, tempPos2.X);
	Plane planeZX = Plane(Vector3::Down, tempPos2.Y);

	Ray ray = ConvertMouseToRay(rotMat);

	float value = 0;
	lastIntersectPosition = intersectPosition;
	switch (activeAxis)
	{
	case EGizmoAxis::None:
		break;
	case EGizmoAxis::XY:
	case EGizmoAxis::X:
		if (ray.Intersects(planeXY, value))
		{
			intersectPosition = (ray.Position + (ray.Direction * value));
			if (lastIntersectPosition != Vector3::Zero)
			{
				delta = intersectPosition - lastIntersectPosition;
			}
			delta = activeAxis == EGizmoAxis::X ? Vector3(delta.X, 0, 0) : Vector3(delta.X, delta.Y, 0);
		}
		break;
	case EGizmoAxis::Z:
	case EGizmoAxis::YZ:
	case EGizmoAxis::Y:
		if (ray.Intersects(planeYZ, value))
		{
			intersectPosition = (ray.Position + (ray.Direction * value));
			if (lastIntersectPosition != Vector3::Zero)
			{
				delta = intersectPosition - lastIntersectPosition;
			}
			switch (activeAxis)
			{
			case EGizmoAxis::Y:
				delta = Vector3(0, delta.Y, 0);
				break;
			case EGizmoAxis::Z:
				delta = Vector3(0, 0, delta.Z);
				break;
			default:
				delta = Vector3(0, delta.Y, delta.Z);
				break;
			}
		}
		break;
	case EGizmoAxis::ZX:
		if (ray.Intersects(planeZX, value))
		{
			intersectPosition = (ray.Position + (ray.Direction * value));
			if (lastIntersectPosition != Vector3::Zero)
			{
				delta = intersectPosition - lastIntersectPosition;
			}
			delta = Vector3(delta.X, 0, delta.Z);
		}
		break;
	}

	//ActiveMode

	switch (activeMode)
	{
	case EGizmoMode::Scale:
	{
		scaleDelta += D3DXVECTOR3(delta.X, delta.Y, delta.Z);
		D3DXMATRIX deltaTranslation;
		D3DXMatrixTranslation(&deltaTranslation, delta.X, delta.Y, delta.Z);
		switch (activeAxis)
		{
		case EGizmoAxis::X:
		case EGizmoAxis::Y:
		case EGizmoAxis::Z:
			int index = (int)activeAxis;
			lines[index]->vertexData[1].position += scaleDelta;
			geometryWorld[index] *= deltaTranslation;
			lines[index]->UpdateVertexData();
			break;
		}
	}
	break;

	case EGizmoMode::Rotate:
	{
		lastMousePos = curMousePos;
		curMousePos = Mouse::Get()->GetPosition();
		float deltaX = 0;
		if (lastMousePos != D3DXVECTOR3(0, 0, 0))
			deltaX = curMousePos.x - lastMousePos.x;

		D3DXVECTOR3 rotVec = D3DXVECTOR3(
			Math::ToRadian(deltaX * ROTATE_WEIGHT), Math::ToRadian(deltaX * ROTATE_WEIGHT), Math::ToRadian(deltaX * ROTATE_WEIGHT));

		D3DXMATRIX rot, tempRot;
		D3DXMatrixIdentity(&rot);
		rot = rotMat;

		D3DXVECTOR3 vecX, vecY, vecZ;
		vecX = D3DXVECTOR3(rot._11, rot._12, rot._13);
		vecY = D3DXVECTOR3(rot._21, rot._22, rot._23);
		vecZ = D3DXVECTOR3(rot._31, rot._32, rot._33);

		D3DXQUATERNION q;
		D3DXQuaternionIdentity(&q);
		switch (activeAxis)
		{
		case EGizmoAxis::X:
			D3DXMatrixRotationAxis(&tempRot, &vecX, rotVec.x);
			D3DXQuaternionRotationAxis(&q, &vecX, rotVec.x);
			break;
		case EGizmoAxis::Y:
			D3DXMatrixRotationAxis(&tempRot, &vecY, rotVec.y);
			D3DXQuaternionRotationAxis(&q, &vecY, rotVec.y);
			break;
		case EGizmoAxis::Z:
			D3DXMatrixRotationAxis(&tempRot, &vecZ, rotVec.z);
			D3DXQuaternionRotationAxis(&q, &vecZ, rotVec.z);
			break;
		}

		rotQuat *= q;
		D3DXMatrixRotationQuaternion(&rotationDelta, &q);
		D3DXMatrixRotationQuaternion(&rotMat, &rotQuat);
	}
	break;

	case EGizmoMode::Translate:
	{
		D3DXVECTOR3 temp, temp2;
		temp2 = { delta.X, delta.Y, delta.Z };
		D3DXVec3TransformCoord(&temp, &temp2, &rotMat);
		position += temp;
		translationDelta += temp;
	}
	break;
	}
}

void Gizmo::GizmoComponent::Update()
{
	//TargetTransform
	if (target != NULL)
	{
		D3DXMATRIX targetMat = *target;
		D3DXMATRIX deltaMat = TransformDelta();

		targetMat *= deltaMat;
		*target = targetMat;
	}

	//ResizeWorldScale
	//TODO: 모델거리에 비례해서 기즈모 크기조절
	ResizeWorldScale();

	if (Keyboard::Get()->Down('1'))
		activeMode = EGizmoMode::Translate;
	if (Keyboard::Get()->Down('2'))
		activeMode = EGizmoMode::Rotate;
	if (Keyboard::Get()->Down('3'))
		activeMode = EGizmoMode::Scale;

	//MouseInput
	if (Mouse::Get()->Down(0))
	{
		MouseCollision();
		bMousePressed = true;
	}
	if (bMousePressed)
	{
		ResetDeltas();
		Pressing();
	}
	if (Mouse::Get()->Up(0))
	{
		bMousePressed = false;
		ResetMouseValues();
		ResetDeltas();
		ResetHighlight();
		ResetScaleGizmo();
	}

	//GizmoWorld
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&posMat, position.x, position.y, position.z);

	gizmoWorld = scaleMat*rotMat*posMat;
}

void Gizmo::GizmoComponent::Render()
{
	D3D::GetDC()->OMSetDepthStencilState(depthStencilState[1], 1);
	D3D::GetDC()->RSSetState(rasterizer[1]);
	{
		Draw2D();
		Draw3D();

		if (bDrawBounding == true)
			DrawBounding();
	}
	D3D::GetDC()->RSSetState(rasterizer[0]);
	D3D::GetDC()->OMSetDepthStencilState(depthStencilState[0], 1);
}

void Gizmo::GizmoComponent::PostRender()
{
	ImGui::Begin("Gizmo");

	ImGui::Checkbox("DrawBounding", &bDrawBounding);
	ImGui::InputFloat3("Intersect Position", (float*)&intersectPosition);
	ImGui::InputFloat3("LastIntersect Position", (float*)&lastIntersectPosition);
	ImGui::InputFloat3("Delta", (float*)&delta);
	ImGui::End();
}

void Gizmo::GizmoComponent::Draw2D()
{
	for (size_t i = 0; i < quads.size(); i++)
	{
		if (activeMode == EGizmoMode::Translate)
		{
			quads[i]->rootWorld = gizmoWorld;
			quads[i]->color = colors[i];
			quads[i]->Render();
		}
	}

	for (size_t i = 0; i < lines.size(); i++)
	{
		lines[i]->rootWorld = gizmoWorld;
		lines[i]->color = colors[i];
		lines[i]->Render();
	}
}

void Gizmo::GizmoComponent::Draw3D()
{
	for (int i = 0; i < 3; i++) //(order: x, y, z)
	{
		Gizmo* activeModel;
		switch (activeMode)
		{
		case EGizmoMode::Translate:
			activeModel = translates[i];
			break;
		case EGizmoMode::Rotate:
			activeModel = rotates[i];
			break;
		case EGizmoMode::Scale:
			activeModel = scales[i];
			break;
		}

		activeModel->rootWorld = gizmoWorld;
		activeModel->localWorld = geometryWorld[i];
		activeModel->color = colors[i];

		activeModel->Render();
	}
}

void Gizmo::GizmoComponent::DrawBounding()
{
	for (Gizmo* gizmo : boxes)
	{
		gizmo->rootWorld = gizmoWorld;
		gizmo->Render();
	}
	for (Gizmo* gizmo : spheres)
	{
		gizmo->rootWorld = gizmoWorld;
		gizmo->Render();
	}

}

void Gizmo::GizmoComponent::Create2D()
{
	//Quads
	float halfLineOffset = LINE_OFFSET / 2;
	quads.push_back(Gizmos::Quad(D3DXVECTOR3(halfLineOffset, halfLineOffset, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR3(0, 1, 0), LINE_OFFSET,
		LINE_OFFSET)); //XY
	quads.push_back(Gizmos::Quad(D3DXVECTOR3(halfLineOffset, 0, halfLineOffset), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(1, 0, 0), LINE_OFFSET,
		LINE_OFFSET)); //XZ
	quads.push_back(Gizmos::Quad(D3DXVECTOR3(0, halfLineOffset, halfLineOffset), D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 1, 0), LINE_OFFSET,
		LINE_OFFSET)); //ZY 

					   //Lines
	lines.push_back(Gizmos::Line({ 0,0,0 }, { LINE_LENGTH, 0,0 }));
	lines.push_back(Gizmos::Line({ 0,0,0 }, { 0, LINE_LENGTH,0 }));
	lines.push_back(Gizmos::Line({ 0,0,0 }, { 0, 0,LINE_LENGTH }));
}

void Gizmo::GizmoComponent::Create3D()
{
	for (size_t i = 0; i < 3; i++)
	{
		scales.push_back(Gizmos::Scale());
		rotates.push_back(Gizmos::Rotate());
		translates.push_back(Gizmos::Translate());
	}
}

void Gizmo::GizmoComponent::CreateBoundings()
{
	//Boxes
	const float MULTI_AXIS_THICKNESS = 0.05f;
	const float SINGLE_AXIS_THICKNESS = 0.2f;

	xAxisBox = new BoundingBox(Vector3(LINE_OFFSET, 0, 0),
		Vector3(LINE_OFFSET + LINE_LENGTH, SINGLE_AXIS_THICKNESS, SINGLE_AXIS_THICKNESS));

	boxes.push_back(Gizmos::WireCube({ LINE_OFFSET, 0, 0 },
	{ LINE_OFFSET + LINE_LENGTH, SINGLE_AXIS_THICKNESS, SINGLE_AXIS_THICKNESS }));

	yAxisBox = new BoundingBox(Vector3(0, LINE_OFFSET, 0),
		Vector3(SINGLE_AXIS_THICKNESS, LINE_OFFSET + LINE_LENGTH, SINGLE_AXIS_THICKNESS));

	boxes.push_back(Gizmos::WireCube({ 0, LINE_OFFSET, 0 },
	{ SINGLE_AXIS_THICKNESS, LINE_OFFSET + LINE_LENGTH, SINGLE_AXIS_THICKNESS }));

	zAxisBox = new BoundingBox(Vector3(0, 0, LINE_OFFSET),
		Vector3(SINGLE_AXIS_THICKNESS, SINGLE_AXIS_THICKNESS, LINE_OFFSET + LINE_LENGTH));

	boxes.push_back(Gizmos::WireCube({ 0, 0, LINE_OFFSET },
	{ SINGLE_AXIS_THICKNESS, SINGLE_AXIS_THICKNESS, LINE_OFFSET + LINE_LENGTH }));

	xzAxisBox = new BoundingBox(Vector3::Zero,
		Vector3(LINE_OFFSET, MULTI_AXIS_THICKNESS, LINE_OFFSET));

	boxes.push_back(Gizmos::WireCube({ 0, 0, 0 },
	{ LINE_OFFSET, MULTI_AXIS_THICKNESS, LINE_OFFSET }));

	xyAxisBox = new BoundingBox(Vector3::Zero,
		Vector3(LINE_OFFSET, LINE_OFFSET, MULTI_AXIS_THICKNESS));

	boxes.push_back(Gizmos::WireCube({ 0, 0, 0 },
	{ LINE_OFFSET, LINE_OFFSET, MULTI_AXIS_THICKNESS }));

	yzAxisBox = new BoundingBox(Vector3::Zero,
		Vector3(MULTI_AXIS_THICKNESS, LINE_OFFSET, LINE_OFFSET));

	boxes.push_back(Gizmos::WireCube({ 0, 0, 0 },
	{ MULTI_AXIS_THICKNESS, LINE_OFFSET, LINE_OFFSET }));

	//Spheres
	const float RADIUS = 1.0f;
	D3DXVECTOR3 position = lines[0]->vertexData[1].position;
	Vector3 temp = { position.x, position.y, position.z };
	xSphere = new BoundingSphere(temp, RADIUS);
	spheres.push_back(Gizmos::WireSphere(position, RADIUS));

	position = lines[1]->vertexData[1].position;
	temp = { position.x, position.y, position.z };
	ySphere = new BoundingSphere(temp, RADIUS);
	spheres.push_back(Gizmos::WireSphere(position, RADIUS));

	position = lines[2]->vertexData[1].position;
	temp = { position.x, position.y, position.z };
	zSphere = new BoundingSphere(temp, RADIUS);
	spheres.push_back(Gizmos::WireSphere(position, RADIUS));
}

void Gizmo::GizmoComponent::ResetHighlight()
{
	for (Gizmo* gizmo : quads)
		gizmo->bHighlight = false;
	for (Gizmo* gizmo : lines)
		gizmo->bHighlight = false;
	for (Gizmo* gizmo : scales)
		gizmo->bHighlight = false;
	for (Gizmo* gizmo : rotates)
		gizmo->bHighlight = false;
	for (Gizmo* gizmo : translates)
		gizmo->bHighlight = false;
}

void Gizmo::GizmoComponent::ResetMouseValues()
{
	intersectPosition = lastIntersectPosition = delta = Vector3::Zero;
	curMousePos = lastMousePos = { 0,0,0 };
}

void Gizmo::GizmoComponent::ResetDeltas()
{
	translationDelta = scaleDelta = { 0,0,0 };
	D3DXMatrixIdentity(&rotationDelta);
}

void Gizmo::GizmoComponent::ResetScaleGizmo()
{
	geometryWorld[0] = Matrix::CreateWorld(Vector3(LINE_LENGTH, 0, 0), Vector3::Left, Vector3::Up).ToD3DXMATRIX();
	geometryWorld[1] = Matrix::CreateWorld(Vector3(0, LINE_LENGTH, 0), Vector3::Down, Vector3::Left).ToD3DXMATRIX();
	geometryWorld[2] = Matrix::CreateWorld(Vector3(0, 0, LINE_LENGTH), Vector3::Forward, Vector3::Up).ToD3DXMATRIX();

	lines[0]->vertexData[1].position = { LINE_LENGTH, 0,0 };
	lines[1]->vertexData[1].position = { 0, LINE_LENGTH,0 };
	lines[2]->vertexData[1].position = { 0, 0,LINE_LENGTH };

	for (size_t i = 0; i < lines.size(); i++)
	{
		lines[i]->UpdateVertexData();
	}
}

Ray Gizmo::GizmoComponent::ConvertMouseToRay(D3DXMATRIX& world)
{
	//mouse pos, dir
	D3DXVECTOR3 start;
	values->MainCamera->GetPosition(&start);
	D3DXVECTOR3 dir = values->MainCamera->GetDirection(values->Viewport, values->Perspective);

	//inverse
	D3DXMATRIX invMat;
	D3DXMatrixInverse(&invMat, NULL, &world);
	D3DXVec3TransformCoord(&start, &start, &invMat);
	D3DXVec3TransformNormal(&dir, &dir, &invMat);

	//ray
	Ray ray = Ray(Vector3(start.x, start.y, start.z), Vector3(dir.x, dir.y, dir.z));
	return ray;
}

void Gizmo::GizmoComponent::ResizeWorldScale()
{
	if (target != NULL)
	{
		D3DXVECTOR3 targetPos, cameraPos, distance;
		targetPos = { target->_41, target->_42, target->_43 };
		values->MainCamera->GetPosition(&cameraPos);
		distance = targetPos - cameraPos;

		float scaleValue = D3DXVec3Length(&distance);
		scaleValue /= RESIZE_RATIO;
		scale = { scaleValue,scaleValue,scaleValue };
	}
}
