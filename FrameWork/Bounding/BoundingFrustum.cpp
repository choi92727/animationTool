#include "BoundingFrustum.h"

#include <assert.h>
#include "Bounding.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"

#include "../Core/MathHelper.h"

//////////////////////////////////////////////////////////////////////////

const int BoundingFrustum::CornerCount = 8;
const int BoundingFrustum::NearPlaneIndex = 0;
const int BoundingFrustum::FarPlaneIndex = 1;
const int BoundingFrustum::LeftPlaneIndex = 2;
const int BoundingFrustum::RightPlaneIndex = 3;
const int BoundingFrustum::TopPlaneIndex = 4;
const int BoundingFrustum::BottomPlaneIndex = 5;
const int BoundingFrustum::NumPlanes = 6;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
BoundingFrustum::BoundingFrustum( void )
{

}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param value : ��Ʈ����
//////////////////////////////////////////////////////////////////////////
BoundingFrustum::BoundingFrustum( Matrix value )
{
	SetMatrix(value);
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : �ٿ�� ��������
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::operator==( const BoundingFrustum& value ) const
{
	return Equals(value);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : �ٿ�� ��������
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::operator!=( const BoundingFrustum& value ) const
{
	return !Equals(value);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ��� ��ȯ
///@param ���ڿ�
//////////////////////////////////////////////////////////////////////////
std::string BoundingFrustum::ToString()
{
	std::string temp;

	temp += "{{Near:" + planes[0].ToString() + "}, ";
	temp += "{Far:" + planes[1].ToString() + "}, ";
	temp += "{Left:" + planes[2].ToString() + "}, ";
	temp += "{Right:" + planes[3].ToString() + "}, ";
	temp += "{Top:" + planes[4].ToString() + "}, ";
	temp += "{Bottom:" + planes[5].ToString() + "}}";

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@param v : ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
Vector3 BoundingFrustum::SupportMapping( Vector3 v )
{
	float result1;
	int index1 = 0;
	result1 = Vector3::Dot(cornerArray[0], v);

	for(int index2 = 1; index2 < 8; ++index2)
	{
		float result2;
		result2 = Vector3::Dot(cornerArray[index2], v);

		if((double)result2 > (double)result1)
		{
			index1 = index2;
			result1 = result2;
		}
	}

	return cornerArray[index1];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���� ���� ��ü���� �˻�
///@param value : �ٿ�� ��������
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Equals( const BoundingFrustum& value ) const
{
	bool flag = false;
	flag = matrix == value.matrix;

	return flag;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٸ�
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Near() const
{
	return planes[0];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Far() const
{
	return planes[1];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Left() const
{
	return planes[2];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Right() const
{
	return planes[3];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Top() const
{
	return planes[4];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �Ʒ���
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Bottom() const
{
	return planes[5];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ʈ����
///@return ��� ��Ʈ����
//////////////////////////////////////////////////////////////////////////
Matrix BoundingFrustum::GetMatrix() const
{
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ʈ���� ����
///@param value : ������ ��Ʈ����
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::SetMatrix( const Matrix value )
{
	matrix = value;
	planes[2].Normal.X = -value.M14 - value.M11; planes[2].Normal.Y = -value.M24 - value.M21; planes[2].Normal.Z = -value.M34 - value.M31; planes[2].D = -value.M44 - value.M41;
	planes[3].Normal.X = -value.M14 + value.M11; planes[3].Normal.Y = -value.M24 + value.M21; planes[3].Normal.Z = -value.M34 + value.M31; planes[3].D = -value.M44 + value.M41;
	planes[4].Normal.X = -value.M14 + value.M12; planes[4].Normal.Y = -value.M24 + value.M22; planes[4].Normal.Z = -value.M34 + value.M32; planes[4].D = -value.M44 + value.M42;
	planes[5].Normal.X = -value.M14 - value.M12; planes[5].Normal.Y = -value.M24 - value.M22; planes[5].Normal.Z = -value.M34 - value.M32; planes[5].D = -value.M44 - value.M42;

	planes[0].Normal.X = -value.M13;
	planes[0].Normal.Y = -value.M23;
	planes[0].Normal.Z = -value.M33;
	planes[0].D = -value.M43;

	planes[1].Normal.X = -value.M14 + value.M13;
	planes[1].Normal.Y = -value.M24 + value.M23;
	planes[1].Normal.Z = -value.M34 + value.M33;
	planes[1].D = -value.M44 + value.M43;

	for(int index = 0; index < 6; ++index)
	{
		float num = planes[index].Normal.Length();
		planes[index].Normal /= num;
		planes[index].D /= num;
	}

	Ray intersectionLine1 = ComputeIntersectionLine(planes[0], planes[2]);
	cornerArray[0] = ComputeIntersection(planes[4], intersectionLine1);
	cornerArray[3] = ComputeIntersection(planes[5], intersectionLine1);

	Ray intersectionLine2 = ComputeIntersectionLine(planes[3], planes[0]);
	cornerArray[1] = ComputeIntersection(planes[4], intersectionLine2);
	cornerArray[2] = ComputeIntersection(planes[5], intersectionLine2);

	intersectionLine2 = ComputeIntersectionLine(planes[2], planes[1]);
	cornerArray[4] = ComputeIntersection(planes[4], intersectionLine2);
	cornerArray[7] = ComputeIntersection(planes[5], intersectionLine2);

	intersectionLine2 = ComputeIntersectionLine(planes[1], planes[3]);
	cornerArray[5] = ComputeIntersection(planes[4], intersectionLine2);
	cornerArray[6] = ComputeIntersection(planes[5], intersectionLine2);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ڳ� ���
///@param pOut : 
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::GetCorner( Vector3* pCorner )
{
	assert(pCorner != NULL);

	for(int i = 0; i < 8; i++)
		pCorner[i] = cornerArray[i];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� �ΰ��� ������ ���
///@return ��� ������
//////////////////////////////////////////////////////////////////////////
Ray BoundingFrustum::ComputeIntersectionLine( Plane p1, Plane p2 )
{
	Ray ray;
	ray.Direction = Vector3::Cross(p1.Normal, p2.Normal);
	
	float num = ray.Direction.LengthSquared();
	ray.Position = Vector3::Cross(-p1.D * p2.Normal + p2.D * p1.Normal, ray.Direction) / num;
	
	return ray;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��� ������ ���� ��ġ ���
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
Vector3 BoundingFrustum::ComputeIntersection( Plane plane, Ray ray )
{
	float num = (-plane.D - Vector3::Dot(plane.Normal, ray.Position)) / Vector3::Dot(plane.Normal, ray.Direction);
	
	return ray.Position + ray.Direction * num;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ��� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Intersects( BoundingBox box )
{	
	bool result = false;
	Intersects(box, result);
	
	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ��� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@param result : ���
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::Intersects( BoundingBox box, bool& result )
{
	gjk.Reset();
	
	Vector3 result1;
	result1 = cornerArray[0] - box.Min;
	
	if((double)result1.LengthSquared() < 9.99999974737875E-06)
		result1 = cornerArray[0] - box.Max;

	float num1 = MathHelper::FloatMaxValue;
	float num2;
	result = false;

	do
	{
		Vector3 v(-result1.X, -result1.Y, -result1.Z);

		Vector3 result2 = SupportMapping(v);
		Vector3 result3 = box.SupportMapping(result1);
		Vector3 result4 = result2 - result3;
		if((double)result1.X * (double)result4.X + (double)result1.Y * (double)result4.Y + (double)result1.Z * (double)result4.Z > 0.0)
		{
			return;
		}
		else
		{
			gjk.AddSupportPoint(result4);
			result1 = gjk.ClosestPoint();
			
			float num3 = num1;
			num1 = result1.LengthSquared();

			if ((double) num3 - (double)num1 <= 9.99999974737875E-06 * (double)num3)
				return;
			else
				num2 = 4E-05f * gjk.MaxLengthSquared();
		}
	}
	while(!gjk.FullSimplex() && (double)num1 >= (double)num2);

	result = true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������Ұ� ���� �˻�
///@param frustum : �ٿ�� ��������
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Intersects( BoundingFrustum frustum )
{
	gjk.Reset();
	Vector3 result1;
	result1 = cornerArray[0] - frustum.cornerArray[0];
	
	if((double) result1.LengthSquared() < 9.99999974737875E-06)
		result1 = cornerArray[0] - frustum.cornerArray[1];

	float num1 = MathHelper::FloatMaxValue;
	float num2;
	do
	{
		Vector3 v(-result1.X, -result1.Y, -result1.Z);
		Vector3 result2 = SupportMapping(v);
		Vector3 result3 = frustum.SupportMapping(result1);
		Vector3 result4 = result2 - result3;
		
		if((double)result1.X * (double)result4.X + (double)result1.Y * (double)result4.Y + (double)result1.Z * (double)result4.Z > 0.0)
		{
			return false;
		}
		else
		{
			gjk.AddSupportPoint(result4);
			result1 = gjk.ClosestPoint();

			float num3 = num1;
			num1 = result1.LengthSquared();
			num2 = 4E-05f * gjk.MaxLengthSquared();

			if((double)num3 - (double)num1 <= 9.99999974737875E-06 * (double)num3)
				return false;
		}
	}
	while(!gjk.FullSimplex() && (double)num1 >= (double)num2);

	return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��� ���� �˻�
///@param plane : ��
///@return ���
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::Intersects( Plane plane, PlaneIntersectionType& result )
{
	int num = 0;
	for(int index = 0; index < 8; ++index)
	{
		float result = Vector3::Dot(cornerArray[index], plane.Normal);

		if((double)result + (double)plane.D > 0.0)
			num |= 1;
		else
			num |= 2;
		
		if(num == 3)
		{
			result = PlaneIntersectionType_Intersecting;
			
			return ;
		}
	}
	
	result = num == 1 ? PlaneIntersectionType_Front : PlaneIntersectionType_Back;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���̿��� �����˻�
///@param ray : ����
///@param result : ���� �����
///@warning
///		������ ���� ���� ��� result�� 0.0f�� ���� �ƴϴ�!
///		result == NULL �̴�!!!!!
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::Intersects( Ray ray, float* result )
{
	ContainmentType result1;
	result1 = Contains(ray.Position);
	if (result1 == ContainmentType_Contains)
	{
		*result = 0.0f;
	}
	else
	{
		float num1 = MathHelper::FloatMinValue;
		float num2 = MathHelper::FloatMaxValue;

		if(result != NULL)
		{
			delete result;
			result = NULL;
		}
		result = new float();
		
		for(int i = 0; i < 6; i++)
		{
			Plane plane = planes[i];

			Vector3 vector2 = plane.Normal;
			float result2 = Vector3::Dot(ray.Direction, vector2);
			float result3 = Vector3::Dot(ray.Position, vector2);
			result3 += plane.D;
			
			if((double)MathHelper::Abs(result2) < 9.99999974737875E-06)
			{
				if ((double)result3 > 0.0)
					return;
			}
			else
			{
				float num3 = -result3 / result2;

				if((double)result2 < 0.0)
				{
					if((double) num3 > (double)num2)
						return;
					else if((double)num3 > (double)num1)
						num1 = num3;
				}
				else if((double)num3 < (double)num1)
					return;
				else if((double)num3 < (double)num2)
					num2 = num3;
			}
		}
		float num4 = (double)num1 >= 0.0 ? num1 : num2;

		if ((double) num4 >= 0.0)
			*result = num4;
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ������ �����˻�
///@param sphere : �ٿ�� �����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Intersects( BoundingSphere sphere )
{
	bool result = false;
	Intersects(sphere, result);
	
	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ������ �����˻�
///@param sphere : �ٿ�� �����
///@param result : ���
//////////////////////////////////////////////////////////////////////////
void BoundingFrustum::Intersects( BoundingSphere sphere, bool& result )
{
	gjk.Reset();
	Vector3 result1 = cornerArray[0] - sphere.Center;
	if((double)result1.LengthSquared() < 9.99999974737875E-06)
		result1 = Vector3::UnitX;

	float num1 = MathHelper::FloatMaxValue; //float.MaxValue
	result = false;
	float num2;
	do
	{
		Vector3 v(-result1.X, -result1.Y, -result1.Z);
		Vector3 result2 = SupportMapping(v);
		Vector3 result3 = sphere.SupportMapping(result1);
		Vector3 result4 = result2 - result3;

		if((double)result1.X * (double)result4.X + (double)result1.Y * (double)result4.Y + (double)result1.Z * (double)result4.Z > 0.0)
		{
			return;
		}
		else
		{
			gjk.AddSupportPoint(result4);
			result1 = gjk.ClosestPoint();
			
			float num3 = num1;
			num1 = result1.LengthSquared();
			if((double)num3 - (double)num1 <= 9.99999974737875E-06 * (double)num3)
				return;
			else
				num2 = 4E-05f * gjk.MaxLengthSquared();
		}
	}
	while(!gjk.FullSimplex() && (double)num1 >= (double)num2);
	
	result = true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ��� ���� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingFrustum::Contains( BoundingBox box )
{
	bool flag = false;
	
	for(int i = 0; i < 6; i++)
	{
		Plane plane = planes[i];
		
		switch(box.Intersects(plane))
		{
			case PlaneIntersectionType_Front:
				return ContainmentType_Disjoint;

			case PlaneIntersectionType_Intersecting:
				flag = true;
				break;
		}
	}
	
	if(!flag)
		return ContainmentType_Contains;
	else
		return ContainmentType_Intersects;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ���������� ���Կ��� �˻�
///@param frustum : �ٿ�� ��������
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingFrustum::Contains( BoundingFrustum frustum )
{
	ContainmentType containmentType = ContainmentType_Disjoint;

	if(Intersects(frustum))
	{
		containmentType = ContainmentType_Contains;

		for(int index = 0; index < 8; ++index)
		{
			if(Contains(frustum.cornerArray[index]) == ContainmentType_Disjoint)
			{
				containmentType = ContainmentType_Intersects;
				
				break;
			}
		}
	}
	
	return containmentType;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��ġ ������ ���Կ��� �˻�
///@param point : ��ġ ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingFrustum::Contains( Vector3 point )
{
	for(int i = 0; i < 6; i++)
	{
		Plane plane = planes[i];

		if((double)((float)((double)plane.Normal.X * (double)point.X + (double)plane.Normal.Y * (double)point.Y + (double)plane.Normal.Z * (double)point.Z)+ plane.D) > 9.99999974737875E-06)
			return ContainmentType_Disjoint;
	}
	
	return ContainmentType_Contains;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ������� ���Կ��� �˻�
///@param point : ��ġ ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingFrustum::Contains( BoundingSphere sphere )
{
	Vector3 vector3 = sphere.Center;
	float num1 = sphere.Radius;
	int num2 = 0;

	for(int i = 0; i < 6; i++)
	{
		Plane plane = planes[i];

		float num3 = (float)((double)plane.Normal.X * (double)vector3.X + (double)plane.Normal.Y * (double)vector3.Y + (double)plane.Normal.Z * (double)vector3.Z) + plane.D;
		
		if((double)num3 > (double)num1)
			return ContainmentType_Disjoint;
		else if ((double)num3 < -(double)num1)
			++num2;
	}

	if(num2 != 6)
		return ContainmentType_Intersects;
	else
		return ContainmentType_Contains;
}