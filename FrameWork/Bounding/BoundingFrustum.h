#pragma once

#include "Gjk.h"
#include "../Core/Vector3.h"
#include "../Core/Matrix.h"
#include "../Core/Plane.h"

enum PlaneIntersectionType;
enum ContainmentType;

class Ray;
class BoundingBox;
class BoundingSphere;

//////////////////////////////////////////////////////////////////////////
///@brief 충돌 프러스텀
//////////////////////////////////////////////////////////////////////////
class BoundingFrustum
{
public:
	BoundingFrustum(void);
	BoundingFrustum(Matrix value);

	bool operator ==(const BoundingFrustum& value) const;
	bool operator !=(const BoundingFrustum& value) const;
	bool Equals(const BoundingFrustum& value) const;

	std::string ToString();

	Vector3 SupportMapping(Vector3 v);

	Plane Near() const;
	Plane Far() const;
	Plane Left() const;
	Plane Right() const;
	Plane Top() const;
	Plane Bottom() const;

	Matrix GetMatrix() const;
	void SetMatrix(const Matrix value);

	void GetCorner(Vector3* pCorner);

	static Ray ComputeIntersectionLine(Plane p1, Plane p2);
	static Vector3 ComputeIntersection(Plane plane, Ray ray);

	bool Intersects(BoundingBox box);
	void Intersects(BoundingBox box, bool& result);
	bool Intersects(BoundingFrustum frustum);
	void Intersects(Plane plane, PlaneIntersectionType& result);
	void Intersects(Ray ray, float* result);
	bool Intersects(BoundingSphere sphere);
	void Intersects(BoundingSphere sphere, bool& result);

	ContainmentType Contains(BoundingBox box);
	ContainmentType Contains(BoundingFrustum frustum);
	ContainmentType Contains(Vector3 point);
	ContainmentType Contains(BoundingSphere sphere);

public:
	const static int CornerCount;
	const static int NearPlaneIndex;
	const static int FarPlaneIndex;
	const static int LeftPlaneIndex;
	const static int RightPlaneIndex;
	const static int TopPlaneIndex;
	const static int BottomPlaneIndex;
	const static int NumPlanes;

	Plane planes[6];
	Vector3 cornerArray[8];
	Matrix matrix;
	Gjk gjk;
};