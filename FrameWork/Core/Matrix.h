#pragma once

#include <string>
#pragma warning( disable : 4996)

struct D3DXMATRIX;
class Vector3;
class Quaternion;
class Plane;

//////////////////////////////////////////////////////////////////////////
///@brief 행렬
//////////////////////////////////////////////////////////////////////////
class Matrix
{
public:
	Matrix(void);
	Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	Vector3 Up();			void Up(Vector3 value);
	Vector3 Down();			void Down(Vector3 value);
	Vector3 Right();		void Right(Vector3 value);
	Vector3 Left();			void Left(Vector3 value);
	Vector3 Forward();		void Forward(Vector3 value);
	Vector3 Backward();		void Backward(Vector3 value);
	Vector3 Translate();	void Translate(Vector3 value);

	Matrix operator -();

	bool operator ==(const Matrix& matrix2) const;
	bool operator !=(const Matrix& matrix2) const;

	Matrix operator +(const Matrix& matrix2) const;
	Matrix operator -(const Matrix& matrix2) const;
	Matrix operator *(const Matrix& matrix2) const;
	Matrix operator *(const float& scaleFactor) const;
	Matrix operator /(const Matrix& matrix2) const;
	Matrix operator /(const float& divider) const;

	void operator +=(const Matrix& matrix2);
	void operator -=(const Matrix& matrix2);
	void operator *=(const Matrix& matrix2);
	void operator *=(const float& scaleFactor);
	void operator /=(const Matrix& matrix2);
	void operator /=(const float& divider);

	//////////////////////////////////////////////////////////////////////////
	///@brief float형의 *연산 처리
	///@param scalefactor : 값
	///@param matrix2 : 매트릭스
	///@return 결과 매트릭스
	//////////////////////////////////////////////////////////////////////////
	friend Matrix operator *(const float scaleFactor, const Matrix& matrix2)
	{
		return matrix2 * scaleFactor;
	}
	//////////////////////////////////////////////////////////////////////////

	std::string ToString();
	D3DXMATRIX ToD3DXMATRIX();

	float Determinant();

	static Matrix CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Vector3* cameraForwardVector=NULL);
	
	static Matrix CreateTranslation(Vector3 position);
	static Matrix CreateTranslation(float xPosition, float yPosition, float zPosition);
	
	static Matrix CreateScale(Vector3 scales);
	static Matrix CreateScale(float xScale, float yScale, float zScale);
	static Matrix CreateScale(float scale);

	static Matrix CreateRotationX(float radians);
	static Matrix CreateRotationY(float radians);
	static Matrix CreateRotationZ(float radians);
	static Matrix CreateFromAxisAngle(Vector3 axis, float angle);

	static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

	static Matrix CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);
	static Matrix CreateWorld(Vector3 position, Vector3 forward, Vector3 up);
	static Matrix CreateFromQuaternion(Quaternion quaternion);
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static Matrix CreateShadow(Vector3 lightDirection, Plane plane);
	static Matrix CreateReflection(Plane value);
	static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);

	static Matrix Transform(Matrix value, Quaternion rotation);
	static Matrix Transpose(Matrix matrix);
	static Matrix Invert(Matrix matrix);
	static Matrix Lerp(Matrix matrix1, Matrix matrix2, float amount);	

public:
	const static Matrix Identity;

	float M11;
	float M12;
	float M13;
	float M14;

	float M21;
	float M22;
	float M23;
	float M24;

	float M31;
	float M32;
	float M33;
	float M34;

	float M41;
	float M42;
	float M43;
	float M44;
};