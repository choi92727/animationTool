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
///@brief 생성자
//////////////////////////////////////////////////////////////////////////
BoundingFrustum::BoundingFrustum( void )
{

}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param value : 매트릭스
//////////////////////////////////////////////////////////////////////////
BoundingFrustum::BoundingFrustum( Matrix value )
{
	SetMatrix(value);
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : 바운딩 프러스텀
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::operator==( const BoundingFrustum& value ) const
{
	return Equals(value);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param value : 바운딩 프러스텀
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::operator!=( const BoundingFrustum& value ) const
{
	return !Equals(value);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 문자열로 변환
///@param 문자열
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
///@brief 서포트 매핑
///@param v : 벡터
///@return 결과 벡터
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
///@brief 값이 같은 객체인지 검사
///@param value : 바운딩 프러스텀
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Equals( const BoundingFrustum& value ) const
{
	bool flag = false;
	flag = matrix == value.matrix;

	return flag;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 근면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Near() const
{
	return planes[0];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 원면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Far() const
{
	return planes[1];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 좌측면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Left() const
{
	return planes[2];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 우측면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Right() const
{
	return planes[3];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 윗면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Top() const
{
	return planes[4];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 아랫면
///@return 결과 면
//////////////////////////////////////////////////////////////////////////
Plane BoundingFrustum::Bottom() const
{
	return planes[5];
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix BoundingFrustum::GetMatrix() const
{
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 매트릭스 세팅
///@param value : 설정할 매트릭스
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
///@brief 코너 얻기
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
///@brief 면 두개의 교차선 계산
///@return 결과 교차선
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
///@brief 면과 레이의 교차 위치 계산
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 BoundingFrustum::ComputeIntersection( Plane plane, Ray ray )
{
	float num = (-plane.D - Vector3::Dot(plane.Normal, ray.Position)) / Vector3::Dot(plane.Normal, ray.Direction);
	
	return ray.Position + ray.Direction * num;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 바운딩 박스와 교차 검사
///@param box : 바운딩 박스
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Intersects( BoundingBox box )
{	
	bool result = false;
	Intersects(box, result);
	
	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 바운딩 박스와 교차 검사
///@param box : 바운딩 박스
///@param result : 결과
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
///@brief 바운딩 프러스텀과 교차 검사
///@param frustum : 바운딩 프러스텀
///@return 결과
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
///@brief 면과 교차 검사
///@param plane : 면
///@return 결과
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
///@brief 레이와의 교차검사
///@param ray : 레이
///@param result : 교차 결과값
///@warning
///		교차가 되지 않은 결과 result는 0.0f이 절대 아니다!
///		result == NULL 이다!!!!!
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
///@brief 바운딩 스페어와 교차검사
///@param sphere : 바운딩 스페어
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool BoundingFrustum::Intersects( BoundingSphere sphere )
{
	bool result = false;
	Intersects(sphere, result);
	
	return result;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 바운딩 스페어와 교차검사
///@param sphere : 바운딩 스페어
///@param result : 결과
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
///@brief 바운딩 박스의 포함 여부 검사
///@param box : 바운딩 박스
///@return 포함 결과
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
///@brief 바운딩 프러스텀의 포함여부 검사
///@param frustum : 바운딩 프러스텀
///@return 포함 결과
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
///@brief 위치 벡터의 포함여부 검사
///@param point : 위치 벡터
///@return 포함 결과
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
///@brief 바운딩 스페어의 포함여부 검사
///@param point : 위치 벡터
///@return 포함 결과
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