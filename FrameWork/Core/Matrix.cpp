#include "Matrix.h"

#include <assert.h>
#include <d3dx9math.h>
#include "Vector3.h"
#include "Quaternion.h"
#include "Plane.h"

//////////////////////////////////////////////////////////////////////////

const Matrix Matrix::Identity = Matrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
///@brief 생성자
//////////////////////////////////////////////////////////////////////////
Matrix::Matrix( void )
{
	this->M11 = 0.0f; this->M12 = 0.0f; this->M13 = 0.0f; this->M14 = 0.0f;
	this->M21 = 0.0f; this->M22 = 0.0f; this->M23 = 0.0f; this->M24 = 0.0f;
	this->M31 = 0.0f; this->M32 = 0.0f; this->M33 = 0.0f; this->M34 = 0.0f;
	this->M41 = 0.0f; this->M42 = 0.0f; this->M43 = 0.0f; this->M44 = 0.0f;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param m11 : M11
///@param m12 : M12
///@param m13 : M13
///@param m14 : M14
///@param m21 : M21
///@param m22 : M22
///@param m23 : M23
///@param m24 : M24
///@param m31 : M31
///@param m32 : M32
///@param m33 : M33
///@param m34 : M34
///@param m41 : M41
///@param m42 : M42
///@param m43 : M43
///@param m44 : M44
//////////////////////////////////////////////////////////////////////////
Matrix::Matrix( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 )
{
	this->M11 = m11; this->M12 = m12; this->M13 = m13; this->M14 = m14;
	this->M21 = m21; this->M22 = m22; this->M23 = m23; this->M24 = m24;
	this->M31 = m31; this->M32 = m32; this->M33 = m33; this->M34 = m34;
	this->M41 = m41; this->M42 = m42; this->M43 = m43; this->M44 = m44;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 업 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Up()
{
	Vector3 vector3;
	vector3.X = this->M21; vector3.Y = this->M22; vector3.Z = this->M23;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 업 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Up( Vector3 value )
{
	this->M21 = value.X; this->M22 = value.Y; this->M23 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 다운 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Down()
{
	Vector3 vector3;
	vector3.X = -this->M21; vector3.Y = -this->M22; vector3.Z = -this->M23;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 다운 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Down( Vector3 value )
{
	this->M21 = -value.X; this->M22 = -value.Y; this->M23 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 라이트 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Right()
{
	Vector3 vector3;
	vector3.X = this->M11; vector3.Y = this->M12; vector3.Z = this->M13;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 다운 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Right( Vector3 value )
{
	this->M11 = value.X; this->M12 = value.Y; this->M13 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 레프트 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Left()
{
	Vector3 vector3;
	vector3.X = -this->M11; vector3.Y = -this->M12; vector3.Z = -this->M13;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 레프트 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Left( Vector3 value )
{
	this->M11 = -value.X; this->M12 = -value.Y; this->M13 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 포워드 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Forward()
{
	Vector3 vector3;
	vector3.X = -this->M31; vector3.Y = -this->M32; vector3.Z = -this->M33;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 포워드 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Forward( Vector3 value )
{
	this->M31 = -value.X; this->M32 = -value.Y; this->M33 = -value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 백워드 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Backward()
{
	Vector3 vector3;
	vector3.X = this->M31; vector3.Y = this->M32; vector3.Z = this->M33;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 백워드 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Backward( Vector3 value )
{
	this->M31 = value.X; this->M32 = value.Y; this->M33 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 이동 벡터
///@return 결과 벡터
//////////////////////////////////////////////////////////////////////////
Vector3 Matrix::Translate()
{
	Vector3 vector3;
	vector3.X = this->M41; vector3.Y = this->M42; vector3.Z = this->M43;

	return vector3;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 이동 벡터
///@param value : 벡터
//////////////////////////////////////////////////////////////////////////
void Matrix::Translate( Vector3 value )
{
	this->M41 = value.X; this->M42 = value.Y; this->M43 = value.Z;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator-()
{
	Matrix matrix;
	matrix.M11 = -M11; matrix.M12 = -M12; matrix.M13 = -M13; matrix.M14 = -M14;
	matrix.M21 = -M21; matrix.M22 = -M22; matrix.M23 = -M23; matrix.M24 = -M24;
	matrix.M31 = -M31; matrix.M32 = -M32; matrix.M33 = -M33; matrix.M34 = -M34;
	matrix.M41 = -M41; matrix.M42 = -M42; matrix.M43 = -M43; matrix.M44 = -M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief ==
///@param matrix2 : 매트릭스
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Matrix::operator==( const Matrix& matrix2 ) const
{
	if ((double)this->M11 == (double)matrix2.M11 && (double)this->M22 == (double)matrix2.M22 && ((double)this->M33 == (double)matrix2.M33 && (double)this->M44 == (double)matrix2.M44)&& ((double)this->M12 == (double)matrix2.M12 && (double)this->M13 == (double)matrix2.M13 && ((double)this->M14 == (double)matrix2.M14 && (double)this->M21 == (double)matrix2.M21))&& ((double)this->M23 == (double)matrix2.M23 && (double)this->M24 == (double)matrix2.M24 && ((double)this->M31 == (double)matrix2.M31 && (double)this->M32 == (double)matrix2.M32)&& ((double)this->M34 == (double)matrix2.M34 && (double)this->M41 == (double)matrix2.M41 && (double)this->M42 == (double)matrix2.M42)))
		return (double)this->M43 == (double)matrix2.M43;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief !=
///@param matrix2 : 매트릭스
///@return 결과
//////////////////////////////////////////////////////////////////////////
bool Matrix::operator!=( const Matrix& matrix2 ) const
{
	if ((double)this->M11 == (double)matrix2.M11 && (double)this->M12 == (double)matrix2.M12 && ((double)this->M13 == (double)matrix2.M13 && (double)this->M14 == (double)matrix2.M14)&& ((double)this->M21 == (double)matrix2.M21 && (double)this->M22 == (double)matrix2.M22 && ((double)this->M23 == (double)matrix2.M23 && (double)this->M24 == (double)matrix2.M24))&& ((double)this->M31 == (double)matrix2.M31 && (double)this->M32 == (double)matrix2.M32 && ((double)this->M33 == (double)matrix2.M33 && (double)this->M34 == (double)matrix2.M34)&& ((double)this->M41 == (double)matrix2.M41 && (double)this->M42 == (double)matrix2.M42 && (double)this->M43 == (double)matrix2.M43)))
		return (double)this->M44 != (double)matrix2.M44;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator+( const Matrix& matrix2 ) const
{
	Matrix matrix;
	matrix.M11 = this->M11 + matrix2.M11; matrix.M12 = this->M12 + matrix2.M12; matrix.M13 = this->M13 + matrix2.M13; matrix.M14 = this->M14 + matrix2.M14;
	matrix.M21 = this->M21 + matrix2.M21; matrix.M22 = this->M22 + matrix2.M22; matrix.M23 = this->M23 + matrix2.M23; matrix.M24 = this->M24 + matrix2.M24;
	matrix.M31 = this->M31 + matrix2.M31; matrix.M32 = this->M32 + matrix2.M32; matrix.M33 = this->M33 + matrix2.M33; matrix.M34 = this->M34 + matrix2.M34;
	matrix.M41 = this->M41 + matrix2.M41; matrix.M42 = this->M42 + matrix2.M42; matrix.M43 = this->M43 + matrix2.M43; matrix.M44 = this->M44 + matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator-( const Matrix& matrix2 ) const
{
	Matrix matrix;
	matrix.M11 = this->M11 - matrix2.M11; matrix.M12 = this->M12 - matrix2.M12; matrix.M13 = this->M13 - matrix2.M13; matrix.M14 = this->M14 - matrix2.M14;
	matrix.M21 = this->M21 - matrix2.M21; matrix.M22 = this->M22 - matrix2.M22; matrix.M23 = this->M23 - matrix2.M23; matrix.M24 = this->M24 - matrix2.M24;
	matrix.M31 = this->M31 - matrix2.M31; matrix.M32 = this->M32 - matrix2.M32; matrix.M33 = this->M33 - matrix2.M33; matrix.M34 = this->M34 - matrix2.M34;
	matrix.M41 = this->M41 - matrix2.M41; matrix.M42 = this->M42 - matrix2.M42; matrix.M43 = this->M43 - matrix2.M43; matrix.M44 = this->M44 - matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator*( const Matrix& matrix2 ) const
{
	Matrix matrix;
	matrix.M11 = (float)((double)this->M11 * (double)matrix2.M11 + (double)this->M12 * (double)matrix2.M21 + (double)this->M13 * (double)matrix2.M31 + (double)this->M14 * (double)matrix2.M41);
	matrix.M12 = (float)((double)this->M11 * (double)matrix2.M12 + (double)this->M12 * (double)matrix2.M22 + (double)this->M13 * (double)matrix2.M32 + (double)this->M14 * (double)matrix2.M42);
	matrix.M13 = (float)((double)this->M11 * (double)matrix2.M13 + (double)this->M12 * (double)matrix2.M23 + (double)this->M13 * (double)matrix2.M33 + (double)this->M14 * (double)matrix2.M43);
	matrix.M14 = (float)((double)this->M11 * (double)matrix2.M14 + (double)this->M12 * (double)matrix2.M24 + (double)this->M13 * (double)matrix2.M34 + (double)this->M14 * (double)matrix2.M44);
	matrix.M21 = (float)((double)this->M21 * (double)matrix2.M11 + (double)this->M22 * (double)matrix2.M21 + (double)this->M23 * (double)matrix2.M31 + (double)this->M24 * (double)matrix2.M41);
	matrix.M22 = (float)((double)this->M21 * (double)matrix2.M12 + (double)this->M22 * (double)matrix2.M22 + (double)this->M23 * (double)matrix2.M32 + (double)this->M24 * (double)matrix2.M42);
	matrix.M23 = (float)((double)this->M21 * (double)matrix2.M13 + (double)this->M22 * (double)matrix2.M23 + (double)this->M23 * (double)matrix2.M33 + (double)this->M24 * (double)matrix2.M43);
	matrix.M24 = (float)((double)this->M21 * (double)matrix2.M14 + (double)this->M22 * (double)matrix2.M24 + (double)this->M23 * (double)matrix2.M34 + (double)this->M24 * (double)matrix2.M44);
	matrix.M31 = (float)((double)this->M31 * (double)matrix2.M11 + (double)this->M32 * (double)matrix2.M21 + (double)this->M33 * (double)matrix2.M31 + (double)this->M34 * (double)matrix2.M41);
	matrix.M32 = (float)((double)this->M31 * (double)matrix2.M12 + (double)this->M32 * (double)matrix2.M22 + (double)this->M33 * (double)matrix2.M32 + (double)this->M34 * (double)matrix2.M42);
	matrix.M33 = (float)((double)this->M31 * (double)matrix2.M13 + (double)this->M32 * (double)matrix2.M23 + (double)this->M33 * (double)matrix2.M33 + (double)this->M34 * (double)matrix2.M43);
	matrix.M34 = (float)((double)this->M31 * (double)matrix2.M14 + (double)this->M32 * (double)matrix2.M24 + (double)this->M33 * (double)matrix2.M34 + (double)this->M34 * (double)matrix2.M44);
	matrix.M41 = (float)((double)this->M41 * (double)matrix2.M11 + (double)this->M42 * (double)matrix2.M21 + (double)this->M43 * (double)matrix2.M31 + (double)this->M44 * (double)matrix2.M41);
	matrix.M42 = (float)((double)this->M41 * (double)matrix2.M12 + (double)this->M42 * (double)matrix2.M22 + (double)this->M43 * (double)matrix2.M32 + (double)this->M44 * (double)matrix2.M42);
	matrix.M43 = (float)((double)this->M41 * (double)matrix2.M13 + (double)this->M42 * (double)matrix2.M23 + (double)this->M43 * (double)matrix2.M33 + (double)this->M44 * (double)matrix2.M43);
	matrix.M44 = (float)((double)this->M41 * (double)matrix2.M14 + (double)this->M42 * (double)matrix2.M24 + (double)this->M43 * (double)matrix2.M34 + (double)this->M44 * (double)matrix2.M44);

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *
///@param scaleFactor : 값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator*( const float& scaleFactor ) const
{
	float num = scaleFactor;
	Matrix matrix1;

	matrix1.M11 = this->M11 * num; matrix1.M12 = this->M12 * num; matrix1.M13 = this->M13 * num; matrix1.M14 = this->M14 * num;
	matrix1.M21 = this->M21 * num; matrix1.M22 = this->M22 * num; matrix1.M23 = this->M23 * num; matrix1.M24 = this->M24 * num;
	matrix1.M31 = this->M31 * num; matrix1.M32 = this->M32 * num; matrix1.M33 = this->M33 * num; matrix1.M34 = this->M34 * num;
	matrix1.M41 = this->M41 * num; matrix1.M42 = this->M42 * num; matrix1.M43 = this->M43 * num; matrix1.M44 = this->M44 * num;

	return matrix1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator/( const Matrix& matrix2 ) const
{
	Matrix matrix;
	matrix.M11 = this->M11 / matrix2.M11; matrix.M12 = this->M12 / matrix2.M12; matrix.M13 = this->M13 / matrix2.M13; matrix.M14 = this->M14 / matrix2.M14;
	matrix.M21 = this->M21 / matrix2.M21; matrix.M22 = this->M22 / matrix2.M22; matrix.M23 = this->M23 / matrix2.M23; matrix.M24 = this->M24 / matrix2.M24;
	matrix.M31 = this->M31 / matrix2.M31; matrix.M32 = this->M32 / matrix2.M32; matrix.M33 = this->M33 / matrix2.M33; matrix.M34 = this->M34 / matrix2.M34;
	matrix.M41 = this->M41 / matrix2.M41; matrix.M42 = this->M42 / matrix2.M42; matrix.M43 = this->M43 / matrix2.M43; matrix.M44 = this->M44 / matrix2.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /
///@param divider : 값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::operator/( const float& divider ) const
{
	float num = 1.0f / divider;
	
	Matrix matrix;
	matrix.M11 = this->M11 * num; matrix.M12 = this->M12 * num; matrix.M13 = this->M13 * num; matrix.M14 = this->M14 * num;
	matrix.M21 = this->M21 * num; matrix.M22 = this->M22 * num; matrix.M23 = this->M23 * num; matrix.M24 = this->M24 * num;
	matrix.M31 = this->M31 * num; matrix.M32 = this->M32 * num; matrix.M33 = this->M33 * num; matrix.M34 = this->M34 * num;
	matrix.M41 = this->M41 * num; matrix.M42 = this->M42 * num; matrix.M43 = this->M43 * num; matrix.M44 = this->M44 * num;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief +=
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator+=( const Matrix& matrix2 )
{
	*this = *this + matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief -=
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator-=( const Matrix& matrix2 )
{
	*this = *this - matrix2;	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator*=( const Matrix& matrix2 )
{
	*this = *this * matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief *=
///@param scaleFactor : 값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator*=( const float& scaleFactor )
{
	*this = *this * scaleFactor;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param matrix2 : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator/=( const Matrix& matrix2 )
{
	*this = *this / matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief /=
///@param divider : 값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
void Matrix::operator/=( const float& divider )
{
	*this = *this / divider;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 문자열로 변환
///@return 문자열
//////////////////////////////////////////////////////////////////////////
std::string Matrix::ToString()
{
	std::string temp;
	char val[255];

	sprintf(val, "{ {M11:%#f ", M11); temp += val;
	sprintf(val, "M12:%#f ", M12); temp += val;
	sprintf(val, "M13:%#f ", M13); temp += val;
	sprintf(val, "M14:%#f} ", M14); temp += val;

	sprintf(val, "{M21:%#f ", M21); temp += val;
	sprintf(val, "M22:%#f ", M22); temp += val;
	sprintf(val, "M23:%#f ", M23); temp += val;
	sprintf(val, "M24:%#f} ", M24); temp += val;

	sprintf(val, "{321:%#f ", M31); temp += val;
	sprintf(val, "M32:%#f ", M32); temp += val;
	sprintf(val, "M33:%#f ", M33); temp += val;
	sprintf(val, "M34:%#f} ", M34); temp += val;

	sprintf(val, "{M41:%#f ", M41); temp += val;
	sprintf(val, "M42:%#f ", M42); temp += val;
	sprintf(val, "M43:%#f ", M43); temp += val;
	sprintf(val, "M44:%#f} }", M44); temp += val;

	return temp;	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief D3DXMATRIX로 변환
///@return D3DX 매트릭스 
//////////////////////////////////////////////////////////////////////////
D3DXMATRIX Matrix::ToD3DXMATRIX()
{
	D3DXMATRIX matrix;
	matrix._11 = this->M11; matrix._12 = this->M12; matrix._13 = this->M13; matrix._14 = this->M14;
	matrix._21 = this->M21; matrix._22 = this->M22; matrix._23 = this->M23; matrix._24 = this->M24;
	matrix._31 = this->M31; matrix._32 = this->M32; matrix._33 = this->M33; matrix._34 = this->M34;
	matrix._41 = this->M41; matrix._42 = this->M42; matrix._43 = this->M43; matrix._44 = this->M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 행렬식
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
float Matrix::Determinant()
{
	float num1 = (float)((double)M33 * (double)M44 - (double)M34 * (double)M43);
	float num2 = (float)((double)M32 * (double)M44 - (double)M34 * (double)M42);
	float num3 = (float)((double)M32 * (double)M43 - (double)M33 * (double)M42);
	float num4 = (float)((double)M31 * (double)M44 - (double)M34 * (double)M41);
	float num5 = (float)((double)M31 * (double)M43 - (double)M33 * (double)M41);
	float num6 = (float)((double)M31 * (double)M42 - (double)M32 * (double)M41);

	float temp = 
		(float)((double)M11 * ((double)M22 * (double)num1 - (double)M23 * (double)num2 + (double)M24 * (double)num3) - 
				(double)M12 * ((double)M21 * (double)num1 - (double)M23 * (double)num4 + (double)M24 * (double)num5) + 
				(double)M13 * ((double)M21 * (double)num2 - (double)M22 * (double)num4 + (double)M24 * (double)num6) - 
				(double)M14 * ((double)M21 * (double)num3 - (double)M22 * (double)num5 + (double)M23 * (double)num6));

	return temp;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 빌보드 매트릭스 생성
///@param objectPosition : 오브젝트 위치
///@param cameraPosition : 카메라 위치
///@param cameraUpVector : 카메라 업벡터
///@param cameraForwardVector : 카메라 포워드벡터
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateBillboard( Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector/*=NULL*/ )
{
	Vector3 forwardVec;
	forwardVec.X = objectPosition.X - cameraPosition.X;
	forwardVec.Y = objectPosition.Y - cameraPosition.Y;
	forwardVec.Z = objectPosition.Z - cameraPosition.Z;

	float num = forwardVec.LengthSquared();
	if ((double) num < 9.99999974737875E-05)
		forwardVec = cameraForwardVector != NULL ? -(*cameraForwardVector) : Vector3::Forward;
	else
		forwardVec = forwardVec * (1.0f / (float)sqrt((double)num));

	Vector3 rightVec;
	rightVec = Vector3::Cross(cameraUpVector, forwardVec);
	rightVec.Normalize();

	Vector3 upVec;
	upVec = Vector3::Cross(forwardVec, rightVec);
	
	Matrix matrix;
	matrix.M11 = rightVec.X;		matrix.M12 = rightVec.Y;		matrix.M13 = rightVec.Z;		matrix.M14 = 0.0f;
	matrix.M21 = upVec.X;			matrix.M22 = upVec.Y;			matrix.M23 = upVec.Z;			matrix.M24 = 0.0f;
	matrix.M31 = forwardVec.X;		matrix.M32 = forwardVec.Y;		matrix.M33 = forwardVec.Z;		matrix.M34 = 0.0f;
	matrix.M41 = objectPosition.X;	matrix.M42 = objectPosition.Y;	matrix.M43 = objectPosition.Z;	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 이동 매트릭스 생성
///@param position : 위치
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateTranslation( Vector3 position )
{
	Matrix matrix;
	matrix.M11 = 1.0f; matrix.M12 = 0.0f; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;
	
	matrix.M41 = position.X; 
	matrix.M42 = position.Y; 
	matrix.M43 = position.Z; 
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 이동 매트릭스 생성
///@param xPosition : x 위치
///@param yPosition : y 위치
///@param zPosition : z 위치
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateTranslation( float xPosition, float yPosition, float zPosition )
{
	Matrix matrix;
	matrix.M11 = 1.0f; matrix.M12 = 0.0f; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;
	
	matrix.M41 = xPosition;
	matrix.M42 = yPosition;
	matrix.M43 = zPosition;
	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 크기 매트릭스 생성
///@param scales : 크기
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale( Vector3 scales )
{	
	Matrix matrix;
	matrix.M11 = scales.X;	matrix.M12 = 0.0f;		matrix.M13 = 0.0f;		matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;		matrix.M22 = scales.Y;	matrix.M23 = 0.0f;		matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;		matrix.M32 = 0.0f;		matrix.M33 = scales.Z;	matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;		matrix.M42 = 0.0f;		matrix.M43 = 0.0f;		matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 크기 매트릭스 생성
///@param xScale : x 크기
///@param yScale : y 크기
///@param zScale : z 크기
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale( float xScale, float yScale, float zScale )
{
	Matrix matrix;
	matrix.M11 = xScale;	matrix.M12 = 0.0f;		matrix.M13 = 0.0f;		matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;		matrix.M22 = yScale;	matrix.M23 = 0.0f;		matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;		matrix.M32 = 0.0f;		matrix.M33 = zScale;	matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;		matrix.M42 = 0.0f;		matrix.M43 = 0.0f;		matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 크기 매트릭스 생성
///@param scale : 크기값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateScale( float scale )
{
	Matrix matrix;
	matrix.M11 = scale;	matrix.M12 = 0.0f;	matrix.M13 = 0.0f;	matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;	matrix.M22 = scale;	matrix.M23 = 0.0f;	matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;	matrix.M32 = 0.0f;	matrix.M33 = scale;	matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;	matrix.M42 = 0.0f;	matrix.M43 = 0.0f;	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief X축 회전 매트릭스 생성
///@param radians : 라디안 각도값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationX( float radians )
{
	float num1 = (float)cos((double) radians);
	float num2 = (float)sin((double) radians);
	
	Matrix matrix;
	matrix.M11 = 1.0f;	matrix.M12 = 0.0f;	matrix.M13 = 0.0f;	matrix.M14 = 0.0f;
	matrix.M21 = 0.0f;	matrix.M22 = num1;	matrix.M23 = num2;	matrix.M24 = 0.0f;
	matrix.M31 = 0.0f;	matrix.M32 = -num2;	matrix.M33 = num1;	matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;	matrix.M42 = 0.0f;	matrix.M43 = 0.0f;	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Y축 회전 매트릭스 생성
///@param radians : 라디안 각도값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationY( float radians )
{
	float num1 = (float)cos((double) radians);
	float num2 = (float)sin((double) radians);
	
	Matrix matrix;
	matrix.M11 = num1; matrix.M12 = 0.0f; matrix.M13 = -num2; matrix.M14 = 0.0f;
	matrix.M21 = 0.0f; matrix.M22 = 1.0f; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = num2; matrix.M32 = 0.0f; matrix.M33 = num1; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f; matrix.M43 = 0.0f; matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief Z축 회전 매트릭스 생성
///@param radians : 라디안 각도값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateRotationZ( float radians )
{
	float num1 = (float)cos((double) radians);
	float num2 = (float)sin((double) radians);
	
	Matrix matrix;
	matrix.M11 = num1; matrix.M12 = num2; matrix.M13 = 0.0f; matrix.M14 = 0.0f;
	matrix.M21 = -num2; matrix.M22 = num1; matrix.M23 = 0.0f; matrix.M24 = 0.0f;
	matrix.M31 = 0.0f; matrix.M32 = 0.0f; matrix.M33 = 1.0f; matrix.M34 = 0.0f;
	matrix.M41 = 0.0f; matrix.M42 = 0.0f; matrix.M43 = 0.0f; matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 축 벡터 회전 매트릭스 생성
///@param axis : 축
///@param angle : 회전값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromAxisAngle( Vector3 axis, float angle )
{
	float sinValue = (float)sin((double)angle);
	float cosValue = (float)cos((double)angle);

	float xx = axis.X * axis.X;
	float yy = axis.Y * axis.Y;
	float zz = axis.Z * axis.Z;

	float xy = axis.X * axis.Y;
	float xz = axis.X * axis.Z;
	float yz = axis.Y * axis.Z;

	Matrix matrix;
	matrix.M11 = xx + cosValue * (1.0f - xx);
	matrix.M12 = (float)((double)xy - (double)cosValue * (double)xy + (double)sinValue * (double)axis.Z);
	matrix.M13 = (float)((double)xz - (double)cosValue * (double)xz - (double)sinValue * (double)axis.Y);
	matrix.M14 = 0.0f;

	matrix.M21 = (float)((double)xy - (double)cosValue * (double)xy - (double)sinValue * (double)axis.Z);
	matrix.M22 = yy + cosValue * (1.0f - yy);
	matrix.M23 = (float)((double)yz - (double)cosValue * (double)yz + (double)sinValue * (double)axis.X);
	matrix.M24 = 0.0f;

	matrix.M31 = (float)((double)xz - (double)cosValue * (double)xz + (double)sinValue * (double)axis.Y);
	matrix.M32 = (float)((double)yz - (double)cosValue * (double)yz - (double)sinValue * (double)axis.X);
	matrix.M33 = zz + cosValue * (1.0f - zz);
	matrix.M34 = 0.0f;

	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 원근투영 매트릭스 생성
///@param width : 화면넓이
///@param height : 화면높이
///@param nearPlaneDistance : 근면거리
///@param farPlaneDistance : 원면거리
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreatePerspective( float width, float height, float nearPlaneDistance, float farPlaneDistance )
{
	assert((double)nearPlaneDistance > 0.0);
	assert((double)farPlaneDistance > 0.0);
	assert((double)nearPlaneDistance < (double)farPlaneDistance);

	Matrix matrix;
	matrix.M11 = 2.0f * nearPlaneDistance / width;
	matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;

	matrix.M22 = 2.0f * nearPlaneDistance / height;
	matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;

	matrix.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	matrix.M31 = matrix.M32 = 0.0f;
	matrix.M34 = -1.0f;

	matrix.M41 = matrix.M42 = matrix.M44 = 0.0f;
	matrix.M43 = (float)((double)nearPlaneDistance * (double)farPlaneDistance / ((double)nearPlaneDistance - (double)farPlaneDistance));

	return matrix;	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief FOV를 기준으로 원근투영 매트릭스 생성
///@param fieldOfView : FOV
///@param aspectRatio : 화면비율
///@param nearPlaneDistance : 근면거리
///@param farPlaneDistance : 원면거리
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreatePerspectiveFieldOfView( float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance )
{
	assert((double)fieldOfView > 0.0 || (double)fieldOfView < 3.14159274101257);
	assert((double)nearPlaneDistance > 0.0);
	assert((double)farPlaneDistance > 0.0);
	assert((double)nearPlaneDistance < (double)farPlaneDistance);
	
	float num1 = 1.0f / (float)tan((double)fieldOfView * 0.5);
	float num2 = num1 / aspectRatio;
	
	Matrix matrix;
	matrix.M11 = num2; 
	matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;
	
	matrix.M22 = num1; 
	matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;
	
	matrix.M31 = matrix.M32 = 0.0f;
	matrix.M33 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	matrix.M34 = -1.0f;
	
	matrix.M41 = matrix.M42 = matrix.M44 = 0.0f;
	matrix.M43 = (float)((double)nearPlaneDistance * (double)farPlaneDistance / ((double)nearPlaneDistance - (double)farPlaneDistance));
	
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 룩앳(뷰) 매트릭스 생성
///@param cameraPosition : 카메라 위치
///@param cameraTarget : 카메라 타켓
///@param cameraUpVector : 카메라 업벡터
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateLookAt( Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector )
{
	Vector3 vector3_1 = Vector3::Normalize(cameraPosition - cameraTarget);
	Vector3 vector3_2 = Vector3::Normalize(Vector3::Cross(cameraUpVector, vector3_1));
	Vector3 vector1 = Vector3::Cross(vector3_1, vector3_2);

	Matrix matrix;
	matrix.M11 = vector3_2.X; matrix.M12 = vector1.X; matrix.M13 = vector3_1.X; matrix.M14 = 0.0f;
	matrix.M21 = vector3_2.Y; matrix.M22 = vector1.Y; matrix.M23 = vector3_1.Y; matrix.M24 = 0.0f;
	matrix.M31 = vector3_2.Z; matrix.M32 = vector1.Z; matrix.M33 = vector3_1.Z; matrix.M34 = 0.0f;
	
	matrix.M41 = -Vector3::Dot(vector3_2, cameraPosition);
	matrix.M42 = -Vector3::Dot(vector1, cameraPosition);
	matrix.M43 = -Vector3::Dot(vector3_1, cameraPosition);
	matrix.M44 = 1.0f;
	
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 월드 매트릭스 생성
///@param position : 위치
///@param forward : 전방 방향
///@param up : 업
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateWorld( Vector3 position, Vector3 forward, Vector3 up )
{
	Vector3 vector3_1 = Vector3::Normalize(-forward);
	Vector3 vector2 = Vector3::Normalize(Vector3::Cross(up, vector3_1));
	Vector3 vector3_2 = Vector3::Cross(vector3_1, vector2);

	Matrix matrix;
	matrix.M11 = vector2.X; matrix.M12 = vector2.Y; matrix.M13 = vector2.Z; matrix.M14 = 0.0f;
	matrix.M21 = vector3_2.X; matrix.M22 = vector3_2.Y; matrix.M23 = vector3_2.Z; matrix.M24 = 0.0f;
	matrix.M31 = vector3_1.X; matrix.M32 = vector3_1.Y; matrix.M33 = vector3_1.Z; matrix.M34 = 0.0f;
	matrix.M41 = position.X; matrix.M42 = position.Y; matrix.M43 = position.Z; matrix.M44 = 1.0f;
	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 쿼터니온으로부터 매트릭스 생성
///@param quaternion : 쿼터니온
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromQuaternion( Quaternion quaternion )
{
	float xx = quaternion.X * quaternion.X;
	float yy = quaternion.Y * quaternion.Y;
	float zz = quaternion.Z * quaternion.Z;
	float xy = quaternion.X * quaternion.Y;
	float zw = quaternion.Z * quaternion.W;
	float zx = quaternion.Z * quaternion.X;
	float yw = quaternion.Y * quaternion.W;
	float yz = quaternion.Y * quaternion.Z;
	float xw = quaternion.X * quaternion.W;

	Matrix matrix;
	matrix.M11 = (float)(1.0 - 2.0 * ((double)yy + (double)zz));
	matrix.M12 = (float)(2.0 * ((double)xy + (double)zw));
	matrix.M13 = (float)(2.0 * ((double)zx - (double)yw));
	matrix.M14 = 0.0f;

	matrix.M21 = (float)(2.0 * ((double)xy - (double)zw));
	matrix.M22 = (float)(1.0 - 2.0 * ((double)zz + (double)xx));
	matrix.M23 = (float)(2.0 * ((double)yz + (double)xw));
	matrix.M24 = 0.0f;

	matrix.M31 = (float)(2.0 * ((double)zx + (double)yw));
	matrix.M32 = (float)(2.0 * ((double)yz - (double)xw));
	matrix.M33 = (float)(1.0 - 2.0 * ((double)yy + (double)xx));

	matrix.M34 = 0.0f;
	matrix.M41 = 0.0f;
	matrix.M42 = 0.0f;
	matrix.M43 = 0.0f;
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 각 축값에 의한 회전 매트릭스 생성(쿼터니온 이용)
///@param yaw : Yaw
///@param pitch : Pitch
///@param roll : Roll
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateFromYawPitchRoll( float yaw, float pitch, float roll )
{
	Quaternion result1;
	result1 = Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll);

	Matrix result2;
	result2 = CreateFromQuaternion(result1);

	return result2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 그림자 매트릭스 생성
///@param lightDirection : 빛 방향 벡터
///@param plane : 면
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateShadow( Vector3 lightDirection, Plane plane )
{
	Plane result = Plane::Normalize(plane);
	float length = (float)((double)result.Normal.X * (double)lightDirection.X + (double)result.Normal.Y * (double)lightDirection.Y + (double)result.Normal.Z * (double)lightDirection.Z);

	Matrix matrix;
	matrix.M11 = -result.Normal.X * lightDirection.X + length;
	matrix.M21 = -result.Normal.Y * lightDirection.X;
	matrix.M31 = -result.Normal.Z * lightDirection.X;
	matrix.M41 = -result.D * lightDirection.X;

	matrix.M12 = -result.Normal.X * lightDirection.Y;
	matrix.M22 = -result.Normal.Y * lightDirection.Y + length;
	matrix.M32 = -result.Normal.Z * lightDirection.Y;
	matrix.M42 = -result.D * lightDirection.Y;

	matrix.M13 = -result.Normal.X * lightDirection.Z;
	matrix.M23 = -result.Normal.Y * lightDirection.Z;
	matrix.M33 = -result.Normal.Z * lightDirection.Z + length;
	matrix.M43 = -result.D * lightDirection.Z;

	matrix.M14 = 0.0f;
	matrix.M24 = 0.0f;
	matrix.M34 = 0.0f;
	matrix.M44 = length;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 면의 반사 매트릭스 생성
///@param value : 면
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateReflection( Plane value )
{
	value.Normalize();

	Matrix matrix;
	matrix.M11 = (float)((double)(-2.0f * value.Normal.X)* (double)value.Normal.X + 1.0);
	matrix.M12 = (-2.0f * value.Normal.Y) * value.Normal.X;
	matrix.M13 = (-2.0f * value.Normal.Z) * value.Normal.X;
	matrix.M14 = 0.0f;

	matrix.M21 = (-2.0f * value.Normal.X) * value.Normal.Y;
	matrix.M22 = (float)((double)(-2.0f * value.Normal.Y)* (double)value.Normal.Y + 1.0);
	matrix.M23 = (-2.0f * value.Normal.Z) * value.Normal.Y;
	matrix.M24 = 0.0f;

	matrix.M31 = (-2.0f * value.Normal.X) * value.Normal.Z;
	matrix.M32 = (-2.0f * value.Normal.Y) * value.Normal.Z;
	matrix.M33 = (float)((double)(-2.0f * value.Normal.Z)* (double)value.Normal.Z + 1.0);
	matrix.M34 = 0.0f;

	matrix.M41 = (-2.0f * value.Normal.X) * value.D;
	matrix.M42 = (-2.0f * value.Normal.Y) * value.D;
	matrix.M43 = (-2.0f * value.Normal.Z) * value.D;
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정사도법에 의한 행렬 생성
///@param width : 넓이
///@param height : 높이
///@param zNearPlane : z방향 근면
///@param zFarPlane : z방향 원면
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::CreateOrthographic( float width, float height, float zNearPlane, float zFarPlane )
{
	Matrix matrix;
	matrix.M11 = 2.0f / width;
	matrix.M12 = matrix.M13 = matrix.M14 = 0.0f;
	matrix.M22 = 2.0f / height;
	matrix.M21 = matrix.M23 = matrix.M24 = 0.0f;
	matrix.M33 = (float) (1.0 / ((double) zNearPlane - (double) zFarPlane));
	matrix.M31 = matrix.M32 = matrix.M34 = 0.0f;
	matrix.M41 = matrix.M42 = 0.0f;
	matrix.M43 = zNearPlane / (zNearPlane - zFarPlane);
	matrix.M44 = 1.0f;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 쿼터니온에 의한 매트릭스 변환
///@param value : 매트릭스
///@param rotation : 쿼터니온
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::Transform( Matrix value, Quaternion rotation )
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

	Matrix matrix;
	matrix.M11 = (float)((double)value.M11 * (double)num1 + (double)value.M12 * (double)num2 + (double)value.M13 * (double)num3);
	matrix.M12 = (float)((double)value.M11 * (double)num4 + (double)value.M12 * (double)num5 + (double)value.M13 * (double)num6);
	matrix.M13 = (float)((double)value.M11 * (double)num7 + (double)value.M12 * (double)num8 + (double)value.M13 * (double)num9);
	matrix.M14 = value.M14;

	matrix.M21 = (float)((double)value.M21 * (double)num1 + (double)value.M22 * (double)num2 + (double)value.M23 * (double)num3);
	matrix.M22 = (float)((double)value.M21 * (double)num4 + (double)value.M22 * (double)num5 + (double)value.M23 * (double)num6);
	matrix.M23 = (float)((double)value.M21 * (double)num7 + (double)value.M22 * (double)num8 + (double)value.M23 * (double)num9);
	matrix.M24 = value.M24;

	matrix.M31 = (float)((double)value.M31 * (double)num1 + (double)value.M32 * (double)num2 + (double)value.M33 * (double)num3);
	matrix.M32 = (float)((double)value.M31 * (double)num4 + (double)value.M32 * (double)num5 + (double)value.M33 * (double)num6);
	matrix.M33 = (float)((double)value.M31 * (double)num7 + (double)value.M32 * (double)num8 + (double)value.M33 * (double)num9);
	matrix.M34 = value.M34;

	matrix.M41 = (float)((double)value.M41 * (double)num1 + (double)value.M42 * (double)num2 + (double)value.M43 * (double)num3);
	matrix.M42 = (float)((double)value.M41 * (double)num4 + (double)value.M42 * (double)num5 + (double)value.M43 * (double)num6);
	matrix.M43 = (float)((double)value.M41 * (double)num7 + (double)value.M42 * (double)num8 + (double)value.M43 * (double)num9);
	matrix.M44 = value.M44;

	return matrix;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 전치 매트릭스
///@param matrix : 행렬
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::Transpose( Matrix matrix )
{
	Matrix matrix1;
	matrix1.M11 = matrix.M11; matrix1.M12 = matrix.M21; matrix1.M13 = matrix.M31; matrix1.M14 = matrix.M41;
	matrix1.M21 = matrix.M12; matrix1.M22 = matrix.M22; matrix1.M23 = matrix.M32; matrix1.M24 = matrix.M42;
	matrix1.M31 = matrix.M13; matrix1.M32 = matrix.M23; matrix1.M33 = matrix.M33; matrix1.M34 = matrix.M43;
	matrix1.M41 = matrix.M14; matrix1.M42 = matrix.M24; matrix1.M43 = matrix.M34; matrix1.M44 = matrix.M44;
	
	return matrix1;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 역행렬
///@param matrix : 매트릭스
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::Invert( Matrix matrix )
{
	Matrix matrix2;
	float num5 = matrix.M11; float num4 = matrix.M12; float num3 = matrix.M13; float num2 = matrix.M14;
	float num9 = matrix.M21; float num8 = matrix.M22; float num7 = matrix.M23; float num6 = matrix.M24;
	float num17 = matrix.M31; float num16 = matrix.M32; float num15 = matrix.M33; float num14 = matrix.M34;
	float num13 = matrix.M41; float num12 = matrix.M42; float num11 = matrix.M43; float num10 = matrix.M44;

	float num23 = (num15 * num10) - (num14 * num11);
	float num22 = (num16 * num10) - (num14 * num12);
	float num21 = (num16 * num11) - (num15 * num12);
	float num20 = (num17 * num10) - (num14 * num13);
	float num19 = (num17 * num11) - (num15 * num13);
	float num18 = (num17 * num12) - (num16 * num13);
	float num39 = ((num8 * num23) - (num7 * num22)) + (num6 * num21);
	float num38 = -(((num9 * num23) - (num7 * num20)) + (num6 * num19));
	float num37 = ((num9 * num22) - (num8 * num20)) + (num6 * num18);
	float num36 = -(((num9 * num21) - (num8 * num19)) + (num7 * num18));
	float num = 1.0f / ((((num5 * num39) + (num4 * num38)) + (num3 * num37)) + (num2 * num36));

	matrix2.M11 = num39 * num;
	matrix2.M21 = num38 * num;
	matrix2.M31 = num37 * num;
	matrix2.M41 = num36 * num;

	matrix2.M12 = -(((num4 * num23) - (num3 * num22)) + (num2 * num21)) * num;
	matrix2.M22 = (((num5 * num23) - (num3 * num20)) + (num2 * num19)) * num;
	matrix2.M32 = -(((num5 * num22) - (num4 * num20)) + (num2 * num18)) * num;
	matrix2.M42 = (((num5 * num21) - (num4 * num19)) + (num3 * num18)) * num;

	float num35 = (num7 * num10) - (num6 * num11);
	float num34 = (num8 * num10) - (num6 * num12);
	float num33 = (num8 * num11) - (num7 * num12);
	float num32 = (num9 * num10) - (num6 * num13);
	float num31 = (num9 * num11) - (num7 * num13);
	float num30 = (num9 * num12) - (num8 * num13);

	matrix2.M13 = (((num4 * num35) - (num3 * num34)) + (num2 * num33)) * num;
	matrix2.M23 = -(((num5 * num35) - (num3 * num32)) + (num2 * num31)) * num;
	matrix2.M33 = (((num5 * num34) - (num4 * num32)) + (num2 * num30)) * num;
	matrix2.M43 = -(((num5 * num33) - (num4 * num31)) + (num3 * num30)) * num;

	float num29 = (num7 * num14) - (num6 * num15);
	float num28 = (num8 * num14) - (num6 * num16);
	float num27 = (num8 * num15) - (num7 * num16);
	float num26 = (num9 * num14) - (num6 * num17);
	float num25 = (num9 * num15) - (num7 * num17);
	float num24 = (num9 * num16) - (num8 * num17);

	matrix2.M14 = -(((num4 * num29) - (num3 * num28)) + (num2 * num27)) * num;
	matrix2.M24 = (((num5 * num29) - (num3 * num26)) + (num2 * num25)) * num;
	matrix2.M34 = -(((num5 * num28) - (num4 * num26)) + (num2 * num24)) * num;
	matrix2.M44 = (((num5 * num27) - (num4 * num25)) + (num3 * num24)) * num;

	return matrix2;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 두 매트릭스의 선형보간
///@param matrix1 : 매트릭스1
///@param matrix2 : 매트릭스2
///@param amount : 보간 값
///@return 결과 매트릭스
//////////////////////////////////////////////////////////////////////////
Matrix Matrix::Lerp( Matrix matrix1, Matrix matrix2, float amount )
{
	Matrix matrix;
	matrix.M11 = matrix1.M11 + (matrix2.M11 - matrix1.M11) * amount;
	matrix.M12 = matrix1.M12 + (matrix2.M12 - matrix1.M12) * amount;
	matrix.M13 = matrix1.M13 + (matrix2.M13 - matrix1.M13) * amount;
	matrix.M14 = matrix1.M14 + (matrix2.M14 - matrix1.M14) * amount;
	matrix.M21 = matrix1.M21 + (matrix2.M21 - matrix1.M21) * amount;
	matrix.M22 = matrix1.M22 + (matrix2.M22 - matrix1.M22) * amount;
	matrix.M23 = matrix1.M23 + (matrix2.M23 - matrix1.M23) * amount;
	matrix.M24 = matrix1.M24 + (matrix2.M24 - matrix1.M24) * amount;
	matrix.M31 = matrix1.M31 + (matrix2.M31 - matrix1.M31) * amount;
	matrix.M32 = matrix1.M32 + (matrix2.M32 - matrix1.M32) * amount;
	matrix.M33 = matrix1.M33 + (matrix2.M33 - matrix1.M33) * amount;
	matrix.M34 = matrix1.M34 + (matrix2.M34 - matrix1.M34) * amount;
	matrix.M41 = matrix1.M41 + (matrix2.M41 - matrix1.M41) * amount;
	matrix.M42 = matrix1.M42 + (matrix2.M42 - matrix1.M42) * amount;
	matrix.M43 = matrix1.M43 + (matrix2.M43 - matrix1.M43) * amount;
	matrix.M44 = matrix1.M44 + (matrix2.M44 - matrix1.M44) * amount;

	return matrix;
}