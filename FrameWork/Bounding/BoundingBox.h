#pragma once

#include "../Core/Vector3.h"

enum PlaneIntersectionType;
enum ContainmentType;

class BoundingSphere;
class BoundingFrustum;
class Ray;
class Plane;

//////////////////////////////////////////////////////////////////////////
///@brief �浹 �ڽ�
//////////////////////////////////////////////////////////////////////////
class BoundingBox
{
public:
	BoundingBox(void);
	BoundingBox(Vector3 min, Vector3 max);

	bool operator ==(const BoundingBox& value) const;
	bool operator !=(const BoundingBox& value) const;

	void GetCorners(Vector3* pCorner);
	std::string ToString();

	Vector3 SupportMapping(Vector3 v); 

	static BoundingBox CreateMerged(BoundingBox original, BoundingBox additional);
	static BoundingBox CreateFromSphere(BoundingSphere sphere);

	bool Intersects(BoundingBox box);
	bool Intersects(BoundingFrustum frustum);
	PlaneIntersectionType Intersects(Plane plane);
	bool Intersects(Ray ray, float* result);
	bool Intersects(BoundingSphere sphere);

	ContainmentType Contains(BoundingBox box);
	ContainmentType Contains(BoundingFrustum frustum);
	ContainmentType Contains(Vector3 point);
	ContainmentType Contains(BoundingSphere sphere);

public:
	const static int CornerCount;///< �𼭸� ����

	Vector3 Min;///< �ּ���ġ
	Vector3 Max;///< �ִ���ġ
};