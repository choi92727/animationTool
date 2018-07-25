#include "Quaternion.h"

#include <d3dx9math.h>
#include "Vector3.h"
#include "Matrix.h"

//////////////////////////////////////////////////////////////////////////

const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion( void )
{
	this->X = 0.0f;
	this->Y = 0.0f;
	this->Z = 0.0f;
	this->W = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param x : X
///@param y : Y
///@param z : Z
///@param w : W
//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion( float x, float y, float z, float w )
{
	this->X = x;
	this->Y = y;
	this->Z = z;
	this->W = w;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param vectorPart : 벡터(XYZ)
///@param scalarPart : 값(W)
//////////////////////////////////////////////////////////////////////////
Quaternion::Quaternion( Vector3 vectorPart, float scalarPart )
{
	this->X = vectorPart.X;
	this->Y = vectorPart.Y;
	this->Z = vectorPart.Z;
	this->W = scalarPart;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator-( void )
{
	Quaternion quaternion1;
	quaternion1.X = -this->X;
	quaternion1.Y = -this->Y;
	quaternion1.Z = -this->Z;
	quaternion1.W = -this->W;

	return quaternion1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Quaternion::operator==( const Quaternion& quaternion2 ) const
{
	if((double)X == (double)quaternion2.X && (double)Y == (double)quaternion2.Y && (double)Z == (double)quaternion2.Z)
		return (double)W == (double)quaternion2.W;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Quaternion::operator!=( const Quaternion& quaternion2 ) const
{
	if((double)X == (double)quaternion2.X && (double)Y == (double)quaternion2.Y && (double)Z == (double)quaternion2.Z)
		return (double)W != (double)quaternion2.W;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator+( const Quaternion& quaternion2 ) const
{
	Quaternion quaternion;
	quaternion.X = this->X + quaternion2.X;
	quaternion.Y = this->Y + quaternion2.Y;
	quaternion.Z = this->Z + quaternion2.Z;
	quaternion.W = this->W + quaternion2.W;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator-( const Quaternion& quaternion2 ) const
{
	Quaternion quaternion;
	quaternion.X = this->X - quaternion2.X;
	quaternion.Y = this->Y - quaternion2.Y;
	quaternion.Z = this->Z - quaternion2.Z;
	quaternion.W = this->W - quaternion2.W;
	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator*( const Quaternion& quaternion2 ) const
{
	float num1 = (float)((double)this->Y * (double)quaternion2.Z - (double)this->Z * (double)quaternion2.Y);
	float num2 = (float)((double)this->Z * (double)quaternion2.X - (double)this->X * (double)quaternion2.Z);
	float num3 = (float)((double)this->X * (double)quaternion2.Y - (double)this->Y * (double)quaternion2.X);
	float num4 = (float)((double)this->X * (double)quaternion2.X + (double)this->Y * (double)quaternion2.Y + (double)this->Z * (double)quaternion2.Z);

	Quaternion quaternion;
	quaternion.X = (float)((double)this->X * (double)quaternion2.W + (double)quaternion2.X * (double)this->W) + num1;
	quaternion.Y = (float)((double)this->Y * (double)quaternion2.W + (double)quaternion2.Y * (double)this->W) + num2;
	quaternion.Z = (float)((double)this->Z * (double)quaternion2.W + (double)quaternion2.Z * (double)this->W) + num3;
	quaternion.W = this->W * quaternion2.W - num4;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : 값
///@return 결과
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator*( const float& scaleFactor ) const
{
	Quaternion quaternion;
	quaternion.X = this->X * scaleFactor;
	quaternion.Y = this->Y * scaleFactor;
	quaternion.Z = this->Z * scaleFactor;
	quaternion.W = this->W * scaleFactor;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::operator/( const Quaternion& quaternion2 ) const
{
	float num1 = 1.0f / (float)((double)quaternion2.X * (double)quaternion2.X + (double)quaternion2.Y * (double)quaternion2.Y + (double)quaternion2.Z * (double)quaternion2.Z + (double)quaternion2.W * (double)quaternion2.W);
	float num2 = -quaternion2.X * num1;
	float num3 = -quaternion2.Y * num1;
	float num4 = -quaternion2.Z * num1;
	float num5 = quaternion2.W * num1;

	float multiple1 = (float)((double)this->Y * (double)num4 - (double)this->Z * (double)num3);
	float multiple2 = (float)((double)this->Z * (double)num2 - (double)this->X * (double)num4);
	float multiple3 = (float)((double)this->X * (double)num3 - (double)this->Y * (double)num2);
	float multiple4 = (float)((double)this->X * (double)num2 + (double)this->Y * (double)num3 + (double)this->Z * (double)num4);

	Quaternion quaternion;
	quaternion.X = (float)((double)this->X * (double)num5 + (double)num2 * (double)this->W) + multiple1;
	quaternion.Y = (float)((double)this->Y * (double)num5 + (double)num3 * (double)this->W) + multiple2;
	quaternion.Z = (float)((double)this->Z * (double)num5 + (double)num4 * (double)this->W) + multiple3;
	quaternion.W = this->W * num5 - multiple4;
	
	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
void Quaternion::operator+=( const Quaternion& quaternion2 )
{
	*this = *this + quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
void Quaternion::operator-=( const Quaternion& quaternion2 )
{
	*this = *this - quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
void Quaternion::operator*=( const Quaternion& quaternion2 )
{
	*this = *this * quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param scaleFactor : 값
///@return 결과
//////////////////////////////////////////////////////////////////////////
void Quaternion::operator*=( const float& scaleFactor )
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param quaternion2 : 쿼터니온
///@return 결과
//////////////////////////////////////////////////////////////////////////
void Quaternion::operator/=( const Quaternion& quaternion2 )
{
	*this = *this / quaternion2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 문자열로 변환
///@param 문자열
//////////////////////////////////////////////////////////////////////////
std::string Quaternion::ToString()
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
///@brief D3DXQUATERNION으로 변환
///@param D3DX 쿼터니온
//////////////////////////////////////////////////////////////////////////
D3DXQUATERNION Quaternion::ToD3DXQUATERNION()
{
	return D3DXQUATERNION(X, Y, Z, W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 크기 계산
///@return 결과 값
//////////////////////////////////////////////////////////////////////////
float Quaternion::Length()
{
	return (float)sqrt((double)X * (double)X + (double)Y * (double)Y + (double)Z * (double)Z + (double)W * (double)W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 제곱으로 크기 계산
///@return 결과 값
//////////////////////////////////////////////////////////////////////////
float Quaternion::LengthSquared()
{
	return (float)((double)X * (double)X + (double)Y * (double)Y + (double)Z * (double)Z + (double)W * (double)W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정규화
//////////////////////////////////////////////////////////////////////////
void Quaternion::Normalize()
{
	float num = 1.0f / (float)sqrt((double)X * (double)X + (double)Y * (double)Y + (double)Z * (double)Z + (double)W * (double)W);
	
	X *= num;
	Y *= num;
	Z *= num;
	W *= num;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정규화
///@param value : 쿼터니온
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Normalize( Quaternion quaternion )
{
	float num = 1.0f / (float)sqrt((double)quaternion.X * (double)quaternion.X + (double)quaternion.Y * (double)quaternion.Y + (double)quaternion.Z * (double)quaternion.Z + (double)quaternion.W * (double)quaternion.W);

	Quaternion quaternion1;
	quaternion1.X = quaternion.X * num;
	quaternion1.Y = quaternion.Y * num;
	quaternion1.Z = quaternion.Z * num;
	quaternion1.W = quaternion.W * num;

	return quaternion1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 쿼터니온 켤레값
//////////////////////////////////////////////////////////////////////////
void Quaternion::Conjugate()
{
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 쿼터니온 켤레값
///@param value : 쿼터니온
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Conjugate( Quaternion value )
{
	Quaternion quaternion;
	quaternion.X = -value.X;
	quaternion.Y = -value.Y;
	quaternion.Z = -value.Z;
	quaternion.W = value.W;
	
	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 역 쿼터니온
///@param quaternion : 쿼터니온
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Inverse( Quaternion quaternion )
{
	float num = 1.0f / (float)((double)quaternion.X * (double)quaternion.X + (double)quaternion.Y * (double)quaternion.Y + (double)quaternion.Z * (double)quaternion.Z + (double)quaternion.W * (double)quaternion.W);

	Quaternion quaternion1;
	quaternion1.X = -quaternion.X * num;
	quaternion1.Y = -quaternion.Y * num;
	quaternion1.Z = -quaternion.Z * num;
	quaternion1.W = quaternion.W * num;
	
	return quaternion1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 축과 각도에 의해 회전된 쿼터니온
///@param axis : 축 벡터
///@param angle : 각도
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::CreateFromAxisAngle( Vector3 axis, float angle )
{
	float sinValue = (float)sin((double)(angle * 0.5f));
	float cosValue = (float)cos((double)(angle * 0.5f));

	Quaternion quaternion;
	quaternion.X = axis.X * sinValue;
	quaternion.Y = axis.Y * sinValue;
	quaternion.Z = axis.Z * sinValue;
	quaternion.W = cosValue;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 각 각도에 의해 회전된 쿼터니온
///@param yaw : Yaw
///@param pitch : Pitch
///@param roll : Roll
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::CreateFromYawPitchRoll( float yaw, float pitch, float roll )
{
	float roll1 = roll * 0.5f;
	float roll2 = (float)sin((double)roll1);
	float roll3 = (float)cos((double)roll1);

	float pitch1 = pitch * 0.5f;
	float pitch2 = (float)sin((double)pitch1);
	float pitch3 = (float)cos((double)pitch1);

	float yaw1 = yaw * 0.5f;
	float yaw2 = (float)sin((double)yaw1);
	float yaw3 = (float)cos((double)yaw1);
	
	Quaternion quaternion;
	quaternion.X = (float)((double)yaw3 * (double)pitch2 * (double)roll3 + (double)yaw2 * (double)pitch3 * (double)roll2);
	quaternion.Y = (float)((double)yaw2 * (double)pitch3 * (double)roll3 - (double)yaw3 * (double)pitch2 * (double)roll2);
	quaternion.Z = (float)((double)yaw3 * (double)pitch3 * (double)roll2 - (double)yaw2 * (double)pitch2 * (double)roll3);
	quaternion.W = (float)((double)yaw3 * (double)pitch3 * (double)roll3 + (double)yaw2 * (double)pitch2 * (double)roll2);

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 매트릭스에 의해 회전된 쿼터니온
///@param matrix : 매트릭스
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::CreateFromRotationMatrix( Matrix matrix )
{
	float num1 = matrix.M11 + matrix.M22 + matrix.M33;

	Quaternion quaternion;
	if((double)num1 > 0.0)
	{
		float num2 = (float)sqrt((double)num1 + 1.0);
		quaternion.W = num2 * 0.5f;

		float num3 = 0.5f / num2;
		quaternion.X = (matrix.M23 - matrix.M32)* num3;
		quaternion.Y = (matrix.M31 - matrix.M13)* num3;
		quaternion.Z = (matrix.M12 - matrix.M21)* num3;
	}
	else if((double)matrix.M11 >= (double)matrix.M22 && (double)matrix.M11 >= (double)matrix.M33)
	{
		float num2 = (float)sqrt(1.0 + (double)matrix.M11 - (double)matrix.M22 - (double)matrix.M33);

		float num3 = 0.5f / num2;
		quaternion.X = 0.5f * num2;
		quaternion.Y = (matrix.M12 + matrix.M21)* num3;
		quaternion.Z = (matrix.M13 + matrix.M31)* num3;
		quaternion.W = (matrix.M23 - matrix.M32)* num3;
	}
	else if((double)matrix.M22 > (double)matrix.M33)
	{
		float num2 = (float)sqrt(1.0 + (double)matrix.M22 - (double)matrix.M11 - (double)matrix.M33);

		float num3 = 0.5f / num2;
		quaternion.X = (matrix.M21 + matrix.M12)* num3;
		quaternion.Y = 0.5f * num2;
		quaternion.Z = (matrix.M32 + matrix.M23)* num3;
		quaternion.W = (matrix.M31 - matrix.M13)* num3;
	}
	else
	{
		float num2 = (float)sqrt(1.0 + (double)matrix.M33 - (double)matrix.M11 - (double)matrix.M22);

		float num3 = 0.5f / num2;
		quaternion.X = (matrix.M31 + matrix.M13)* num3;
		quaternion.Y = (matrix.M32 + matrix.M23)* num3;
		quaternion.Z = 0.5f * num2;
		quaternion.W = (matrix.M12 - matrix.M21)* num3;
	}

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 내적
///@param quaternion1 : 쿼터니온1
///@param quaternion2 : 쿼터니온2
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
float Quaternion::Dot( Quaternion quaternion1, Quaternion quaternion2 )
{
	return (float)((double)quaternion1.X * (double)quaternion2.X + (double)quaternion1.Y * (double)quaternion2.Y + (double)quaternion1.Z * (double)quaternion2.Z + (double)quaternion1.W * (double)quaternion2.W);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 구면보간
///@param quaternion1 : 쿼터니온1
///@param quaternion2 : 쿼터니온2
///@param amount : 보간값
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Slerp( Quaternion quaternion1, Quaternion quaternion2, float amount )
{
	float normal = (float)((double)quaternion1.X * (double)quaternion2.X + (double)quaternion1.Y * (double)quaternion2.Y + (double)quaternion1.Z * (double)quaternion2.Z + (double)quaternion1.W * (double)quaternion2.W);

	bool flag = false;
	if((double)normal < 0.0)
	{
		flag = true;
		normal = -normal;
	}

	float num1, num2;
	if((double)normal > 0.999998986721039)
	{
		num1 = 1.0f - amount;
		num2 = flag ? -amount : amount;
	}
	else
	{
		float num3 = (float)acos((double)normal);
		float num4 = (float)(1.0 / sin((double)num3));

		num1 = (float)sin((1.0 - (double)amount)* (double)num3)* num4;
		num2 = flag ? (float)-sin((double)amount * (double)num3)* num4 : (float)sin((double)amount * (double)num3)* num4;
	}
	Quaternion quaternion;
	quaternion.X = (float)((double)num1 * (double)quaternion1.X + (double)num2 * (double)quaternion2.X);
	quaternion.Y = (float)((double)num1 * (double)quaternion1.Y + (double)num2 * (double)quaternion2.Y);
	quaternion.Z = (float)((double)num1 * (double)quaternion1.Z + (double)num2 * (double)quaternion2.Z);
	quaternion.W = (float)((double)num1 * (double)quaternion1.W + (double)num2 * (double)quaternion2.W);

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 선형보간
///@param quaternion1 : 쿼터니온1
///@param quaternion2 : 쿼터니온2
///@param amount : 보간값
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Lerp( Quaternion quaternion1, Quaternion quaternion2, float amount )
{
	float amountInv = 1.0f - amount;
	Quaternion quaternion;

	if((double)quaternion1.X * (double)quaternion2.X + (double)quaternion1.Y * (double)quaternion2.Y + (double)quaternion1.Z * (double)quaternion2.Z + (double)quaternion1.W * (double)quaternion2.W >= 0.0)
	{
		quaternion.X = (float)((double)amountInv * (double)quaternion1.X + (double)amount * (double)quaternion2.X);
		quaternion.Y = (float)((double)amountInv * (double)quaternion1.Y + (double)amount * (double)quaternion2.Y);
		quaternion.Z = (float)((double)amountInv * (double)quaternion1.Z + (double)amount * (double)quaternion2.Z);
		quaternion.W = (float)((double)amountInv * (double)quaternion1.W + (double)amount * (double)quaternion2.W);
	}
	else
	{
		quaternion.X = (float)((double)amountInv * (double)quaternion1.X - (double)amount * (double)quaternion2.X);
		quaternion.Y = (float)((double)amountInv * (double)quaternion1.Y - (double)amount * (double)quaternion2.Y);
		quaternion.Z = (float)((double)amountInv * (double)quaternion1.Z - (double)amount * (double)quaternion2.Z);
		quaternion.W = (float)((double)amountInv * (double)quaternion1.W - (double)amount * (double)quaternion2.W);
	}
	
	float length = 1.0f / (float)sqrt((double)quaternion.X * (double)quaternion.X + (double)quaternion.Y * (double)quaternion.Y + (double)quaternion.Z * (double)quaternion.Z + (double)quaternion.W * (double)quaternion.W);
	quaternion.X *= length;
	quaternion.Y *= length;
	quaternion.Z *= length;
	quaternion.W *= length;

	return quaternion;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 순서를 바꾸어 곱하기
///@param value1 : 쿼터니온1
///@param value2 : 쿼터니온2
///@return 결과 쿼터니온
//////////////////////////////////////////////////////////////////////////
Quaternion Quaternion::Concatenate( Quaternion value1, Quaternion value2 )
{
	float num1 = (float)((double)value2.Y * (double)value1.Z - (double)value2.Z * (double)value1.Y);
	float num2 = (float)((double)value2.Z * (double)value1.X - (double)value2.X * (double)value1.Z);
	float num3 = (float)((double)value2.X * (double)value1.Y - (double)value2.Y * (double)value1.X);
	float num4 = (float)((double)value2.X * (double)value1.X + (double)value2.Y * (double)value1.Y + (double)value2.Z * (double)value1.Z);

	Quaternion quaternion;
	quaternion.X = (float)((double)value2.X * (double)value1.W + (double)value1.X * (double)value2.W)+ num1;
	quaternion.Y = (float)((double)value2.Y * (double)value1.W + (double)value1.Y * (double)value2.W)+ num2;
	quaternion.Z = (float)((double)value2.Z * (double)value1.W + (double)value1.Z * (double)value2.W)+ num3;
	quaternion.W = value2.W * value1.W - num4;

	return quaternion;
}