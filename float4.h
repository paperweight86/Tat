#pragma once

#include "float4.h"

namespace uti
{
	float4 operator-(float4 left, float4 right);
	float4 operator+(float4 left, float4 right);
	float4 operator*(float4 left, float4 right);
	float4 operator/(float4 left, float4 right);

	float4 dot(float4 left, float4 right);
	float4 cross(float4 left, float4 right);
}
