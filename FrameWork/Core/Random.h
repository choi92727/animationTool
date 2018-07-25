#pragma once

#include <wtypes.h>

//////////////////////////////////////////////////////////////////////////
///@brief ���� �߻�(Knuth's Subtractive Method)
//////////////////////////////////////////////////////////////////////////
class Random
{
public:
	Random(void);
	Random(int seed);
	~Random(void);

	virtual int Next();
	virtual int Next(int minValue, int maxValue);
	virtual int Next(int maxValue);
	
	virtual double NextDouble();
	virtual void NextBytes(BYTE* buffer, UINT size);

protected:
	virtual double Sample();
	
private:
	void BuildSeed(int seed);

	int InternalSample();
	double GetSampleForLargeRange();

	int next;///< �����õ�
	int nextP;///< �����õ� ����

	int seedArray[56];///< �õ尪�� ������ �迭

	const static int MaxBig;
	const static int MaxSeed;
};