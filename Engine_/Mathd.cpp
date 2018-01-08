#pragma once
#include "Mathd.h"


// https://graphics.stanford.edu/~seander/bithacks.html
uint32_t Mathd::ClosestPowerOfTwo(uint32_t v)
{
	// todo: create funtion for the closest, instead of the next
	return pow(2, ceil(log(v) / log(2)));
    // compute the next highest power of 2 of 32-bit v
}

uint32_t Mathd::NextPowerOfTwo(uint32_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

bool Mathd::IsPowerOfTwo(uint32_t value)
{
	return value == ClosestPowerOfTwo(value);
}

double Mathd::PerlinNoise(double x, double y)
{
	//todo: implement this
	return 0;
}

int16_t Mathd::FloatToHalf(float val)
{
	return static_cast<int16_t>(val);
}

float Mathd::HalfToFloat(int16_t val)
{
	return static_cast<float>(val);
}

float Mathd::Sin(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(sin(static_cast<double>(f)));
}

float Mathd::Cos(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(cos(static_cast<double>(f)));
}

float Mathd::Tan(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(tan(static_cast<double>(f)));
}

float Mathd::Asin(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(asin(static_cast<double>(f)));
}

float Mathd::Acos(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(acos(static_cast<double>(f)));
}

float Mathd::Atan(float f)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(atan(static_cast<double>(f)));
}

float Mathd::Atan2(float y, float x)
{
	// todo: use a double version (?)
	// todo: implement deterministic math!!
	return static_cast<float>(atan2(static_cast<double>(y), static_cast<double>(x)));
}

float Mathd::Sqrt(float f)
{
	return static_cast<float>(sqrt(static_cast<double>(f)));
}

float Mathd::Abs(float f)
{
	return fabs(f);
}

int32_t Mathd::Abs(int32_t value)
{
	return abs(value);
}

double Mathd::Min(double a, double b)
{
	return a >= b ? b : a;
}

double Mathd::Min(std::vector<double> values)
{
	const auto length = values.size();
	if (length == 0)
		return 0.0f;
	double num = values[0];
	for (int index = 1; index < length; ++index)
	{
		if (values[index] < num)
			num = values[index];
	}
	return num;
}

int Mathd::Min(int a, int b)
{
	return a >= b ? b : a;
}

int32_t Mathd::Min(std::vector<int32_t> values)
{
	const int length = values.size();
	if (length == 0)
		return 0;
	int num = values[0];
	for (int index = 1; index < length; ++index)
	{
		if (values[index] < num)
			num = values[index];
	}
	return num;
}

double Mathd::Max(double a, double b)
{
	return a <= b ? b : a;
}

double Mathd::Max(std::vector<double> values)
{
	const auto length = values.size();
	if (length == 0)
		return 0.0f;
	double num = values[0];
	for (int index = 1; index < length; ++index)
	{
		if (values[index] > num)
			num = values[index];
	}
	return num;
}

int32_t Mathd::Max(int32_t a, int32_t b)
{
	return a <= b ? b : a;
}

int32_t Mathd::Max(std::vector<int32_t> values)
{
	const auto length = values.size();
	if (length == 0)
		return 0.0f;
	double num = values[0];
	for (int index = 1; index < length; ++index)
	{
		if (values[index] > num)
			num = values[index];
	}
	return num;
}

double Mathd::Pow(double f, double p)
{
	return pow(f, p);
}

