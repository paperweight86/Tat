#pragma once

#include "types.h"

// uti::float3
// see types.h
//
// Defines vector math and utility functionality for float3
namespace uti
{
	TAT_DEF float2 operator-(float2 left, float2 right);
	TAT_DEF float2 operator+(float2 left, float2 right);
	TAT_DEF float2 operator*(float2 left, float2 right);
	TAT_DEF float2 operator*(float2 left, float right);
	TAT_DEF float2 operator/(float2 left, float2 right);
	TAT_DEF float2 operator/(float2 left, float right);

	TAT_DEF float2 dot(float2 left, float2 right);

	TAT_DEF float sqdist(float2 left, float2 right);
	TAT_DEF float	dist(float2 left, float2 right);
}

