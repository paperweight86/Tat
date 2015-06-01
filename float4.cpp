#include "stdafx.h"

#include "float4.h"
#include "types.h"

namespace uti
{
	float4 operator-(float4 left, float4 right)
	{
		float4 result;
		result.x = left.x - right.x;
		result.y = left.y - right.y;
		result.z = left.z - right.z;
		return result;
	}

	float4 operator+(float4 left, float4 right)
	{
		float4 result;
		result.x = left.x + right.x;
		result.y = left.y + right.y;
		result.z = left.z + right.z;
		return result;
	}

	float4 operator*(float4 left, float4 right)
	{
		float4 result;
		result.x = left.x * right.x;
		result.y = left.y * right.y;
		result.z = left.z * right.z;
		return result;
	}

	float4 operator/(float4 left, float4 right)
	{
		float4 result;
		result.x = left.x / right.x;
		result.y = left.y / right.y;
		result.z = left.z / right.z;
		return result;
	}

	float4 dot(float4 left, float4 right)
	{
		float4 result;
		result.x = result.y = result.z = left.x*right.x
			+ left.y*right.y
			+ left.z*right.z;
		return result;
	}

	float4 cross(float4 left, float4 right)
	{
		float4 result;
		result.x = left.y*right.z - left.z*right.y;
		result.y = left.x*right.z - left.z*right.x;
		result.z = left.x*right.y - left.y*right.x;
		return result;
	}

}
