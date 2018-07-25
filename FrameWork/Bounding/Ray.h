#pragma once

#include "../Core/Vector3.h"

class BoundingBox;
class BoundingFrustum;
class BoundingSphere;
class Plane;

//////////////////////////////////////////////////////////////////////////
///@brief �浹 ����
//////////////////////////////////////////////////////////////////////////
class Ray
{
public:
	Ray(void);
	Ray(Vector3 position, Vector3 direction);

	bool operator ==(const Ray& value) const;
	bool operator !=(const Ray& value) const;

	std::string ToString();

	bool Intersects(Plane& plane, float& value);
	bool Intersects(BoundingSphere& sphere, float& value);

public:
	Vector3 Position;///< ��ġ
	Vector3 Direction;///< ����
};