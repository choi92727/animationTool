#include "Vector4.h"

#include <d3dx9math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////

const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

const Vector4 Vector4::UnitX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
//////////////////////////////////////////////////////////////////////////
Vector4::Vector4( void )
{
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
	this->W = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param x : X
///@param y : Y
///@param z : Z
///@param w : W
//////////////////////////////////////////////////////////////////////////
Vector4::Vector4( float x, float y, float z, float w )
{
	this->X = x;
	this->Y = y;
	this->Z = z;
	this->W = w;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param value : x, y
///@param z : Z
///@param w : W
//////////////////////////////////////////////////////////////////////////
Vector4::Vector4( Vector2 value, float z, float w )
{
	this->X = value.X;
	this->Y = value.Y;
	this->Z = z;
	this->W = w;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param value : x, y, z
///@param w : W
//////////////////////////////////////////////////////////////////////////
Vector4::Vector4( Vector3 value, float w )
{
	this->X = value.X;
	this->Y = value.Y;
	this->Z = value.Z;
	this->W = w;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param x = y = z = w = value
//////////////////////////////////////////////////////////////////////////
Vector4::Vector4( float value )
{
	this->X = this->Y = this->Z = this->W = value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator-( void )
{
	Vector4 vector4;
	vector4.X = -this->X;
	vector4.Y = -this->Y;
	vector4.Z = -this->Z;
	vector4.W = -this->W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool Vector4::operator==( const Vector4& value2 ) const
{
	if ((double)this->X == (double)value2.X && (double)this->Y == (double)value2.Y && (double)this->Z == (double)value2.Z)
		return (double)this->W == (double)value2.W;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool Vector4::operator!=( const Vector4& value2 ) const
{
	if ((double)this->X == (double)value2.X && (double)this->Y == (double)value2.Y && (double)this->Z == (double)value2.Z)
		return (double)this->W != (double)value2.W;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator+( const Vector4& value2 ) const
{
	Vector4 vector4;
	vector4.X = this->X + value2.X;
	vector4.Y = this->Y + value2.Y;
	vector4.Z = this->Z + value2.Z;
	vector4.W = this->W + value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator-( const Vector4& value2 ) const
{
	Vector4 vector4;
	vector4.X = this->X - value2.X;
	vector4.Y = this->Y - value2.Y;
	vector4.Z = this->Z - value2.Z;
	vector4.W = this->W - value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator*( const Vector4& value2 ) const
{
	Vector4 vector4;
	vector4.X = this->X * value2.X;
	vector4.Y = this->Y * value2.Y;
	vector4.Z = this->Z * value2.Z;
	vector4.W = this->W * value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator*( const float& scaleFactor ) const
{
	Vector4 vector4;
	vector4.X = this->X * scaleFactor;
	vector4.Y = this->Y * scaleFactor;
	vector4.Z = this->Z * scaleFactor;
	vector4.W = this->W * scaleFactor;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator/( const Vector4& value2 ) const
{
	Vector4 vector4;
	vector4.X = this->X / value2.X;
	vector4.Y = this->Y / value2.Y;
	vector4.Z = this->Z / value2.Z;
	vector4.W = this->W / value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::operator/( const float& divider ) const
{
	float num = 1.0f / divider;

	Vector4 vector4;
	vector4.X = this->X * num;
	vector4.Y = this->Y * num;
	vector4.Z = this->Z * num;
	vector4.W = this->W * num;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator+=( const Vector4& value2 )
{
	*this = *this + value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator-=( const Vector4& value2 )
{
	*this = *this - value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator*=( const Vector4& value2 )
{
	*this = *this * value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator*=( const float& scaleFactor )
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator/=( const Vector4& value2 )
{
	*this = *this / value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector4::operator/=( const float& divider )
{
	*this = *this / divider;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¹®ÀÚ¿­·Î º¯È¯
///@return ¹®ÀÚ¿­
//////////////////////////////////////////////////////////////////////////
std::string Vector4::ToString()
{
	std::string temp;
	char val[255];

	sprintf(val, "{X:%#f ", X); temp += val; 
	sprintf(val, "Y:%#f ", Y); temp += val;
	sprintf(val, "Z:%#f ", Z); temp += val;
	sprintf(val, "W:%#f}", W); temp += val;

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief D3DXVECTOR4·Î º¯È¯
///@return D3DX º¤ÅÍ 
//////////////////////////////////////////////////////////////////////////
D3DXVECTOR4 Vector4::ToD3DXVECTOR4()
{
	D3DXVECTOR4 vector4;
	vector4.x = X;
	vector4.y = Y;
	vector4.z = Z;
	vector4.z = W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector4::Length()
{
	return (float)sqrt((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z + (double)this->W * (double)this->W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector4::LengthSquared()
{
	return (float)((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z + (double)this->W * (double)this->W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
//////////////////////////////////////////////////////////////////////////
void Vector4::Normalize()
{
	float num = 1.0f / (float)sqrt((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z + (double)this->W * (double)this->W);

	this->X *= num;
	this->Y *= num;
	this->Z *= num;
	this->W *= num;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector4::Distance( Vector4 value1, Vector4 value2 )
{
	float num1 = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;
	float num4 = value1.W - value2.W;

	return (float)sqrt((double)num1 * (double)num1 + (double)num2 * (double)num2 + (double)num3 * (double)num3 + (double)num4 * (double)num4);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector4::DistanceSquared( Vector4 value1, Vector4 value2 )
{
	float num1 = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;
	float num4 = value1.W - value2.W;

	return (float)((double)num1 * (double)num1 + (double)num2 * (double)num2 + (double)num3 * (double)num3 + (double)num4 * (double)num4);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ³»Àû °è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector4::Dot( Vector4 value1, Vector4 value2 )
{
	return (float)((double)value1.X * (double)value2.X + (double)value1.Y * (double)value2.Y + (double)value1.Z * (double)value2.Z + (double)value1.W * (double)value2.W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
///@param value : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Normalize( Vector4 value )
{
	float num = 1.0f / (float)sqrt((double)value.X * (double)value.X + (double)value.Y * (double)value.Y + (double)value.Z * (double)value.Z + (double)value.W * (double)value.W);

	Vector4 vector4;
	vector4.X = value.X * num;
	vector4.Y = value.Y * num;
	vector4.Z = value.Z * num;
	vector4.W = value.W * num;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß ÀÛÀº º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Min( Vector4 value1, Vector4 value2 )
{
	Vector4 vector4;
	vector4.X = (double)value1.X < (double)value2.X ? value1.X : value2.X;
	vector4.Y = (double)value1.Y < (double)value2.Y ? value1.Y : value2.Y;
	vector4.Z = (double)value1.Z < (double)value2.Z ? value1.Z : value2.Z;
	vector4.W = (double)value1.W < (double)value2.W ? value1.W : value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß Å« º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Max( Vector4 value1, Vector4 value2 )
{
	Vector4 vector4;
	vector4.X = (double)value1.X > (double)value2.X ? value1.X : value2.X;
	vector4.Y = (double)value1.Y > (double)value2.Y ? value1.Y : value2.Y;
	vector4.Z = (double)value1.Z > (double)value2.Z ? value1.Z : value2.Z;
	vector4.W = (double)value1.W > (double)value2.W ? value1.W : value2.W;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÇØ´ç º¤ÅÍ°¡ ÃÖ¼Ò°ªº¸´Ù ÀÛÀ» °æ¿ì ÃÖ¼Ò°ª, ¹Ý´ëÀÇ °æ¿ì ÃÖ´ë°ª
///@param value1 : º¤ÅÍ
///@param min : ÃÖ¼Ò°ª º¤ÅÍ
///@param max : ÃÖ´ë°ª º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Clamp( Vector4 value1, Vector4 min, Vector4 max )
{
	float num1 = value1.X;
	float num2 = (double)num1 > (double)max.X ? max.X : num1;
	float num3 = (double)num2 < (double)min.X ? min.X : num2;

	float num4 = value1.Y;
	float num5 = (double)num4 > (double)max.Y ? max.Y : num4;
	float num6 = (double)num5 < (double)min.Y ? min.Y : num5;

	float num7 = value1.Z;
	float num8 = (double)num7 > (double)max.Z ? max.Z : num7;
	float num9 = (double)num8 < (double)min.Z ? min.Z : num8;

	float num10 = value1.W;
	float num11 = (double)num10 > (double)max.W ? max.W : num10;
	float num12 = (double)num11 < (double)min.W ? min.W : num11;

	Vector4 vector4;
	vector4.X = num3;
	vector4.Y = num6;
	vector4.Z = num9;
	vector4.W = num12;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍÀÇ ¼±Çüº¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Lerp( Vector4 value1, Vector4 value2, float amount )
{
	Vector4 vector4;
	vector4.X = value1.X + (value2.X - value1.X) * amount;
	vector4.Y = value1.Y + (value2.Y - value1.Y) * amount;
	vector4.Z = value1.Z + (value2.Z - value1.Z) * amount;
	vector4.W = value1.W + (value2.W - value1.W) * amount;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ¸¦ ºÎµå·´°Ô º¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::SmoothStep( Vector4 value1, Vector4 value2, float amount )
{
	amount = (double)amount > 1.0 ? 1.0f : ((double)amount < 0.0 ? 0.0f : amount);
	amount = (float)((double)amount * (double)amount * (3.0 - 2.0 * (double)amount));

	Vector4 vector4;
	vector4.X = value1.X + (value2.X - value1.X) * amount;
	vector4.Y = value1.Y + (value2.Y - value1.Y) * amount;
	vector4.Z = value1.Z + (value2.Z - value1.Z) * amount;
	vector4.W = value1.W + (value2.W - value1.W) * amount;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Ä«Æ®¹Ä-·Ò º¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param value3 : º¤ÅÍ3
///@param value4 : º¤ÅÍ4
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::CatmullRom( Vector4 value1, Vector4 value2, Vector4 value3, Vector4 value4, float amount )
{
	float num1 = amount * amount;
	float num2 = amount * num1;

	Vector4 vector4;
	vector4.X = (float)(0.5 * (2.0 * (double)value2.X + (-(double)value1.X + (double)value3.X)* (double)amount + (2.0 * (double)value1.X - 5.0 * (double)value2.X + 4.0 * (double)value3.X - (double)value4.X)* (double)num1 + (-(double)value1.X + 3.0 * (double)value2.X - 3.0 * (double)value3.X + (double)value4.X)* (double)num2));
	vector4.Y = (float)(0.5 * (2.0 * (double)value2.Y + (-(double)value1.Y + (double)value3.Y)* (double)amount + (2.0 * (double)value1.Y - 5.0 * (double)value2.Y + 4.0 * (double)value3.Y - (double)value4.Y)* (double)num1 + (-(double)value1.Y + 3.0 * (double)value2.Y - 3.0 * (double)value3.Y + (double)value4.Y)* (double)num2));
	vector4.Z = (float)(0.5 * (2.0 * (double)value2.Z + (-(double)value1.Z + (double)value3.Z)* (double)amount + (2.0 * (double)value1.Z - 5.0 * (double)value2.Z + 4.0 * (double)value3.Z - (double)value4.Z)* (double)num1 + (-(double)value1.Z + 3.0 * (double)value2.Z - 3.0 * (double)value3.Z + (double)value4.Z)* (double)num2));
	vector4.W = (float)(0.5 * (2.0 * (double)value2.W + (-(double)value1.W + (double)value3.W)* (double)amount + (2.0 * (double)value1.W - 5.0 * (double)value2.W + 4.0 * (double)value3.W - (double)value4.W)* (double)num1 + (-(double)value1.W + 3.0 * (double)value2.W - 3.0 * (double)value3.W + (double)value4.W)* (double)num2));

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¿¡¸£¹ÌÆ® º¸°£
///@param value1 : º¤ÅÍ1
///@param tagent1 : º¤ÅÍ1ÀÇ ÅºÁ¨Æ® º¤ÅÍ
///@param value2 : º¤ÅÍ2
///@param tagent2 : º¤ÅÍ2 ÅºÁ¨Æ® º¤ÅÍ
///@param amount : º¸°£°ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Hermite( Vector4 value1, Vector4 tangent1, Vector4 value2, Vector4 tangent2, float amount )
{
	float num1 = amount * amount;
	float num2 = amount * num1;
	float num3 = (float)(2.0 * (double)num2 - 3.0 * (double)num1 + 1.0);
	float num4 = (float)(-2.0 * (double)num2 + 3.0 * (double)num1);
	float num5 = num2 - 2.0f * num1 + amount;
	float num6 = num2 - num1;

	Vector4 vector4;
	vector4.X = (float)((double)value1.X * (double)num3 + (double)value2.X * (double)num4 + (double)tangent1.X * (double)num5 + (double)tangent2.X * (double)num6);
	vector4.Y = (float)((double)value1.Y * (double)num3 + (double)value2.Y * (double)num4 + (double)tangent1.Y * (double)num5 + (double)tangent2.Y * (double)num6);
	vector4.Z = (float)((double)value1.Z * (double)num3 + (double)value2.Z * (double)num4 + (double)tangent1.Z * (double)num5 + (double)tangent2.Z * (double)num6);
	vector4.W = (float)((double)value1.W * (double)num3 + (double)value2.W * (double)num4 + (double)tangent1.W * (double)num5 + (double)tangent2.W * (double)num6);

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ 2Dº¤ÅÍ º¯È¯
///@param position : º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector2 position, Matrix matrix )
{
	float num1 = (float)((double)position.X * (double)matrix.M11 + (double)position.Y * (double)matrix.M21) + matrix.M41;
	float num2 = (float)((double)position.X * (double)matrix.M12 + (double)position.Y * (double)matrix.M22) + matrix.M42;
	float num3 = (float)((double)position.X * (double)matrix.M13 + (double)position.Y * (double)matrix.M23) + matrix.M43;
	float num4 = (float)((double)position.X * (double)matrix.M14 + (double)position.Y * (double)matrix.M24) + matrix.M44;

	Vector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ 3Dº¤ÅÍ º¯È¯
///@param position : º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector3 position, Matrix matrix )
{
	float num1 = (float)((double)position.X * (double)matrix.M11 + (double)position.Y * (double)matrix.M21 + (double)position.Z * (double)matrix.M31) + matrix.M41;
	float num2 = (float)((double)position.X * (double)matrix.M12 + (double)position.Y * (double)matrix.M22 + (double)position.Z * (double)matrix.M32) + matrix.M42;
	float num3 = (float)((double)position.X * (double)matrix.M13 + (double)position.Y * (double)matrix.M23 + (double)position.Z * (double)matrix.M33) + matrix.M43;
	float num4 = (float)((double)position.X * (double)matrix.M14 + (double)position.Y * (double)matrix.M24 + (double)position.Z * (double)matrix.M34) + matrix.M44;

	Vector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ 4Dº¤ÅÍ º¯È¯
///@param position : º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector4 vector, Matrix matrix )
{
	float num1 = (float)((double)vector.X * (double)matrix.M11 + (double)vector.Y * (double)matrix.M21 + (double)vector.Z * (double)matrix.M31 + (double)vector.W * (double)matrix.M41);
	float num2 = (float)((double)vector.X * (double)matrix.M12 + (double)vector.Y * (double)matrix.M22 + (double)vector.Z * (double)matrix.M32 + (double)vector.W * (double)matrix.M42);
	float num3 = (float)((double)vector.X * (double)matrix.M13 + (double)vector.Y * (double)matrix.M23 + (double)vector.Z * (double)matrix.M33 + (double)vector.W * (double)matrix.M43);
	float num4 = (float)((double)vector.X * (double)matrix.M14 + (double)vector.Y * (double)matrix.M24 + (double)vector.Z * (double)matrix.M34 + (double)vector.W * (double)matrix.M44);
	
	Vector4 vector4;
	vector4.X = num1;
	vector4.Y = num2;
	vector4.Z = num3;
	vector4.W = num4;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÄõÅÍ´Ï¿Â¿¡ ÀÇÇÑ 2Dº¤ÅÍ º¯È¯
///@param value : º¤ÅÍ
///@param rotation : ÄõÅÍ´Ï¿Â
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector2 value, Quaternion rotation )
{
	float num1 = rotation.X + rotation.X;
	float num2 = rotation.Y + rotation.Y;
	float num3 = rotation.Z + rotation.Z;

	float num4 = rotation.W * num1;
	float num5 = rotation.W * num2;
	float num6 = rotation.W * num3;
	float num7 = rotation.X * num1;
	float num8 = rotation.X * num2;
	float num9 = rotation.X * num3;

	float num10 = rotation.Y * num2;
	float num11 = rotation.Y * num3;
	float num12 = rotation.Z * num3;

	float num13 = (float)((double)value.X * (1.0 - (double)num10 - (double)num12)+ (double)value.Y * ((double)num8 - (double)num6));
	float num14 = (float)((double)value.X * ((double)num8 + (double)num6) + (double)value.Y * (1.0 - (double)num7 - (double)num12));
	float num15 = (float)((double)value.X * ((double)num9 - (double)num5) + (double)value.Y * ((double)num11 + (double)num4));
	
	Vector4 vector4;
	vector4.X = num13;
	vector4.Y = num14;
	vector4.Z = num15;
	vector4.W = 1.0f;
	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÄõÅÍ´Ï¿Â¿¡ ÀÇÇÑ 3Dº¤ÅÍ º¯È¯
///@param value : º¤ÅÍ
///@param rotation : ÄõÅÍ´Ï¿Â
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector3 value, Quaternion rotation )
{
	float num1 = rotation.X + rotation.X;
	float num2 = rotation.Y + rotation.Y;
	float num3 = rotation.Z + rotation.Z;

	float num4 = rotation.W * num1;
	float num5 = rotation.W * num2;
	float num6 = rotation.W * num3;
	float num7 = rotation.X * num1;
	float num8 = rotation.X * num2;
	float num9 = rotation.X * num3;

	float num10 = rotation.Y * num2;
	float num11 = rotation.Y * num3;
	float num12 = rotation.Z * num3;

	float num13 = (float)((double)value.X * (1.0 - (double)num10 - (double)num12)+ (double)value.Y * ((double)num8 - (double)num6)+ (double)value.Z * ((double)num9 + (double)num5));
	float num14 = (float)((double)value.X * ((double)num8 + (double)num6)+ (double)value.Y * (1.0 - (double)num7 - (double)num12)+ (double)value.Z * ((double)num11 - (double)num4));
	float num15 = (float)((double)value.X * ((double)num9 - (double)num5)+ (double)value.Y * ((double)num11 + (double)num4)+ (double)value.Z * (1.0 - (double)num7 - (double)num10));

	Vector4 vector4;
	vector4.X = num13;
	vector4.Y = num14;
	vector4.Z = num15;
	vector4.W = 1.0f;

	return vector4;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÄõÅÍ´Ï¿Â¿¡ ÀÇÇÑ 4Dº¤ÅÍ º¯È¯
///@param value : º¤ÅÍ
///@param rotation : ÄõÅÍ´Ï¿Â
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector4 Vector4::Transform( Vector4 value, Quaternion rotation )
{
	float num1 = rotation.X + rotation.X;
	float num2 = rotation.Y + rotation.Y;
	float num3 = rotation.Z + rotation.Z;

	float num4 = rotation.W * num1;
	float num5 = rotation.W * num2;
	float num6 = rotation.W * num3;
	float num7 = rotation.X * num1;
	float num8 = rotation.X * num2;
	float num9 = rotation.X * num3;

	float num10 = rotation.Y * num2;
	float num11 = rotation.Y * num3;
	float num12 = rotation.Z * num3;

	float num13 = (float)((double)value.X * (1.0 - (double)num10 - (double)num12)+ (double)value.Y * ((double)num8 - (double)num6)+ (double)value.Z * ((double)num9 + (double)num5));
	float num14 = (float)((double)value.X * ((double)num8 + (double)num6)+ (double)value.Y * (1.0 - (double)num7 - (double)num12)+ (double)value.Z * ((double)num11 - (double)num4));
	float num15 = (float)((double)value.X * ((double)num9 - (double)num5)+ (double)value.Y * ((double)num11 + (double)num4)+ (double)value.Z * (1.0 - (double)num7 - (double)num10));

	Vector4 vector4;
	vector4.X = num13;
	vector4.Y = num14;
	vector4.Z = num15;
	vector4.W = value.W;
	
	return vector4;
}