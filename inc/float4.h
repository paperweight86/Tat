#pragma once

#include "float4.h"

namespace uti
{
	TAT_DEF float4 operator-(const float4& left, const float4& right);
	TAT_DEF float4 operator+(const float4& left, const float4& right);
	TAT_DEF float4 operator*(const float4& left, const float4& right);
	TAT_DEF float4 operator*(float4 left, float right);
	TAT_DEF float4 operator*(float left, float4 right);
	TAT_DEF float4 operator/(const float4& left, const float4& right);
	TAT_DEF float4 operator/(float4 left, float right);

	TAT_DEF float4 dot(const float4& left, const float4& right);
	TAT_DEF float4 cross(const float4& left, const float4& right);

	TAT_DEF float  len(float4 vec);
	TAT_DEF float4 norm(float4 vec);
}
