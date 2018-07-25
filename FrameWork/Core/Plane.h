#pragma once

#include <string>
#pragma warning( disable : 4996)

#include "Vector3.h"

enum PlaneIntersectionType;

struct D3DXPLANE;
class Vector4;
class Matrix;
class Quaternion;

class BoundingBox;
class BoundingFrustum;
class BoundingSphere;

//////////////////////////////////////////////////////////////////////////
///@brief 평면
//////////////////////////////////////////////////////////////////////////
class Plane
{
public:
	Plane(void);
	Plane(float a, float b, float c, float d);
	Plane(Vector3 normal, float d);
	Plane(Vector4 value);
	Plane(Vector3 point1, Vector3 point2, Vector3 point3);

	bool operator ==(const Plane& value) const;
	bool operator !=(const Plane& value) const;

	std::string ToString();
	D3DXPLANE ToD3DXPLANE();

	void Normalize();
	float Dot(Vector4 value);
	float DotCoordinate(Vector3 value);
	float DotNormal(Vector3 value);

	static Plane Normalize(Plane value);
	static Plane Transform(Plane plane, Matrix matrix);
	static Plane Transform(Plane plane, Quaternion rotation);

	PlaneIntersectionType Intersects(BoundingBox box);
	PlaneIntersectionType Intersects(BoundingFrustum frustum);
	PlaneIntersectionType Intersects(BoundingSphere sphere);

public:
	Vector3 Normal;///< 노멀 벡터
	float D;///< 원점으로부터의 거리
};