#pragma once

#include "../../inc/types.h"

// uti::float3
// see types.h
//
// Defines vector math and utility functionality for float3
namespace uti
{
	float3 operator-(float3 left, float3 right);
	float3 operator+(float3 left, float3 right);
	float3 operator*(float3 left, float3 right);
	float3 operator/(float3 left, float3 right);

	float3 dot  (float3 left, float3 right);
	float3 cross(float3 left, float3 right);
}

