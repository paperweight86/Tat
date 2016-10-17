#include "stdafx.h"

#include "float44.h"
#include "float4.h"

using namespace uti;

float44 uti::make(float4 c0, float4 c1, float4 c2, float4 c3)
{
	float44 res = {};
	res.m[0]  = get_x(c0);
	res.m[1]  = get_x(c1);
	res.m[2]  = get_x(c2);
	res.m[3]  = get_x(c3);
	res.m[4]  = get_y(c0);
	res.m[5]  = get_y(c1);
	res.m[6]  = get_y(c2);
	res.m[7]  = get_y(c3);
	res.m[8]  = get_z(c0);
	res.m[9]  = get_z(c1);
	res.m[10] = get_z(c2);
	res.m[11] = get_z(c3);
	res.m[12] = get_h(c0);
	res.m[13] = get_h(c1);
	res.m[14] = get_h(c2);
	res.m[15] = get_h(c3);
	return res;
}

float44 uti::make(float* values, uti::u32 num_values)
{
	assert(num_values > 0 && num_values <= 16);
	float44 mat = {};
	for (int i = 0; i < num_values; i++)
		mat.m[i] = values[i];
	return mat;
}

float44 uti::make_identity()
{
	float44 res = {};

	res.m[0 ] = 1.0f;
	res.m[5 ] = 1.0f;
	res.m[10] = 1.0f;
	res.m[15] = 1.0f;

	return res;
}

float44 uti::make_scale(float scale)
{
	return make_scale(scale, scale, scale);
}

float44 uti::make_scale(float xs, float ys, float zs)
{
	float44 res = {};
	res.m[0 ] = xs;
	res.m[5 ] = ys;
	res.m[10] = zs;
	res.m[15] = 1.0f;
	return res;
}

float44 uti::make_rotate_x(float rads)
{
	float44 res = make_identity();
	res.m[5] = cos(rads); res.m[9 ] = -sin(rads);
	res.m[6] = sin(rads); res.m[10] =  cos(rads);
	return res;
}

float44 uti::make_rotate_y(float rads)
{
	float44 res = make_identity();
	res.m[0] =  cos(rads); res.m[8 ] = sin(rads);
	res.m[2] = -sin(rads); res.m[10] = cos(rads);
	return res;
}

float44 uti::make_rotate_z(float rads)
{
	float44 res = make_identity();
	res.m[0] = cos(rads); res.m[4] = -sin(rads);
	res.m[1] = sin(rads); res.m[5] =  cos(rads);
	return res;
}

float44 uti::make_translate(float4 offset)
{
	return make_translate( get_x(offset), get_y(offset), get_z(offset));
}

float44 uti::make_translate(float xt, float yt, float zt)
{
	float44 res = make_identity();
	res.m[12] = xt;
	res.m[13] = yt;
	res.m[14] = zt;
	return res;
}

float44 uti::make_look_at(const float4& pos, const float4& at, const float4& up)
{
	//float4 up = norm(cross(pos, at));
	float4 zaxis = norm(pos - at);
	float4 xaxis = norm(cross(up, zaxis));
	float4 yaxis = norm(cross(zaxis, xaxis));

	//float44 res = make(xaxis, yaxis, zaxis, make(0.0f, 0.0f, 0.0f, 1.0f));

	//res.m[3]  = get_x(-1.0f * dot(xaxis, pos));
	//res.m[7]  = get_x(-1.0f * dot(yaxis, pos));
	//res.m[11] = get_x(-1.0f * dot(zaxis, pos));

	float44 res = { get_x(xaxis), get_x(yaxis), get_x(zaxis), 0.0f,
					get_y(xaxis), get_y(yaxis), get_y(zaxis), 0.0f,
					get_z(xaxis), get_z(yaxis), get_z(zaxis), 0.0f,
					-1.0f * get_x(dot(xaxis, pos)), -1.0f * get_x(dot(yaxis, pos)),	-1.0f * get_x(dot(zaxis, pos)),	1.0f};

	return res;
}

float44 uti::make_transposed(const float44& o)
{
	return float44{ o.m[0],o.m[4],o.m[8],o.m[12],
					o.m[1],o.m[5],o.m[9],o.m[13], 
					o.m[2],o.m[6],o.m[10],o.m[14], 
					o.m[3],o.m[7],o.m[11],o.m[15],};
}

float44 uti::make_projection(float aspect, float min_dist, float max_dist, float hfov)
{
	float44 res = make_identity();
	res.m[0] = 1.0f / (aspect * tanf(hfov * 0.5));
	res.m[5] = 1.0f / tanf(hfov * 0.5);
	res.m[10] = -((max_dist+min_dist)/(max_dist - min_dist));
	res.m[14] = -(2.0f * max_dist * min_dist / (max_dist - min_dist));
	res.m[11] = -1.0f;

	return res;
}

