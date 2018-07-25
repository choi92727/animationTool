#pragma once

#include <string>
#pragma warning( disable : 4996)

struct D3DXVECTOR3;
class Matrix;
class Quaternion;

//////////////////////////////////////////////////////////////////////////
///@brief 3D º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
class Vector3
{
public:
	Vector3(void);
	Vector3(float value);
	Vector3(float x, float y, float z);

	Vector3 operator -(void);

	bool operator ==(const Vector3& value2) const;
	bool operator !=(const Vector3& value2) const;

	Vector3 operator +(const Vector3& value2) const;
	Vector3 operator -(const Vector3& value2) const;
	Vector3 operator *(const Vector3& value2) const;
	Vector3 operator *(const float& scaleFactor) const;
	Vector3 operator /(const Vector3& value2) const;
	Vector3 operator /(const float& divider) const;

	void operator +=(const Vector3& value2);
	void operator -=(const Vector3& value2);
	void operator *=(const Vector3& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const Vector3& value2);
	void operator /=(const float& divider);


	//////////////////////////////////////////////////////////////////////////
	///@brief floatÇüÀÇ *¿¬»ê Ã³¸®
	///@param scalefactor : °ª
	///@param value2 : º¤ÅÍ
	///@return °á°ú º¤ÅÍ
	//////////////////////////////////////////////////////////////////////////
	friend Vector3 operator *(const float scaleFactor, const Vector3& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();
	D3DXVECTOR3 ToD3DXVECTOR3();

	float Length();
	float LengthSquared();

	void Normalize();

	static float Distance(Vector3 value1, Vector3 value2);
	static float DistanceSquared(Vector3 value1, Vector3 value2);

	static float Dot(Vector3 value1, Vector3 value2);
	static Vector3 Normalize(Vector3 value);

	static Vector3 Cross(Vector3 vector1, Vector3 vector2);
	static Vector3 Reflect(Vector3 vector, Vector3 normal);

	static Vector3 Min(Vector3 value1, Vector3 value2);
	static Vector3 Max(Vector3 value1, Vector3 value2);
	static Vector3 Clamp(Vector3 value1, Vector3 min, Vector3 max);

	static Vector3 Lerp(Vector3 value1, Vector3 value2, float amount);
	static Vector3 SmoothStep(Vector3 value1, Vector3 value2, float amount);
	static Vector3 CatmullRom(Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount);
	static Vector3 Hermite(Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount);

	static Vector3 Transform(Vector3 position, Matrix matrix);
	static Vector3 Transform(Vector3 value, Quaternion rotation);
	static Vector3 TransformNormal(Vector3 normal, Matrix matrix);
	static Vector3 TransformCoord(Vector3 position, Matrix matrix);

public:
	const static Vector3 Zero;///< 0.0f, 0.0f, 0.0f
	const static Vector3 One;///< 1.0f, 1.0f, 1.0f
	
	const static Vector3 UnitX;///< 1.0f, 0.0f, 0.0f
	const static Vector3 UnitY;///< 0.0f, 1.0f, 0.0f
	const static Vector3 UnitZ;///< 0.0f, 0.0f, 1.0f

	const static Vector3 Up;///< 0.0f, 1.0f, 0.0f
	const static Vector3 Down;///< 0.0f, -1.0f, 0.0f
	const static Vector3 Right;///< 1.0f, 0.0f, 0.0f
	const static Vector3 Left;///< -1.0f, 0.0f, 0.0f
	const static Vector3 Forward;///< 0.0f, 0.0f, -1.0f
	const static Vector3 Backward;///< 0.0f, 0.0f, 1.0f

	float X;///< X
	float Y;///< Y
	float Z;///< Z
};