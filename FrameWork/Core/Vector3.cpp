#include "Vector3.h"

#include <d3dx9math.h>
#include "Matrix.h"
#include "Quaternion.h"

//////////////////////////////////////////////////////////////////////////

const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);

const Vector3 Vector3::UnitX = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ = Vector3(0.0f, 0.0f, 1.0f);

const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Backward = Vector3(0.0f, 0.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
//////////////////////////////////////////////////////////////////////////
Vector3::Vector3( void )
{
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param X = Y = Z = value
//////////////////////////////////////////////////////////////////////////
Vector3::Vector3( float value )
{
	this->X = this->Y = this->Z = value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief »ý¼ºÀÚ
///@param x : X
///@param y : Y
///@param z : Z
//////////////////////////////////////////////////////////////////////////
Vector3::Vector3( float x, float y, float z )
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator-( void )
{
	Vector3 vector3;
	vector3.X = -this->X;
	vector3.Y = -this->Y;
	vector3.Z = -this->Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool Vector3::operator==( const Vector3& value2 ) const
{
	if ((double)this->X == (double)value2.X && (double)this->Y == (double)value2.Y)
		return (double)this->Z == (double)value2.Z;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value2 : º¤ÅÍ
///@return °á°ú
//////////////////////////////////////////////////////////////////////////
bool Vector3::operator!=( const Vector3& value2 ) const
{
	if ((double)this->X == (double)value2.X && (double)this->Y == (double)value2.Y)
		return (double)this->Z != (double)value2.Z;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator+( const Vector3& value2 ) const
{
	Vector3 vector3;
	vector3.X = this->X + value2.X;
	vector3.Y = this->Y + value2.Y;
	vector3.Z = this->Z + value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator-( const Vector3& value2 ) const
{
	Vector3 vector3;
	vector3.X = this->X - value2.X;
	vector3.Y = this->Y - value2.Y;
	vector3.Z = this->Z - value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator*( const Vector3& value2 ) const
{
	Vector3 vector3;
	vector3.X = this->X * value2.X;
	vector3.Y = this->Y * value2.Y;
	vector3.Z = this->Z * value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator*( const float& scaleFactor ) const
{
	Vector3 vector3;
	vector3.X = this->X * scaleFactor;
	vector3.Y = this->Y * scaleFactor;
	vector3.Z = this->Z * scaleFactor;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator/( const Vector3& value2 ) const
{
	Vector3 vector3;
	vector3.X = this->X / value2.X;
	vector3.Y = this->Y / value2.Y;
	vector3.Z = this->Z / value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::operator/( const float& divider ) const
{
	float num = 1.0f / divider;

	Vector3 vector3;
	vector3.X = this->X * num;
	vector3.Y = this->Y * num;
	vector3.Z = this->Z * num;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator+=( const Vector3& value2 )
{
	*this = *this + value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator-=( const Vector3& value2 )
{
	*this = *this - value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param value2 : º¤ÅÍ 
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator*=( const Vector3& value2 )
{
	*this = *this * value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param scaleFactor : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator*=( const float& scaleFactor )
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param value2 : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator/=( const Vector3& value2 )
{
	*this = *this / value2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param divider : °ª
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
void Vector3::operator/=( const float& divider )
{
	*this = *this / divider;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¹®ÀÚ¿­·Î º¯È¯
///@return ¹®ÀÚ¿­
//////////////////////////////////////////////////////////////////////////
std::string Vector3::ToString()
{
	std::string temp;
	char val[255];

	sprintf(val, "{X:%#f ", X); temp += val; 
	sprintf(val, "Y:%#f ", Y); temp += val;
	sprintf(val, "Z:%#f}", Z); temp += val;

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief D3DXVECTOR3·Î º¯È¯
///@return D3DX º¤ÅÍ 
//////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Vector3::ToD3DXVECTOR3()
{
	D3DXVECTOR3 vector3;
	vector3.x = X;
	vector3.y = Y;
	vector3.z = Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector3::Length()
{
	return (float)sqrt((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î Å©±â °è»ê
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector3::LengthSquared()
{
	return (float)((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
//////////////////////////////////////////////////////////////////////////
void Vector3::Normalize()
{
	float num = 1.0f / (float)sqrt((double)this->X * (double)this->X + (double)this->Y * (double)this->Y + (double)this->Z * (double)this->Z);

	this->X *= num;
	this->Y *= num;
	this->Z *= num;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector3::Distance( Vector3 value1, Vector3 value2 )
{
	float num1 = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;

	return (float)sqrt((double)num1 * (double)num1 + (double)num2 * (double)num2 + (double)num3 * (double)num3);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¦°öÀ¸·Î °Å¸®°è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector3::DistanceSquared( Vector3 value1, Vector3 value2 )
{
	float num1 = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;

	return (float)((double)num1 * (double)num1 + (double)num2 * (double)num2 + (double)num3 * (double)num3);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ³»Àû °è»ê
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú °ª
//////////////////////////////////////////////////////////////////////////
float Vector3::Dot( Vector3 value1, Vector3 value2 )
{
	return (float)((double)value1.X * (double)value2.X + (double)value1.Y * (double)value2.Y + (double)value1.Z * (double)value2.Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Á¤±ÔÈ­
///@param value : º¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Normalize( Vector3 value )
{
	float num = 1.0f / (float)sqrt((double)value.X * (double)value.X + (double)value.Y * (double)value.Y + (double)value.Z * (double)value.Z);

	Vector3 vector3;
	vector3.X = value.X * num;
	vector3.Y = value.Y * num;
	vector3.Z = value.Z * num;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¿ÜÀû °è»ê
///@param vector1 : º¤ÅÍ1
///@param vector2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Cross( Vector3 vector1, Vector3 vector2 )
{
	Vector3 vector3;
	vector3.X = (float)((double)vector1.Y * (double)vector2.Z - (double)vector1.Z * (double)vector2.Y);
	vector3.Y = (float)((double)vector1.Z * (double)vector2.X - (double)vector1.X * (double)vector2.Z);
	vector3.Z = (float)((double)vector1.X * (double)vector2.Y - (double)vector1.Y * (double)vector2.X);

	return vector3;	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¹Ý»ç°ª
///@param vector : º¤ÅÍ
///@param normal : ³ë¸Öº¤ÅÍ
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Reflect( Vector3 vector, Vector3 normal )
{
	float num = (float)((double)vector.X * (double)normal.X + (double)vector.Y * (double)normal.Y + (double)vector.Z * (double)normal.Z);

	Vector3 vector3;
	vector3.X = vector.X - 2.0f * num * normal.X;
	vector3.Y = vector.Y - 2.0f * num * normal.Y;
	vector3.Z = vector.Z - 2.0f * num * normal.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß ÀÛÀº º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Min( Vector3 value1, Vector3 value2 )
{
	Vector3 vector3;
	vector3.X = (double)value1.X < (double)value2.X ? value1.X : value2.X;
	vector3.Y = (double)value1.Y < (double)value2.Y ? value1.Y : value2.Y;
	vector3.Z = (double)value1.Z < (double)value2.Z ? value1.Z : value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ Áß Å« º¤ÅÍ
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Max( Vector3 value1, Vector3 value2 )
{
	Vector3 vector3;
	vector3.X = (double)value1.X > (double)value2.X ? value1.X : value2.X;
	vector3.Y = (double)value1.Y > (double)value2.Y ? value1.Y : value2.Y;
	vector3.Z = (double)value1.Z > (double)value2.Z ? value1.Z : value2.Z;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÇØ´ç º¤ÅÍ°¡ ÃÖ¼Ò°ªº¸´Ù ÀÛÀ» °æ¿ì ÃÖ¼Ò°ª, ¹Ý´ëÀÇ °æ¿ì ÃÖ´ë°ª
///@param value1 : º¤ÅÍ
///@param min : ÃÖ¼Ò°ª º¤ÅÍ
///@param max : ÃÖ´ë°ª º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Clamp( Vector3 value1, Vector3 min, Vector3 max )
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

	Vector3 vector3;
	vector3.X = num3;
	vector3.Y = num6;
	vector3.Z = num9;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍÀÇ ¼±Çüº¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Lerp( Vector3 value1, Vector3 value2, float amount )
{
	Vector3 vector3;
	vector3.X = value1.X + (value2.X - value1.X) * amount;
	vector3.Y = value1.Y + (value2.Y - value1.Y) * amount;
	vector3.Z = value1.Z + (value2.Z - value1.Z) * amount;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief µÎ º¤ÅÍ¸¦ ºÎµå·´°Ô º¸°£
///@param value1 : º¤ÅÍ1
///@param value2 : º¤ÅÍ2
///@param amount : º¸°£°ª
///@return °á°úº¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::SmoothStep( Vector3 value1, Vector3 value2, float amount )
{
	amount = (double)amount > 1.0 ? 1.0f : ((double)amount < 0.0 ? 0.0f : amount);
	amount = (float)((double)amount * (double)amount * (3.0 - 2.0 * (double)amount));

	Vector3 vector3;
	vector3.X = value1.X + (value2.X - value1.X)* amount;
	vector3.Y = value1.Y + (value2.Y - value1.Y)* amount;
	vector3.Z = value1.Z + (value2.Z - value1.Z)* amount;

	return vector3;
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
Vector3 Vector3::CatmullRom( Vector3 value1, Vector3 value2, Vector3 value3, Vector3 value4, float amount )
{
	float num1 = amount * amount;
	float num2 = amount * num1;

	Vector3 vector3;
	vector3.X = (float)(0.5 * (2.0 * (double)value2.X + (-(double)value1.X + (double)value3.X)* (double)amount + (2.0 * (double)value1.X - 5.0 * (double)value2.X + 4.0 * (double)value3.X - (double)value4.X)* (double)num1 + (-(double)value1.X + 3.0 * (double)value2.X - 3.0 * (double)value3.X + (double)value4.X)* (double)num2));
	vector3.Y = (float)(0.5 * (2.0 * (double)value2.Y + (-(double)value1.Y + (double)value3.Y)* (double)amount + (2.0 * (double)value1.Y - 5.0 * (double)value2.Y + 4.0 * (double)value3.Y - (double)value4.Y)* (double)num1 + (-(double)value1.Y + 3.0 * (double)value2.Y - 3.0 * (double)value3.Y + (double)value4.Y)* (double)num2));
	vector3.Z = (float)(0.5 * (2.0 * (double)value2.Z + (-(double)value1.Z + (double)value3.Z)* (double)amount + (2.0 * (double)value1.Z - 5.0 * (double)value2.Z + 4.0 * (double)value3.Z - (double)value4.Z)* (double)num1 + (-(double)value1.Z + 3.0 * (double)value2.Z - 3.0 * (double)value3.Z + (double)value4.Z)* (double)num2));

	return vector3;
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
Vector3 Vector3::Hermite( Vector3 value1, Vector3 tangent1, Vector3 value2, Vector3 tangent2, float amount )
{
	float num1 = amount * amount;
	float num2 = amount * num1;
	float num3 = (float)(2.0 * (double)num2 - 3.0 * (double)num1 + 1.0);
	float num4 = (float)(-2.0 * (double)num2 + 3.0 * (double)num1);
	float num5 = num2 - 2.0f * num1 + amount;
	float num6 = num2 - num1;

	Vector3 vector3;
	vector3.X = (float)((double)value1.X * (double)num3 + (double)value2.X * (double)num4 + (double)tangent1.X * (double)num5 + (double)tangent2.X * (double)num6);
	vector3.Y = (float)((double)value1.Y * (double)num3 + (double)value2.Y * (double)num4 + (double)tangent1.Y * (double)num5 + (double)tangent2.Y * (double)num6);
	vector3.Z = (float)((double)value1.Z * (double)num3 + (double)value2.Z * (double)num4 + (double)tangent1.Z * (double)num5 + (double)tangent2.Z * (double)num6);

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ º¤ÅÍ º¯È¯
///@param position : º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Transform( Vector3 position, Matrix matrix )
{
	float num1 = (float)((double)position.X * (double)matrix.M11 + (double)position.Y * (double)matrix.M21 + (double)position.Z * (double)matrix.M31)+ matrix.M41;
	float num2 = (float)((double)position.X * (double)matrix.M12 + (double)position.Y * (double)matrix.M22 + (double)position.Z * (double)matrix.M32)+ matrix.M42;
	float num3 = (float)((double)position.X * (double)matrix.M13 + (double)position.Y * (double)matrix.M23 + (double)position.Z * (double)matrix.M33)+ matrix.M43;

	Vector3 vector3;
	vector3.X = num1;
	vector3.Y = num2;
	vector3.Z = num3;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ÄõÅÍ´Ï¿Â¿¡ ÀÇÇÑ º¤ÅÍ º¯È¯
///@param value : º¤ÅÍ
///@param rotation : ÄõÅÍ´Ï¿Â
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::Transform( Vector3 value, Quaternion rotation )
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
	float num14 = (float)((double)value.X * ((double)num8 + (double)num6) + (double)value.Y * (1.0 - (double)num7 - (double)num12)+ (double)value.Z * ((double)num11 - (double)num4));
	float num15 = (float)((double)value.X * ((double)num9 - (double)num5) + (double)value.Y * ((double)num11 + (double)num4)+ (double)value.Z * (1.0 - (double)num7 - (double)num10));

	Vector3 vector3;
	vector3.X = num13;
	vector3.Y = num14;
	vector3.Z = num15;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ ³ë¸Öº¤ÅÍ º¯È¯
///@param normal : ¹ý¼± º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::TransformNormal( Vector3 normal, Matrix matrix )
{
	float num1 = (float)((double)normal.X * (double)matrix.M11 + (double)normal.Y * (double)matrix.M21 + (double)normal.Z * (double)matrix.M31);
	float num2 = (float)((double)normal.X * (double)matrix.M12 + (double)normal.Y * (double)matrix.M22 + (double)normal.Z * (double)matrix.M32);
	float num3 = (float)((double)normal.X * (double)matrix.M13 + (double)normal.Y * (double)matrix.M23 + (double)normal.Z * (double)matrix.M33);

	Vector3 vector3;
	vector3.X = num1;
	vector3.Y = num2;
	vector3.Z = num3;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ¸ÅÆ®¸¯½º¿¡ ÀÇÇÑ À§Ä¡(Á¤Á¡)º¤ÅÍ º¯È¯
///@param position : À§Ä¡ º¤ÅÍ
///@param matrix : ¸ÅÆ®¸¯½º
///@return °á°ú º¤ÅÍ
//////////////////////////////////////////////////////////////////////////
Vector3 Vector3::TransformCoord( Vector3 position, Matrix matrix )
{
	float num1 = (matrix.M11 * position.X) + (matrix.M21 * position.Y) + (matrix.M31 * position.Z) + matrix.M41;
	float num2 = (matrix.M12 * position.X) + (matrix.M22 * position.Y) + (matrix.M32 * position.Z) + matrix.M42;
	float num3 = (matrix.M13 * position.X) + (matrix.M23 * position.Y) + (matrix.M33 * position.Z) + matrix.M43;
	float num4 = (matrix.M14 * position.X) + (matrix.M24 * position.Y) + (matrix.M34 * position.Z) + matrix.M44;

	return Vector3((num1 / num4), (num2 / num4), (num3 / num4));
}