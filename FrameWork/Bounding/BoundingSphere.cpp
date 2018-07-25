#include "BoundingSphere.h"

#include <assert.h>
#include "Bounding.h"
#include "BoundingBox.h"
#include "BoundingFrustum.h"
#include "Ray.h"

#include "../Core/Plane.h"
#include "../Core/MathHelper.h"

//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
BoundingSphere::BoundingSphere( void )
{
	this->Center = Vector3::Zero;
	this->Radius = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param center : ��ġ ����
///@param radius : ������ ��
//////////////////////////////////////////////////////////////////////////
BoundingSphere::BoundingSphere( Vector3 center, float radius )
{
	assert(radius >= 0.0f);

	this->Center = center;
	this->Radius = radius;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : �ٿ�� �����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::operator==( const BoundingSphere& value ) const
{
	if(this->Center == value.Center)
		return (double)this->Radius == (double)value.Radius;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value : �ٿ�� �����
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::operator!=( const BoundingSphere& value ) const
{
	if (!(this->Center != value.Center))
		return (double)this->Radius != (double)value.Radius;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����Ʈ ����
///@param v : ����
///@return ��� ����
//////////////////////////////////////////////////////////////////////////
Vector3 BoundingSphere::SupportMapping( Vector3 v )
{
	float num = Radius / v.Length();

	Vector3 result;
	result.X = Center.X + v.X * num;
	result.Y = Center.Y + v.Y * num;
	result.Z = Center.Z + v.Z * num;

	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �� ���� �ٿ�� ����� ��ħ
///@param original : �ٿ�� �����1
///@param additional : �ٿ�� �����2
///@return ��� �ٿ�� �����
//////////////////////////////////////////////////////////////////////////
BoundingSphere BoundingSphere::CreateMerged( BoundingSphere original, BoundingSphere additional )
{
	Vector3 result = additional.Center - original.Center;

	float num1 = result.Length();
	float num2 = original.Radius;
	float num3 = additional.Radius;
	
	if((double)num2 + (double)num3 >= (double)num1)
	{
		if ((double)num2 - (double)num3 >= (double)num1)
			return original;
		else if ((double)num3 - (double)num2 >= (double)num1)
			return additional;
	}

	Vector3 vector3 = result * (1.0f / num1);
	float num4 = MathHelper::Min(-num2, num1 - num3);
	float num5 = (float)(((double)MathHelper::Max(num2, num1 + num3) - (double)num4)* 0.5);
	
	BoundingSphere boundingSphere;
	boundingSphere.Center = original.Center + vector3 * (num5 + num4);
	boundingSphere.Radius = num5;

	return boundingSphere;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ��κ��� �ٿ�� ����� ����
///@param box : �ٿ�� �ڽ�
///@return ��� �ٿ�� �����
//////////////////////////////////////////////////////////////////////////
BoundingSphere BoundingSphere::CreateFromBoundingBox( BoundingBox box )
{
	BoundingSphere boundingSphere;
	boundingSphere.Center = Vector3::Lerp(box.Min, box.Max, 0.5f);
	
	float result;
	result = Vector3::Distance(box.Min, box.Max);
	boundingSphere.Radius = result * 0.5f;
	
	return boundingSphere;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ����� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::Intersects( BoundingBox box )
{
	Vector3 result1 = Vector3::Clamp(Center, box.Min, box.Max);
	float result2 = Vector3::DistanceSquared(Center, result1);
	
	if((double)result2 <= (double)Radius * (double)Radius)
		return true;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������Ұ��� ���� �˻�
///@param frustum : �ٿ�� ��������
///@return ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::Intersects( BoundingFrustum frustum )
{
	bool result;
	frustum.Intersects(*this, result);
	
	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������ ���� �˻�
///@param plane : ���
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
PlaneIntersectionType BoundingSphere::Intersects( Plane plane )
{
	return plane.Intersects(*this);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���̿��� ���� �˻�
///@param ray : ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::Intersects( Ray ray, float& result )
{
	return ray.Intersects(*this, result);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������� ���� �˻�
///@param sphere : �ٿ�� �����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
bool BoundingSphere::Intersects( BoundingSphere sphere )
{
	float result = Vector3::DistanceSquared(Center, sphere.Center);
	float num1 = Radius;
	float num2 = sphere.Radius;

	if((double)num1 * (double)num1 + 2.0 * (double)num1 * (double)num2 + (double)num2 * (double)num2 <= (double)result)
		return false;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingSphere::Contains( BoundingBox box )
{
	if(!box.Intersects(*this))
	{
		return ContainmentType_Disjoint;
	}
	else
	{
		float num = Radius * Radius;
		
		Vector3 vector3;
		vector3.X = Center.X - box.Min.X;
		vector3.Y = Center.Y - box.Max.Y;
		vector3.Z = Center.Z - box.Max.Z;

		if((double)vector3.LengthSquared() > (double)num)
		{
			return ContainmentType_Intersects;
		}
		else
		{
			vector3.X = Center.X - box.Max.X;
			vector3.Y = Center.Y - box.Max.Y;
			vector3.Z = Center.Z - box.Max.Z;
			
			if ((double)vector3.LengthSquared() > (double)num)
			{
				return ContainmentType_Intersects;
			}
			else
			{
				vector3.X = Center.X - box.Max.X;
				vector3.Y = Center.Y - box.Min.Y;
				vector3.Z = Center.Z - box.Max.Z;
				
				if((double)vector3.LengthSquared() > (double)num)
				{
					return ContainmentType_Intersects;
				}
				else
				{
					vector3.X = Center.X - box.Min.X;
					vector3.Y = Center.Y - box.Min.Y;
					vector3.Z = Center.Z - box.Max.Z;

					if((double)vector3.LengthSquared() > (double)num)
					{
						return ContainmentType_Intersects;
					}
					else
					{
						vector3.X = Center.X - box.Min.X;
						vector3.Y = Center.Y - box.Max.Y;
						vector3.Z = Center.Z - box.Min.Z;

						if((double)vector3.LengthSquared() > (double)num)
						{
							return ContainmentType_Intersects;
						}
						else
						{
							vector3.X = Center.X - box.Max.X;
							vector3.Y = Center.Y - box.Max.Y;
							vector3.Z = Center.Z - box.Min.Z;

							if((double)vector3.LengthSquared() > (double)num)
							{
								return ContainmentType_Intersects;
							}
							else
							{
								vector3.X = Center.X - box.Max.X;
								vector3.Y = Center.Y - box.Min.Y;
								vector3.Z = Center.Z - box.Min.Z;

								if((double)vector3.LengthSquared() > (double)num)
								{
									return ContainmentType_Intersects;
								}
								else
								{
									vector3.X = Center.X - box.Min.X;
									vector3.Y = Center.Y - box.Min.Y;
									vector3.Z = Center.Z - box.Min.Z;

									if((double)vector3.LengthSquared() > (double)num)
										return ContainmentType_Intersects;
									else
										return ContainmentType_Contains;
								}
							}
						}
					}
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������Ұ��� ���� �˻�
///@param frustum : �ٿ�� ��������
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingSphere::Contains( BoundingFrustum frustum )
{
	if(!frustum.Intersects(*this))
	{
		return ContainmentType_Disjoint;
	}
	else
	{
		float num = Radius * Radius;
		
		for(int i = 0; i < 8; i++)
		{
			Vector3 vector3_1 = frustum.cornerArray[i];
			
			Vector3 vector3_2;
			vector3_2.X = vector3_1.X - Center.X;
			vector3_2.Y = vector3_1.Y - Center.Y;
			vector3_2.Z = vector3_1.Z - Center.Z;

			if((double)vector3_2.LengthSquared() > (double)num)
				return ContainmentType_Intersects;
		}
		
		return ContainmentType_Contains;
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��ġ ������ ���� �˻�
///@param point : ��ġ ����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingSphere::Contains( Vector3 point )
{
	if ((double)Vector3::DistanceSquared(point, Center) >= (double)Radius * (double)Radius)
		return ContainmentType_Disjoint;
	else
		return ContainmentType_Contains;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� ������� ���� ���� �˻�
///@param sphere : �ٿ�� �����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
ContainmentType BoundingSphere::Contains( BoundingSphere sphere )
{
	float result = Vector3::Distance(Center, sphere.Center);
	float num1 = Radius;
	float num2 = sphere.Radius;
	
	if((double)num1 + (double)num2 < (double)result)
		return ContainmentType_Disjoint;
	else if((double)num1 - (double)num2 < (double)result)
		return ContainmentType_Intersects;
	else
		return ContainmentType_Contains;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ʈ������ ���� �ٿ�� ����� ��ȯ
///@param matrix : ��Ʈ����
///@return ��� �ٿ�� �����
//////////////////////////////////////////////////////////////////////////
BoundingSphere BoundingSphere::Transform( Matrix matrix )
{
	BoundingSphere boundingSphere;
	boundingSphere.Center = Vector3::Transform(Center, matrix);

	float num = MathHelper::Max((float)(
		(double)matrix.M11 * (double)matrix.M11 + (double)matrix.M12 * (double)matrix.M12 + (double)matrix.M13 * (double)matrix.M13), 
		MathHelper::Max((float)((double)matrix.M21 * (double)matrix.M21 + (double)matrix.M22 * (double)matrix.M22 + (double)matrix.M23 * (double)matrix.M23), 
		(float)((double)matrix.M31 * (double)matrix.M31 + (double)matrix.M32 * (double)matrix.M32 + (double)matrix.M33 * (double)matrix.M33)));

	boundingSphere.Radius = Radius * (float)sqrt((double)num);
	
	return boundingSphere;
}