#pragma once

#include <string>
#pragma warning( disable : 4996)

struct D3DXQUATERNION;
class Vector3;
class Matrix;

//////////////////////////////////////////////////////////////////////////
///@brief �����
//////////////////////////////////////////////////////////////////////////
class Quaternion
{
public:
	Quaternion(void);
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 vectorPart, float scalarPart);

	Quaternion operator -(void);

	bool operator ==(const Quaternion& quaternion2) const;
	bool operator !=(const Quaternion& quaternion2) const;

	Quaternion operator +(const Quaternion& quaternion2) const;
	Quaternion operator -(const Quaternion& quaternion2) const;
	Quaternion operator *(const Quaternion& quaternion2) const;
	Quaternion operator *(const float& scaleFactor) const;
	Quaternion operator /(const Quaternion& quaternion2) const;

	void operator +=(const Quaternion& quaternion2);
	void operator -=(const Quaternion& quaternion2);
	void operator *=(const Quaternion& quaternion2);
	void operator *=(const float& scaleFactor);
	void operator /=(const Quaternion& quaternion2);


	//////////////////////////////////////////////////////////////////////////
	///@brief float���� *���� ó��
	///@param scalefactor : ��
	///@param value2 : ����
	///@return ��� ����
	//////////////////////////////////////////////////////////////////////////
	friend Quaternion operator *(const float scaleFactor, const Quaternion& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();
	D3DXQUATERNION ToD3DXQUATERNION();

	float Length();
	float LengthSquared();

	void Normalize();
	static Quaternion Normalize(Quaternion quaternion);

	void Conjugate();
	static Quaternion Conjugate(Quaternion value);
	static Quaternion Inverse(Quaternion quaternion);

	static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static Quaternion CreateFromRotationMatrix(Matrix matrix);

	static float Dot(Quaternion quaternion1, Quaternion quaternion2);

	static Quaternion Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount);
	static Quaternion Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount);

	static Quaternion Concatenate(Quaternion value1, Quaternion value2);

public:
	const static Quaternion Identity;///< 0.0f, 0.0f, 0.0f, 1.0f

	float X;///< X
	float Y;///< Y
	float Z;///< Z
	float W;///< W
};