float44 uti::mul(float44 left, float44 right)
{
	/*
	Column Matrix
		  L				 R
	|0  4  8  12|   |0  4  8  12| 
	|1  5  9  13| x |1  5  9  13| 
	|2  6  10 14|   |2  6  10 14| 
	|3  7  11 15|   |3  7  11 15|
	
	0 = L0xR0+L4xR1+L8xR2+L12xR3
	1 = L1xrR0+L5R1+L9xR3+L13

	|0  4  8  12|
	|1  5  9  13|
	|2  6  10 14|
	|3  7  11 15|

	*/
	float44 res = {};
	
	// TODO: [DanJ] Broken it looks like the 1st left column should be taken and multiplied against each row of the right instead of vice versa?

	res.m[0] = left.m[0] * right.m[0] + left.m[4] * right.m[1] + left.m[8] *  right.m[2] + left.m[12] * right.m[3];
	res.m[1] = left.m[1] * right.m[0] + left.m[5] * right.m[1] + left.m[9] *  right.m[2] + left.m[13] * right.m[3];
	res.m[2] = left.m[2] * right.m[0] + left.m[6] * right.m[1] + left.m[10] * right.m[2] + left.m[14] * right.m[3];
	res.m[3] = left.m[3] * right.m[0] + left.m[7] * right.m[1] + left.m[11] * right.m[2] + left.m[15] * right.m[3];

	res.m[4] = left.m[0] * right.m[4] + left.m[4] * right.m[5] + left.m[8] *  right.m[6] + left.m[12] * right.m[7];
	res.m[5] = left.m[1] * right.m[4] + left.m[5] * right.m[5] + left.m[9] *  right.m[6] + left.m[13] * right.m[7];
	res.m[6] = left.m[2] * right.m[4] + left.m[6] * right.m[5] + left.m[10] * right.m[6] + left.m[14] * right.m[7];
	res.m[7] = left.m[3] * right.m[4] + left.m[7] * right.m[5] + left.m[11] * right.m[6] + left.m[15] * right.m[7];

	res.m[8]  = left.m[0] * right.m[8] + left.m[4] * right.m[9] + left.m[8] *  right.m[10] + left.m[12] * right.m[11];
	res.m[9]  = left.m[1] * right.m[8] + left.m[5] * right.m[9] + left.m[9] *  right.m[10] + left.m[13] * right.m[11];
	res.m[10] = left.m[2] * right.m[8] + left.m[6] * right.m[9] + left.m[10] * right.m[10] + left.m[14] * right.m[11];
	res.m[11] = left.m[3] * right.m[8] + left.m[7] * right.m[9] + left.m[11] * right.m[10] + left.m[15] * right.m[11];

	res.m[12] = left.m[0] * right.m[12] + left.m[4] * right.m[13] + left.m[8]  * right.m[14] + left.m[12] * right.m[15];
	res.m[13] = left.m[1] * right.m[12] + left.m[5] * right.m[13] + left.m[9]  * right.m[14] + left.m[13] * right.m[15];
	res.m[14] = left.m[2] * right.m[12] + left.m[6] * right.m[13] + left.m[10] * right.m[14] + left.m[14] * right.m[15];
	res.m[15] = left.m[3] * right.m[12] + left.m[7] * right.m[13] + left.m[11] * right.m[14] + left.m[15] * right.m[15];

	return res;
}

float4 uti::mul(float4 left, float44 right)
{
	/*
	Column Matrix

	|0  4  8  12|
	|1  5  9  13|
	|2  6  10 14|
	|3  7  11 15|

	Rx = Vx*M0+Vy*M4+Vz*M8+Vh*M12... etc

	*/
	float x = get_x(left)*right.m[0] + get_y(left)*right.m[4] + get_z(left)*right.m[8]  + get_h(left)*right.m[12];
	float y = get_x(left)*right.m[1] + get_y(left)*right.m[5] + get_z(left)*right.m[9]  + get_h(left)*right.m[13];
	float z = get_x(left)*right.m[2] + get_y(left)*right.m[6] + get_z(left)*right.m[10] + get_h(left)*right.m[14];
	float w = get_x(left)*right.m[3] + get_y(left)*right.m[7] + get_z(left)*right.m[11] + get_h(left)*right.m[15];

	return uti::make(x, y, z, w);
}

float44 uti::operator*(float44 left, float44 right)
{
	return mul(left, right);
}

float4  uti::operator*(float4  left, float44 right)
{
	return mul(left, right);
}
