#include "stdafx.h"

#include "float2.h"

namespace uti
{

float2 operator-(float2 left, float2 right)
{
	float2 result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return result;
}

float2 operator+(float2 left, float2 right)
{
	float2 result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return result;
}

float2 operator*(float2 left, float2 right)
{
	float2 result;
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return result;
}

float2 operator/(float2 left, float2 right)
{
	float2 result;
	result.x = left.x / right.x;
	result.y = left.y / right.y;
	return result;
}

float2 operator/(float2 left, float right)
{
	float2 result;
	result.x = left.x / right;
	result.y = left.y / right;
	return result;
}

float2 dot(float2 left, float2 right)
{
	float2 result;
	result.x = result.y =  left.x*right.x
					     + left.y*right.y;
	return result;
}

float sqdist(float2 left, float2 right)
{
	return powf(left.x - right.x, 2.0f) + powf(left.y - right.y, 2.0f);
}

float dist(float2 left, float2 right)
{
	return sqrt(sqdist(left, right));
}

}
