#pragma once

class Vector3;

//////////////////////////////////////////////////////////////////////////
///@brief ���а���
//////////////////////////////////////////////////////////////////////////
class MathHelper
{
public:
	MathHelper(void);	

	static double Round(double value);
	static double Round(double value, int position);

	static int Abs(int value);
	static float Abs(float value);
	static double Abs(double value);

	static float ToRadians(float degrees);
	static float ToDegrees(float radians);
	static float Distance(float value1, float value2);

	static float Min(float value1, float value2);
	static float Max(float value1, float value2);
	static float Clamp(float value, float min, float max);
	
	static float Lerp(float value1, float value2, float amount);
	static float SmoothStep(float value1, float value2, float amount);
	static float CatmullRom(float value1, float value2, float value3, float value4, float amount);
	static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
	static float WrapAngle(float angle);

	static float AngleOfInclineY(Vector3 value);

public:
	const static float E;///< �ڿ��α��� �ؼ�
	const static float Log2E;///< �ڿ��α��� �ؼ� 2
	const static float Log10E;///< �ڿ��α��� �ؼ� 10
	const static float Pi;///< PI
	const static float TwoPi;///< PI * 2
	const static float PiOver2;///< PI / 2
	const static float PiOver4;///< PI / 4
	const static float Epsilon;///< 0.000001f

	const static int IntMinValue;///< Int���� �ּҰ�
	const static int IntMaxValue;///< Int���� �ִ밪
	const static float FloatMinValue;///< Flaot���� �ּҰ�
	const static float FloatMaxValue;///< Float���� �ִ밪
};