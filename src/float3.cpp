#include "stdafx.h"

#include "float3.h"

namespace uti
{

float3 operator-(float3 left, float3 right)
{
	float3 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	return result;
}

float3 operator+(float3 left, float3 right)
{
	float3 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	return result;
}

float3 operator*(float3 left, float3 right)
{
	float3 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	return result;
}

float3 operator*(float3 left, float right)
{
	float3 result;
	result.x = left.x * right;
	result.y = left.y * right;
	result.z = left.z * right;
	return result;
}

float3 operator*(float left, float3 right)
{
	float3 result;
	result.x = left * right.x;
	result.y = left * right.y;
	result.z = left * right.z;
	return result;
}

float3 operator/(float3 left, float3 right)
{
	float3 result;
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;
	return result;
}

float3 operator/(float3 left, float right)
{
	float3 result;
	result.x = left.x / right;
	result.y = left.y / right;
	result.z = left.z / right;
	return result;
}

float3 dot(float3 left, float3 right)
{
	float3 result;
	result.x = result.y = result.z =  left.x*right.x
								    + left.y*right.y 
								    + left.z*right.z;
	return result;
}

float3 cross(float3 left, float3 right)
{
	float3 result;
	result.x = left.y*right.z - left.z*right.y;
	result.y = left.x*right.z - left.z*right.x;
	result.z = left.x*right.y - left.y*right.x;
	return result;
}

float  len(float3 vec)
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

float3 norm(float3 vec)
{
	return vec / len(vec);
}

}
