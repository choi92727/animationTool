#pragma once

#include "../Core/Vector3.h"

enum PlaneIntersectionType;
enum ContainmentType;

class BoundingBox;
class BoundingFrustum;
class Ray;
class Plane;

//////////////////////////////////////////////////////////////////////////
///@brief 충돌 구
//////////////////////////////////////////////////////////////////////////
class BoundingSphere
{
public:
	BoundingSphere(void);
	BoundingSphere(Vector3 center, float radius);

	bool operator ==(const BoundingSphere& value) const;
	bool operator !=(const BoundingSphere& value) const;

	Vector3 SupportMapping(Vector3 v);

	static BoundingSphere CreateMerged(BoundingSphere original, BoundingSphere additional);
	static BoundingSphere CreateFromBoundingBox(BoundingBox box);

	bool Intersects(BoundingBox box);
	bool Intersects(BoundingFrustum frustum);
	PlaneIntersectionType Intersects(Plane plane);
	bool Intersects(Ray ray, float& result);
	bool Intersects(BoundingSphere sphere);

	ContainmentType Contains(BoundingBox box);
	ContainmentType Contains(BoundingFrustum frustum);
	ContainmentType Contains(Vector3 point);
	ContainmentType Contains(BoundingSphere sphere);

	BoundingSphere Transform(Matrix matrix);

public:
	Vector3 Center;///< 중심점 위치
	float Radius;///< 반지름
};