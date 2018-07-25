#pragma once

#include "../Core/Vector3.h"

//////////////////////////////////////////////////////////////////////////
///@brief GJK 충돌검출
//////////////////////////////////////////////////////////////////////////
class Gjk
{
public:
	Gjk(void);

	bool FullSimplex() const;
	float MaxLengthSquared() const;
	Vector3 ClosestPoint() const;

	void Reset();

	bool AddSupportPoint(Vector3 newPoint);

private:
	void UpdateDeterminant(int index);
	bool UpdateSimplex(int newIndex);
	Vector3 ComputeClosestPoint();
	bool IsSatisfiesRule(int xBits, int yBits);

	static float Dot(Vector3 a, Vector3 b);

private:
	const static int BitsToIndices[16];

	Vector3 closestPoint; ///< 가까운 위치 벡터
	
	Vector3 y[4];///< y축 벡터
	float yLengthSq[4];///< y축 방향 크기
	
	Vector3 edges[4][4];///< 모서리 벡터
	float edgeLengthSq[4][4];///< 모서리 크기
	
	float det[16][4];///< Determinant
	
	int simplexBits;///< 심플렉스 비트(max:15)
	float maxLengthSq;///< 제곱으로 계산한 크기 중 가장 큰 값
};