#include "Random.h"

#include <assert.h>
#include "MathHelper.h"
//#include "../Framework.h"

//////////////////////////////////////////////////////////////////////////

const int Random::MaxBig = 2147483647;
const int Random::MaxSeed = 161803398;

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
//////////////////////////////////////////////////////////////////////////
Random::Random( void )
{
	this->next = 0;
	this->nextP = 21;

	BuildSeed((int)GetTickCount());
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 생성자
///@param 시드의 시작 절대값
//////////////////////////////////////////////////////////////////////////
Random::Random( int seed )
{
	this->next = 0;
	this->nextP = 21;

	BuildSeed(seed);	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 소멸자
//////////////////////////////////////////////////////////////////////////
Random::~Random( void )
{
	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 내부 샘플링
///@return 난수
//////////////////////////////////////////////////////////////////////////
int Random::InternalSample()
{
	int index1 = next + 1 >= 56 ? 1 : next + 1;
	int index2 = nextP + 1 >= 56 ? 1 : nextP + 1;
	
	int value = seedArray[index1] - seedArray[index2];
	if(value == MathHelper::IntMaxValue) 
		--value;

	if (value < 0) 
		value += MathHelper::IntMaxValue;

	seedArray[index1] = value;
	next = index1;
	nextP = index2;

	return value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 더블형에서 큰 범위내로 샘플링
///@return 더블형의 난수
///@see 난수 발생요구시 정수형의 범위를 벋어날때 호출된다.
//////////////////////////////////////////////////////////////////////////
double Random::GetSampleForLargeRange()
{
	int temp = InternalSample();

	if(InternalSample() % 2 == 0 && true)
		temp = -temp;

	return ((double)temp + 2147483646.0) / 4294967293.0;	
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 배정도실수 샘플링
//////////////////////////////////////////////////////////////////////////
double Random::Sample()
{
	return (double)InternalSample() * 4.6566128752458E-10;//Double Elipson
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정수형 난수 발생
///@return 난수 
//////////////////////////////////////////////////////////////////////////
int Random::Next()
{
	return InternalSample();
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정수형 난수 발생
///@param minValue : 최소값
///@param maxValue : 최대값
///@return 난수 
//////////////////////////////////////////////////////////////////////////
int Random::Next( int minValue, int maxValue )
{
	assert(minValue < maxValue);
	
	long temp = (long)maxValue - (long)minValue;
	if (temp <= (long)MathHelper::IntMaxValue)
		return (int)(Sample() * (double)temp) + minValue;
	else
		return (int)((long)(GetSampleForLargeRange() * (double)temp) + (long)minValue);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 정수형 난수 발생
///@param maxValue : 최대값
///@return 난수 
//////////////////////////////////////////////////////////////////////////
int Random::Next( int maxValue )
{
	assert(maxValue >= 0);

	return (int)(Sample() * (double)maxValue);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 더블형 난수 발생
///@return 난수
//////////////////////////////////////////////////////////////////////////
double Random::NextDouble()
{
	return Sample();
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 배열 사이즈만큼 난수를 자동으로 생성
///@param buffer : 배열
///@param size : 사이즈
//////////////////////////////////////////////////////////////////////////
void Random::NextBytes( BYTE* buffer, UINT size )
{
	assert(buffer != NULL);
	assert(size > 0);

	for(UINT index = 0; index < size; ++index)
		buffer[index] = (byte)(InternalSample() % 256);
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///@brief 시드 빌드
///@param seed : 시드
//////////////////////////////////////////////////////////////////////////
void Random::BuildSeed( int seed )
{
	int seedValue = 161803398 - (seed == MathHelper::IntMaxValue ? MathHelper::IntMaxValue : MathHelper::Abs(seed));
	seedArray[55] = seedValue;

	int temp = 1;
	for (int i = 1; i < 55; ++i)
	{
		int j = 21 * i % 55;
		seedArray[j] = temp;

		temp = seedValue - temp;
		if (temp < 0)
			temp += MathHelper::IntMaxValue;
		seedValue = seedArray[j];
	}

	for(int i = 1; i < 5; ++i)
	{
		for(int j = 1; j < 56; ++j)
		{
			seedArray[j] -= seedArray[1 + (j + 30) % 55];
			if(seedArray[j] < 0)
				seedArray[j] += MathHelper::IntMaxValue;
		}
	}

	next = 0;
	nextP = 21;
	seed = 1;	
}