#include "stdafx.h"

#include "float4.h"

namespace uti
{
	float4 operator-(const float4& left, const float4& right)
	{
		float4 result;
		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
		return result;
	}

	float4 operator+(const float4& left, const float4& right)
	{
		float4 result;
		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;
		return result;
	}

	float4 operator*(const float4& left, const float4& right)
	{
		return float4(_mm_mul_ps(left.v, right.v));
	}

	float4 operator*(float4 left, float right)
	{
		return float4(_mm_mul_ps(left.v, _mm_set1_ps(right)));
	}

	float4 operator*(float left, float4 right)
	{
		return float4(_mm_mul_ps(_mm_set1_ps(left), right.v));
	}

	float4 operator/(const float4& left, const float4& right)
	{
		return float4(_mm_div_ps(left.v, right.v));
	}

	float4 operator/(float4 left, float right)
	{
		return float4(_mm_div_ps(left.v, _mm_set1_ps(right)));
	}

	float4 dot(const float4& left, const float4& right)
	{
		//const int mask = (0xF >> 1 << 4) | (0xF >> 1);
		const int mask = 0xE << 4 | 0xE;
		float4 result = float4(_mm_dp_ps(left.v, right.v, mask));
		return result;
	}

	float4 cross(const float4& left, const float4& right)
	{
		float4 result;
		result.x = left.y*right.z - left.z*right.y;
		result.y = left.x*right.z - left.z*right.x;
		result.z = left.x*right.y - left.y*right.x;
		return result;
	}

	float len(float4 vec)
	{
		return sqrtf(dot(vec,vec).get_x());
	}

	float4 norm(float4 vec)
	{
		return vec / len(vec);
	}
}
