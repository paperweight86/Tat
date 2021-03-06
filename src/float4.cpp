#include "stdafx.h"

#include "float4.h"

#include <smmintrin.h>

namespace uti
{
	float4 make_float4(float x, float y, float z, float h)
	{
		return _mm_set_ps(z, y, x, h);
	}

	float4 make_float4(float x)
	{
		return _mm_set_ps1(x);
	}

	float4 make_float4_ordered(float r0, float r1, float r2, float r3)
	{
		return _mm_set_ps(r3,r2,r1,r0);
	}

	float4 make_float4_zero()
	{
		return _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	}

	float get_x(float4 v)
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((1) << 6) | ((1) << 4) | ((1) << 2) | ((1)))));
	}

	float get_y(float4 v)
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((2) << 6) | ((2) << 4) | ((2) << 2) | ((2)))));
	}

	float get_z(float4 v)
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((3) << 6) | ((3) << 4) | ((3) << 2) | ((3)))));
	}

	float get_h(float4 v)
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((0) << 6) | ((0) << 4) | ((0) << 2) | ((0)))));
	}

	float get_r0(float4 v)
	{
		return _mm_cvtss_f32(_mm_shuffle_ps(v, v, (((0) << 6) | ((0) << 4) | ((0) << 2) | ((0)))));
	}

	float4 dot(const float4& left, const float4& right)
	{
		//#ifdef __SSE4_1__
		const int mask = 0xE << 4 | 0xF;
		float4 result = float4(_mm_dp_ps(left, right, mask));
		return result;
		/*#else
		//float4 result = make_float4(0.0f,0.0f,0.0f,1.0f);
		float4 r1 = _mm_mul_ps(left, right);
		float4 r2 = _mm_hadd_ps(r1, r1);
		float4 r3 = _mm_hadd_ps(r2, r2);
		//_mm_store_ss(&result, r3);
		return r3;
		#endif*/
	}

	float4 cross(const float4& left, const float4& right)
	{
		float x = get_y(left)*get_z(right) - get_z(left)*get_y(right);
		float y = get_z(left)*get_x(right) - get_x(left)*get_z(right);
		float z = get_x(left)*get_y(right) - get_y(left)*get_x(right);
		return make_float4(x,y,z);
	}

	float len(float4 vec)
	{
		return get_h(_mm_sqrt_ss(dot(vec,vec)));
	}

	float sqlen(float4 vec)
	{
		return get_h(dot(vec, vec));
	}

	float4 norm(float4 vec)
	{
		float len_vec = len(vec);
		if (len_vec == 0.0f)
			return vec;
		auto res = vec / len_vec;
		return make_float4(get_x(res), get_y(res), get_z(res));
	}
}

using namespace uti;

float4 operator-(const float4& left, const float4& right)
{
	auto res = _mm_sub_ps(left, right);
	return make_float4(get_x(res), get_y(res), get_z(res));
}

float4 operator+(const float4& left, const float4& right)
{
	return _mm_add_ps(left, right);
}

float4 operator*(const float4& left, const float4& right)
{
	return float4(_mm_mul_ps(left, right));
}

float4 operator*(float4 left, float right)
{
	return float4(_mm_mul_ps(left, _mm_set1_ps(right)));
}

float4 operator*(float left, float4 right)
{
	return float4(_mm_mul_ps(_mm_set1_ps(left), right));
}

float4 operator/(const float4& left, const float4& right)
{
	return float4(_mm_div_ps(left, right));
}

float4 operator/(float4 left, float right)
{
	return float4(_mm_div_ps(left, _mm_set1_ps(right)));
}

