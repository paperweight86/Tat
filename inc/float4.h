#pragma once

#include "float4.h"

namespace uti
{
	TAT_DEF float4 operator-(const float4& left, const float4& right);
	TAT_DEF float4 operator+(const float4& left, const float4& right);
	TAT_DEF float4 operator*(const float4& left, const float4& right);
	TAT_DEF float4 operator/(const float4& left, const float4& right);

	TAT_DEF float4 dot(const float4& left, const float4& right);
	TAT_DEF float4 cross(const float4& left, const float4& right);
}
