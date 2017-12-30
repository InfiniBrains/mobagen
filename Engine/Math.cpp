#pragma once
#include "Math.h"
#include <cmath>

// https://graphics.stanford.edu/~seander/bithacks.html
uint32_t Math::ClosestPowerOfTwo(uint32_t v)
{
	//return pow(2, ceil(log(value) / log(2)));
    // compute the next highest power of 2 of 32-bit v

	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

double Math::GammaToLinearSpace(const double value)
{
	return pow(value, 2.2);
}

double Math::LinearToGammaSpace(double value)
{
	return pow(value, 1/2.2);
}
