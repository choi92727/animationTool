#include "Plane.h"

#include <d3dx9math.h>
#include "Vector4.h"
#include "Matrix.h"
#include "MathHelper.h"
#include "Quaternion.h"

#include "../Bounding/Bounding.h"
#include "../Bounding/BoundingBox.h"
#include "../Bounding/BoundingFrustum.h"
#include "../Bounding/BoundingSphere.h"

//////////////////////////////////////////////////////////////////////////
///@brief ������
//////////////////////////////////////////////////////////////////////////
Plane::Plane( void )
{
	this->D = 0.0f;
	this->Normal = Vector3::Zero;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param a : ����� X
///@param b : ����� Y
///@param c : ����� Z
///@param d : �Ÿ���
//////////////////////////////////////////////////////////////////////////
Plane::Plane( float a, float b, float c, float d )
{
	this->Normal.X = a;
	this->Normal.Y = b;
	this->Normal.Z = c;
	this->D = d;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param normal : ��� ����
///@param d : �Ÿ���
//////////////////////////////////////////////////////////////////////////
Plane::Plane( Vector3 normal, float d )
{
	this->Normal = normal;
	this->D = d;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param value : 4D ����(XYZ, W=�Ÿ�)
//////////////////////////////////////////////////////////////////////////
Plane::Plane( Vector4 value )
{
	this->Normal.X = value.X;
	this->Normal.Y = value.Y;
	this->Normal.Z = value.Z;
	this->D = value.W;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ������
///@param point1 : ��ġ ����1
///@param point2 : ��ġ ����2
///@param point3 : ��ġ ����3
//////////////////////////////////////////////////////////////////////////
Plane::Plane( Vector3 point1, Vector3 point2, Vector3 point3 )
{
	float xValue1 = point2.X - point1.X;
	float yValue1 = point2.Y - point1.Y;
	float zValue1 = point2.Z - point1.Z;
	float xValue2 = point3.X - point1.X;
	float yValue2 = point3.Y - point1.Y;
	float zValue2 = point3.Z - point1.Z;

	float num1 = (float)((double)yValue1 * (double)zValue2 - (double)zValue1 * (double)yValue2);
	float num2 = (float)((double)zValue1 * (double)xValue2 - (double)xValue1 * (double)zValue2);
	float num3 = (float)((double)xValue1 * (double)yValue2 - (double)yValue1 * (double)xValue2);
	float num4 = 1.0f / (float)sqrt((double)num1 * (double)num1 + (double)num2 * (double)num2 + (double)num3 * (double)num3);
	
	this->Normal.X = num1 * num4;
	this->Normal.Y = num2 * num4;
	this->Normal.Z = num3 * num4;
	this->D = (float)-((double)this->Normal.X * (double)point1.X + (double)this->Normal.Y * (double)point1.Y + (double)this->Normal.Z * (double)point1.Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : ���
//////////////////////////////////////////////////////////////////////////
bool Plane::operator==( const Plane& value )const
{
	if((double)Normal.X == (double)value.Normal.X && (double)Normal.Y == (double)value.Normal.Y && (double)Normal.Z == (double)value.Normal.Z)
		return (double)D == (double)value.D;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param value : ���
//////////////////////////////////////////////////////////////////////////
bool Plane::operator!=( const Plane& value )const
{
	if((double)Normal.X == (double)value.Normal.X && (double)Normal.Y == (double)value.Normal.Y && (double)Normal.Z == (double)value.Normal.Z)
		return (double)D != (double)value.D;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ڿ��� ��ȯ
///@param ���ڿ�
//////////////////////////////////////////////////////////////////////////
std::string Plane::ToString()
{
	std::string temp;
	char val[255];

	temp += "{Normal:" + Normal.ToString();
	sprintf(val, " D:%#f}", D); temp += val;

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 
///@param 
//////////////////////////////////////////////////////////////////////////
D3DXPLANE Plane::ToD3DXPLANE()
{
	return D3DXPLANE(Normal.X, Normal.Y, Normal.Z, D);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����ȭ
//////////////////////////////////////////////////////////////////////////
void Plane::Normalize()
{
	float num1 = (float)((double)Normal.X * (double)Normal.X + (double)Normal.Y * (double)Normal.Y + (double)Normal.Z * (double)Normal.Z);
	
	if((double)MathHelper::Abs(num1 - 1.0f) >= 1.19209289550781E-07)
	{
		float num2 = 1.0f / (float)sqrt((double)num1);
		Normal.X *= num2;
		Normal.Y *= num2;
		Normal.Z *= num2;
		D *= num2;
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ����ȭ
///@param value : ���
///@return ��� ���
//////////////////////////////////////////////////////////////////////////
Plane Plane::Normalize( Plane value )
{
	float num1 = (float)((double)value.Normal.X * (double)value.Normal.X + (double)value.Normal.Y * (double)value.Normal.Y + (double)value.Normal.Z * (double)value.Normal.Z);

	if((double)MathHelper::Abs(num1 - 1.0f) < 1.19209289550781E-07)
	{
		Plane plane;
		plane.Normal = value.Normal;
		plane.D = value.D;

		return plane;
	}
	else
	{
		float num2 = 1.0f / (float)sqrt((double)num1);
		
		Plane plane;
		plane.Normal.X = value.Normal.X * num2;
		plane.Normal.Y = value.Normal.Y * num2;
		plane.Normal.Z = value.Normal.Z * num2;
		plane.D = value.D * num2;

		return plane;
	}
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ��Ʈ������ ���� ��� ��ȯ
///@param plane : ���
///@param matrix : ��Ʈ����
///@return ��� ���
//////////////////////////////////////////////////////////////////////////
Plane Plane::Transform( Plane plane, Matrix matrix )
{
	Matrix result;
	result = Matrix::Invert(matrix);

	Plane plane1;
	plane1.Normal.X = (float)((double)plane.Normal.X * (double)result.M11 + (double)plane.Normal.Y * (double)result.M12 + (double)plane.Normal.Z * (double)result.M13 + (double)plane.D * (double)result.M14);
	plane1.Normal.Y = (float)((double)plane.Normal.X * (double)result.M21 + (double)plane.Normal.Y * (double)result.M22 + (double)plane.Normal.Z * (double)result.M23 + (double)plane.D * (double)result.M24);
	plane1.Normal.Z = (float)((double)plane.Normal.X * (double)result.M31 + (double)plane.Normal.Y * (double)result.M32 + (double)plane.Normal.Z * (double)result.M33 + (double)plane.D * (double)result.M34);
	plane1.D = (float)((double)plane.Normal.X * (double)result.M41 + (double)plane.Normal.Y * (double)result.M42 + (double)plane.Normal.Z * (double)result.M43 + (double)plane.D * (double)result.M44);

	return plane1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���ʹϿ¿� ���� ��� ��ȯ
///@param plane : ���
///@param rotation : ���ʹϿ�
///@return ��� ���
//////////////////////////////////////////////////////////////////////////
Plane Plane::Transform( Plane plane, Quaternion rotation )
{
	float wxx = rotation.W * (rotation.X + rotation.X);
	float wyy = rotation.W * (rotation.Y + rotation.Y);
	float wzz = rotation.W * (rotation.Z + rotation.Z);

	float xxx = rotation.X * (rotation.X + rotation.X);
	float xyy = rotation.X * (rotation.Y + rotation.Y);
	float xzz = rotation.X * (rotation.Z + rotation.Z);

	float yyy = rotation.Y * (rotation.Y + rotation.Y);
	float yzz = rotation.Y * (rotation.Z + rotation.Z);
	float zzz = rotation.Z * (rotation.Z + rotation.Z);

	float num1 = 1.0f - yyy - zzz;
	float num2 = xyy - wzz;
	float num3 = xzz + wyy;
	float num4 = xyy + wzz;

	float num5 = 1.0f - xxx - zzz;
	float num6 = yzz - wxx;
	float num7 = xzz - wyy;
	float num8 = yzz + wxx;

	float num9 = 1.0f - xxx - yyy;
	float num10 = plane.Normal.X;
	float num11 = plane.Normal.Y;
	float num12 = plane.Normal.Z;

	Plane plane1;
	plane1.Normal.X = (float)((double)num10 * (double)num1 + (double)num11 * (double)num2 + (double)num12 * (double)num3);
	plane1.Normal.Y = (float)((double)num10 * (double)num4 + (double)num11 * (double)num5 + (double)num12 * (double)num6);
	plane1.Normal.Z = (float)((double)num10 * (double)num7 + (double)num11 * (double)num8 + (double)num12 * (double)num9);
	plane1.D = plane.D;
	
	return plane1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���� 4D ������ ����
///@param value : ����
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
float Plane::Dot( Vector4 value )
{
	return (float)((double)Normal.X * (double)value.X + (double)Normal.Y * (double)value.Y + (double)Normal.Z * (double)value.Z + (double)D * (double)value.W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���� 3D ��ġ ������ ����(W=1.0f)
///@param value : ����
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
float Plane::DotCoordinate( Vector3 value )
{
	return (float)((double)Normal.X * (double)value.X + (double)Normal.Y * (double)value.Y + (double)Normal.Z * (double)value.Z)+ D;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ���� 3D ���� ������ ����(W=0.0f)
///@param value : ����
///@return ��� ��
//////////////////////////////////////////////////////////////////////////
float Plane::DotNormal( Vector3 value )
{
	return (float)((double)Normal.X * (double)value.X + (double)Normal.Y * (double)value.Y + (double)Normal.Z * (double)value.Z);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �ڽ����� ���� �˻�
///@param box : �ٿ�� �ڽ�
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
PlaneIntersectionType Plane::Intersects(BoundingBox box)
{
	Vector3 vector3_1;
	vector3_1.X = (double)Normal.X >= 0.0 ? box.Min.X : box.Max.X;
	vector3_1.Y = (double)Normal.Y >= 0.0 ? box.Min.Y : box.Max.Y;
	vector3_1.Z = (double)Normal.Z >= 0.0 ? box.Min.Z : box.Max.Z;

	Vector3 vector3_2;
	vector3_2.X = (double)Normal.X >= 0.0 ? box.Max.X : box.Min.X;
	vector3_2.Y = (double)Normal.Y >= 0.0 ? box.Max.Y : box.Min.Y;
	vector3_2.Z = (double)Normal.Z >= 0.0 ? box.Max.Z : box.Min.Z;

	if((double)Normal.X * (double)vector3_1.X + (double)Normal.Y * (double)vector3_1.Y + (double)Normal.Z * (double)vector3_1.Z + (double)D > 0.0)
		return PlaneIntersectionType_Front;
	else if ((double)Normal.X * (double)vector3_2.X + (double)Normal.Y * (double)vector3_2.Y + (double)Normal.Z * (double)vector3_2.Z + (double)D < 0.0)
		return PlaneIntersectionType_Back;
	else
		return PlaneIntersectionType_Intersecting;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������Ұ��� �����˻�
///@param frustum : �ٿ�� ��������
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
PlaneIntersectionType Plane::Intersects( BoundingFrustum frustum )
{
	PlaneIntersectionType result;
	frustum.Intersects(*this, result);

	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief �ٿ�� �������� �����˻�
///@param sphere : �ٿ�� �����
///@return ���� ���
//////////////////////////////////////////////////////////////////////////
PlaneIntersectionType Plane::Intersects( BoundingSphere sphere )
{
	float num = (float)((double)sphere.Center.X * (double)Normal.X + (double)sphere.Center.Y * (double)Normal.Y + (double)sphere.Center.Z * (double)Normal.Z) + D;
	
	if ((double)num > (double)sphere.Radius)
		return PlaneIntersectionType_Front;
	else if ((double)num < -(double)sphere.Radius)
		return PlaneIntersectionType_Back;
	else
		return PlaneIntersectionType_Intersecting;	
}