#include "BoundingBox.h"

#include <assert.h>
#include "Bounding.h"
#include "BoundingSphere.h"
#include "BoundingFrustum.h"
#include "Ray.h"

#include "../Core/Plane.h"
#include "../Core/MathHelper.h"

//////////////////////////////////////////////////////////////////////////

const int BoundingBox::CornerCount = 8;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
BoundingBox::BoundingBox( void )
{
	this->Min = Vector3::Zero;
	this->Max = Vector3::Zero;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param min : �ּ� ��ġ����
///@param max : �ִ� ��ġ����
//////////////////////////////////////////////////////////////////////////
BoundingBox::BoundingBox( Vector3 min, Vector3 max )
{
	this->Min = min;
	this->Max = max;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : �ٿ�� �ڽ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::operator==( const BoundingBox& value ) const
{
	if(this->Min == value.Min)
		return this->Max == value.Max;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value : �ٿ�� �ڽ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::operator!=( const BoundingBox& value ) const
{
	if(!(this->Min != value.Min))
		return this->Max != value.Max;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ڳ� ��ġ
///@param pCorner : Vector[8]
//////////////////////////////////////////////////////////////////////////
void BoundingBox::GetCorners( Vector3* pCorner )
{
	assert(pCorner != NULL);

	pCorner[0] = Vector3(Min.X, Max.Y, Max.Z);
	pCorner[1] = Vector3(Max.X, Max.Y, Max.Z);
	pCorner[2] = Vector3(Max.X, Min.Y, Max.Z);
	pCorner[3] = Vector3(Min.X, Min.Y, Max.Z);
	pCorner[4] = Vector3(Min.X, Max.Y, Min.Z);
	pCorner[5] = Vector3(Max.X, Max.Y, Min.Z);
	pCorner[6] = Vector3(Max.X, Min.Y, Min.Z);
	pCorner[7] = Vector3(Min.X, Min.Y, Min.Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ��� ��ȯ
///@param ���ڿ�
//////////////////////////////////////////////////////////////////////////
std::string BoundingBox::ToString()
{
	std::string temp;
	char val[255];

	sprintf(val, "{ Min:{X:%#f ", Min.X); temp += val; 
	sprintf(val, "Y:%#f ", Min.Y); temp += val;
	sprintf(val, "Z:%#f}, ", Min.Z); temp += val;

	sprintf(val, "Max:{X:%#f ", Max.X); temp += val; 
	sprintf(val, "Y:%#f ", Max.Y); temp += val;
	sprintf(val, "Z:%#f}}, ", Max.Z); temp += val;

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@param v : ����
///@return ���
//////////////////////////////////////////////////////////////////////////
Vector3 BoundingBox::SupportMapping( Vector3 v )
{
	Vector3 result;
	result.X = (double)v.X >= 0.0 ? Max.X : Min.X;
	result.Y = (double)v.Y >= 0.0 ? Max.Y : Min.Y;
	result.Z = (double)v.Z >= 0.0 ? Max.Z : Min.Z;

	return result;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ� 2���� ��ģ��
///@param original : �ٿ�� �ڽ�1
///@param additional : �ٿ�� �ڽ�2
///@return ��� �ٿ���ڽ�
//////////////////////////////////////////////////////////////////////////
BoundingBox BoundingBox::CreateMerged( BoundingBox original, BoundingBox additional )
{
	BoundingBox boundingBox;
	boundingBox.Min = Vector3::Min(original.Min, additional.Min);
	boundingBox.Max = Vector3::Max(original.Max, additional.Max);

	return boundingBox;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �����κ��� �ٿ�� �ڽ� ����
///@param sphere : �ٿ�� �����
///@return ��� �ٿ���ڽ�
//////////////////////////////////////////////////////////////////////////
BoundingBox BoundingBox::CreateFromSphere( BoundingSphere sphere )
{
	BoundingBox boundingBox;
	boundingBox.Min.X = sphere.Center.X - sphere.Radius;
	boundingBox.Min.Y = sphere.Center.Y - sphere.Radius;
	boundingBox.Min.Z = sphere.Center.Z - sphere.Radius;
	boundingBox.Max.X = sphere.Center.X + sphere.Radius;
	boundingBox.Max.Y = sphere.Center.Y + sphere.Radius;
	boundingBox.Max.Z = sphere.Center.Z + sphere.Radius;

	return boundingBox;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ��� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::Intersects( BoundingBox box )
{
	if ((double)Max.X < (double)box.Min.X || (double)Min.X > (double)box.Max.X || ((double)Max.Y < (double)box.Min.Y || (double)Min.Y > (double)box.Max.Y)|| ((double)Max.Z < (double)box.Min.Z || (double)Min.Z > (double)box.Max.Z))
		return false;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������Ұ� ���� �˻�
///@param frustum : �ٿ�� ��������
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::Intersects( BoundingFrustum frustum )
{	
	return frustum.Intersects(*this);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������ ���� �˻�
///@param plane : ���
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
PlaneIntersectionType BoundingBox::Intersects( Plane plane )
{
	Vector3 vector3_1;
	vector3_1.X = (double)plane.Normal.X >= 0.0 ? Min.X : Max.X;
	vector3_1.Y = (double)plane.Normal.Y >= 0.0 ? Min.Y : Max.Y;
	vector3_1.Z = (double)plane.Normal.Z >= 0.0 ? Min.Z : Max.Z;

	Vector3 vector3_2;
	vector3_2.X = (double)plane.Normal.X >= 0.0 ? Max.X : Min.X;
	vector3_2.Y = (double)plane.Normal.Y >= 0.0 ? Max.Y : Min.Y;
	vector3_2.Z = (double)plane.Normal.Z >= 0.0 ? Max.Z : Min.Z;

	if ((double)plane.Normal.X * (double)vector3_1.X + (double)plane.Normal.Y * (double)vector3_1.Y + (double)plane.Normal.Z * (double)vector3_1.Z + (double)plane.D > 0.0)
		return PlaneIntersectionType_Front;
	else if ((double)plane.Normal.X * (double)vector3_2.X + (double)plane.Normal.Y * (double)vector3_2.Y + (double)plane.Normal.Z * (double)vector3_2.Z + (double)plane.D < 0.0)
		return PlaneIntersectionType_Back;
	else
		return PlaneIntersectionType_Intersecting;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���̿��� ���� �˻�
///@param ray : ����
///@param result : ���
///@warning
///		������ ���� ���� ��� result�� 0.0f�� ���� �ƴϴ�!
///		result == NULL �̴�!!!!!
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::Intersects( Ray ray, float* result )
{
	if(result != NULL)
	{
		delete result;
		result = NULL;
	}

	float num1 = 0.0f;
	float num2 = MathHelper::FloatMaxValue;
	
	
	//1. ray.Direction.X
	if((double)MathHelper::Abs(ray.Direction.X) < 9.99999997475243E-07)
	{
		if((double)ray.Position.X < (double)Min.X || (double)ray.Position.X > (double)Max.X)
			return false;
	}
	else
	{
		float num3 = 1.0f / ray.Direction.X;
		float num4 = (Min.X - ray.Position.X)* num3;
		float num5 = (Max.X - ray.Position.X)* num3;

		if((double)num4 > (double)num5)
		{
			float num6 = num4;
			num4 = num5;
			num5 = num6;
		}
		
		num1 = MathHelper::Max(num4, num1);
		num2 = MathHelper::Min(num5, num2);
		
		if((double)num1 > (double)num2)
			return false;
	}
	

	//2. ray.Direction.Y
	if((double)MathHelper::Abs(ray.Direction.Y) < 9.99999997475243E-07)
	{
		if ((double)ray.Position.Y < (double)Min.Y || (double)ray.Position.Y >(double)Max.Y)
			return false;
	}
	else
	{
		float num3 = 1.0f / ray.Direction.Y;
		float num4 = (Min.Y - ray.Position.Y) * num3;
		float num5 = (Max.Y - ray.Position.Y) * num3;

		if((double)num4 > (double)num5)
		{
			float num6 = num4;
			num4 = num5;
			num5 = num6;
		}

		num1 = MathHelper::Max(num4, num1);
		num2 = MathHelper::Min(num5, num2);
		
		if((double)num1 > (double)num2)
			return false;
	}


	//3. ray.Direction.Z
	if((double)MathHelper::Abs(ray.Direction.Z) < 9.99999997475243E-07)
	{
		if((double)ray.Position.Z < (double)Min.Z || (double)ray.Position.Z > (double)Max.Z)
			return false;
	}
	else
	{
		float num3 = 1.0f / ray.Direction.Z;
		float num4 = (Min.Z - ray.Position.Z) * num3;
		float num5 = (Max.Z - ray.Position.Z) * num3;
		
		if((double)num4 > (double)num5)
		{
			float num6 = num4;
			num4 = num5;
			num5 = num6;
		}

		num1 = MathHelper::Max(num4, num1);
		float num7 = MathHelper::Min(num5, num2);
		
		if((double)num1 > (double)num7)
			return false;
	}

	result = new float(num1);
	return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ������ ���� �˻�
///@param sphere : �ٿ�� �����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingBox::Intersects( BoundingSphere sphere )
{
	Vector3 result1 = Vector3::Clamp(sphere.Center, Min, Max);
	float result2 = Vector3::DistanceSquared(sphere.Center, result1);
	
	if((double)result2 <= (double)sphere.Radius * (double)sphere.Radius)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingBox::Contains( BoundingBox box )
{
	if ((double)Max.X < (double)box.Min.X || (double)Min.X > (double)box.Max.X || ((double)Max.Y < (double)box.Min.Y || (double)Min.Y > (double)box.Max.Y) || ((double)Max.Z < (double)box.Min.Z || (double)Min.Z > (double)box.Max.Z))
		return ContainmentType_Disjoint;
	else if ((double)Min.X > (double)box.Min.X || (double)box.Max.X > (double)Max.X || ((double)Min.Y > (double)box.Min.Y || (double)box.Max.Y > (double)Max.Y)|| ((double)Min.Z > (double)box.Min.Z || (double)box.Max.Z > (double)Max.Z))
		return ContainmentType_Intersects;
	else
		return ContainmentType_Contains;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingBox::Contains( BoundingFrustum frustum )
{
	if(!frustum.Intersects(*this))
	{
		return ContainmentType_Disjoint;
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			Vector3 point = frustum.cornerArray[i];
			
			if(Contains(point) == ContainmentType_Disjoint)
				return ContainmentType_Intersects;
		}
		
		return ContainmentType_Contains;
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��ġ ���� ���� �˻�
///@param point : ��ġ ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingBox::Contains( Vector3 point )
{
	if ((double)Min.X > (double)point.X || (double)point.X > (double)Max.X || ((double)Min.Y > (double)point.Y || (double)point.Y > (double)Max.Y)|| ((double)Min.Z > (double)point.Z || (double)point.Z > (double)Max.Z))
		return ContainmentType_Disjoint;
	else
		return ContainmentType_Contains;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ����� ���� �˻�
///@param point : ��ġ ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingBox::Contains( BoundingSphere sphere )
{
	Vector3 result1 = Vector3::Clamp(sphere.Center, Min, Max);
	float result2 = Vector3::DistanceSquared(sphere.Center, result1);
	float num = sphere.Radius;
	
	if((double)result2 > (double)num * (double)num)
		return ContainmentType_Disjoint;
	else if ((double)Min.X + (double)num > (double)sphere.Center.X || (double)sphere.Center.X > (double)Max.X - (double)num || ((double)Max.X - (double)Min.X <= (double)num || (double)Min.Y + (double)num > (double)sphere.Center.Y)|| ((double)sphere.Center.Y > (double)Max.Y - (double)num || (double)Max.Y - (double)Min.Y <= (double)num || ((double)Min.Z + (double)num > (double)sphere.Center.Z || (double)sphere.Center.Z > (double)Max.Z - (double)num))|| (double)Max.X - (double)Min.X <= (double)num)
		return ContainmentType_Intersects;
	else
		return ContainmentType_Contains;
}