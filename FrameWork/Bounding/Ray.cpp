#include "Ray.h"

#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "BoundingSphere.h"

#include "../Core/Plane.h"
#include "../Core/MathHelper.h"

//////////////////////////////////////////////////////////////////////////
///@brief 생성자
//////////////////////////////////////////////////////////////////////////
Ray::Ray( void )
{
	this->Position = Vector3::Zero;
	this->Direction = Vector3::Zero;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param Position : 위치
///@param Direction : 방향
//////////////////////////////////////////////////////////////////////////
Ray::Ray( Vector3 position, Vector3 direction )
{
	this->Position = position;
	this->Direction = direction;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : 레이
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Ray::operator==( const Ray& value ) const
{
	if((double)Position.X == (double)value.Position.X && (double)Position.Y == (double)value.Position.Y && ((double)Position.Z == (double)value.Position.Z && (double)Direction.X == (double)value.Direction.X)&& (double)Direction.Y == (double)value.Direction.Y)
		return (double)Direction.Z == (double)value.Direction.Z;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value : 레이
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Ray::operator!=( const Ray& value ) const
{
	if((double)Position.X == (double)value.Position.X && (double)Position.Y == (double)value.Position.Y && ((double)Position.Z == (double)value.Position.Z && (double)Direction.X == (double)value.Direction.X)&& (double)Direction.Y == (double)value.Direction.Y)
		return (double)Direction.Z != (double)value.Direction.Z;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 문자열로 변환
///@param 문자열
//////////////////////////////////////////////////////////////////////////
std::string Ray::ToString()
{
	std::string temp;

	temp += "{{Position:" + Position.ToString() + "}, ";
	temp += "{Direction:" + Direction.ToString() + "}}";

	return temp;
}

//////////////////////////////////////////////////////////////////////////
bool Ray::Intersects(Plane & plane, float& value)
{
	float x = plane.Normal.X * this->Direction.X + plane.Normal.Y * this->Direction.Y + plane.Normal.Z * this->Direction.Z;
	if (MathHelper::Abs(x) < 1E-05f)
	{
		value = 0.0f;
		return false;
	}
	float single = plane.Normal.X * this->Position.X + plane.Normal.Y * this->Position.Y + plane.Normal.Z * this->Position.Z;
	float d = (-plane.D - single) / x;
	if (d < 0.0f)
	{
		if (d < -1E-05f)
		{
			value = 0.0f;
			return false;
		}
		d = 0.0f;
	}
	value = d;
	return true;
}

//////////////////////////////////////////////////////////////////////////
bool Ray::Intersects(BoundingSphere& sphere, float & value)
{
	float x = sphere.Center.X - this->Position.X;
	float y = sphere.Center.Y - this->Position.Y;
	float z = sphere.Center.Z - this->Position.Z;
	float single = x * x + y * y + z * z;
	float radius = sphere.Radius * sphere.Radius;
	if (single <= radius)
	{
		value = 0;
		return true;
	}
	float x1 = x * this->Direction.X + y * this->Direction.Y + z * this->Direction.Z;
	if (x1 < 0.0f)
	{
		value = 0;
		return false;
	}
	float single1 = single - x1 * x1;
	if (single1 > radius)
	{
		value = 0;
		return false;
	}
	float single2 = (float)sqrt((double)(radius - single1));
	value = x1 - single2;
	return true;
}
//////////////////////////////////////////////////////////////////////////