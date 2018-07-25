#pragma once

#include "../Core/Vector3.h"

//////////////////////////////////////////////////////////////////////////
///@brief GJK �浹����
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

	Vector3 closestPoint; ///< ����� ��ġ ����
	
	Vector3 y[4];///< y�� ����
	float yLengthSq[4];///< y�� ���� ũ��
	
	Vector3 edges[4][4];///< �𼭸� ����
	float edgeLengthSq[4][4];///< �𼭸� ũ��
	
	float det[16][4];///< Determinant
	
	int simplexBits;///< ���÷��� ��Ʈ(max:15)
	float maxLengthSq;///< �������� ����� ũ�� �� ���� ū ��
};