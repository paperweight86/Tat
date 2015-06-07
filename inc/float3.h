#pragma once

#include "types.h"

// uti::float3
// see types.h
//
// Defines vector math and utility functionality for float3
namespace uti
{
	TAT_DEF float3 operator-(float3 left, float3 right);
	TAT_DEF float3 operator+(float3 left, float3 right);
	TAT_DEF float3 operator*(float3 left, float3 right);
	TAT_DEF float3 operator/(float3 left, float3 right);

	TAT_DEF float3 dot  (float3 left, float3 right);
	TAT_DEF float3 cross(float3 left, float3 right);
}

