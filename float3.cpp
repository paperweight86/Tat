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

float3 operator/(float3 left, float3 right)
{
	float3 result;
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;
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

}
