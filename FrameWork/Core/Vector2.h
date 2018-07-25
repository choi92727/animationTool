#pragma once

#include <string>
#pragma warning( disable : 4996)

struct D3DXVECTOR2;
class Matrix;
class Quaternion;

//////////////////////////////////////////////////////////////////////////
///@brief 2D º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
class Vector2
{
public:
	Vector2(void);
	Vector2(float value);
	Vector2(float x, float y);

	Vector2 operator -(void);

	bool operator ==(const Vector2& value2) const;
	bool operator !=(const Vector2& value2) const;

	Vector2 operator +(const Vector2& value2) const;
	Vector2 operator -(const Vector2& value2) const;
	Vector2 operator *(const Vector2& value2) const;
	Vector2 operator *(const float& scaleFactor) const;
	Vector2 operator /(const Vector2& value2) const;
	Vector2 operator /(const float& divider) const;

	void operator +=(const Vector2& value2);
	void operator -=(const Vector2& value2);
	void operator *=(const Vector2& value2);
	void operator *=(const float& scaleFactor);
	void operator /=(const Vector2& value2);
	void operator /=(const float& divider);


	//////////////////////////////////////////////////////////////////////////
	///@brief floatÇüÀÇ *¿¬»ê Ã³¸®
	///@param scalefactor : °ª
	///@param value2 : º¤ÅÍ
	///@return °á°ú º¤ÅÍ
	//////////////////////////////////////////////////////////////////////////
	friend Vector2 operator *(const float scaleFactor, const Vector2& value2)
	{
		return value2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////


	std::string ToString();
	D3DXVECTOR2 ToD3DXVECTOR2();

	float Length();
	float LengthSquared();

	void Normalize();

	static float Distance(Vector2 value1, Vector2 value2);
	static float DistanceSquared(Vector2 value1, Vector2 value2);

	static float Dot(Vector2 value1, Vector2 value2);
	static Vector2 Normalize(Vector2 value);

	static Vector2 Reflect(Vector2 vector, Vector2 normal);

	static Vector2 Min(Vector2 value1, Vector2 value2);
	static Vector2 Max(Vector2 value1, Vector2 value2);
	static Vector2 Clamp(Vector2 value1, Vector2 min, Vector2 max);

	static Vector2 Lerp(Vector2 value1, Vector2 value2, float amount);
	static Vector2 SmoothStep(Vector2 value1, Vector2 value2, float amount);
	static Vector2 CatmullRom(Vector2 value1, Vector2 value2, Vector2 value3, Vector2 value4, float amount);
	static Vector2 Hermite(Vector2 value1, Vector2 tangent1, Vector2 value2, Vector2 tangent2, float amount);

	static Vector2 Transform(Vector2 position, Matrix matrix);
	static Vector2 Transform(Vector2 value, Quaternion rotation);
	static Vector2 TransformNormal(Vector2 normal, Matrix matrix);

public:
	const static Vector2 Zero;///< 0.0f, 0.0f
	const static Vector2 One;///< 1.0f, 1.0f

	const static Vector2 UnitX;///< 1.0f, 0.0f
	const static Vector2 UnitY;///< 0.0f, 1.0f

	float X;///< X
	float Y;///< Y
};