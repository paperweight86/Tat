#include "stdafx.h"

#include "quaternion.h"
#include "float4.h"
#include "float44.h"

uti::quaternion::quaternion() : data(make_float4(0.0f,0.0f,0.0f))
{
}

uti::quaternion::quaternion(float4 _data) : data(_data)
{
}

uti::quaternion uti::make_quaternion_identity()
{
	return quaternion();
}

uti::quaternion uti::make_quaternion(float angle, float axis_x, float axis_y, float axis_z)
{
	float sinthetadiv2 = sinf(angle / 2.0f);
	float costhetadiv2 = cosf(angle / 2.0f);
	return quaternion{ uti::make_float4(axis_x * sinthetadiv2, axis_y * sinthetadiv2, axis_z * sinthetadiv2, costhetadiv2) };
}

uti::quaternion uti::make_quaternion(float angle, float4 axis)
{
	float sinthetadiv2 = sinf(angle / 2.0f);
	float costhetadiv2 = cosf(angle / 2.0f);
	return quaternion{ uti::make_float4(get_x(axis) * sinthetadiv2, get_y(axis) * sinthetadiv2, get_z(axis) * sinthetadiv2, costhetadiv2) };
}

uti::quaternion uti::make_quaternion(float w)
{
	return quaternion{ uti::make_float4(0.0f,0.0f,0.0f,w) };
}

uti::quaternion uti::make_quaternion_direct(float w, float x, float y, float z)
{
	return quaternion{ uti::make_float4_ordered(w,x,y,z) };
}

uti::float44 uti::quaternion_as_matrix(const uti::quaternion& q)
{
	float44 m = {};
	m.m[15] = 1.0f;

	float qx = get_x(q.data);
	float qy = get_y(q.data);
	float qz = get_z(q.data);
	float qw = get_h(q.data);

	m.m[0] = 1-2*qy*qy - 2*qz*qz;
	m.m[1] = 2*qx*qy + 2*qz*qw;
	m.m[2] = 2*qx*qz - 2*qy*qw;

	m.m[4] = 2*qx*qy - 2*qz*qw;
	m.m[5] = 1-2*qx*qx - 2*qz*qz;
	m.m[6] = 2*qy*qz + 2*qx*qw;

	m.m[8 ] = 2*qx*qz + 2*qy*qw;
	m.m[9 ] = 2*qy*qz - 2*qx*qw;
	m.m[10] = 1-2*qx*qx - 2*qy*qy;

	return m;
}

uti::quaternion uti::quaternion_conjugate(const uti::quaternion& q)
{
	quaternion i = make_quaternion_direct(0, 1, 0, 0);
	quaternion j = make_quaternion_direct(0, 0, 1, 0);
	quaternion k = make_quaternion_direct(0, 0, 0, 1);

	quaternion p = i * j;

	return make_quaternion(-0.5f) * (q + i * q * i + j * q * j + k * q * k);
}

float uti::quaternion_modulus(const uti::quaternion& q)
{
	quaternion sq = q * quaternion_conjugate(q);
	return sqrtf(get_h(sq.data) + get_x(sq.data) + get_y(sq.data) + get_z(sq.data));
}

uti::quaternion uti::quaternion_inverse(const uti::quaternion& q)
{
	float mod = quaternion_modulus(q);
	quaternion sqmod = make_quaternion(mod * mod);
	quaternion conj = quaternion_conjugate(q);
	return conj * sqmod;
}

uti::quaternion uti::quaternion_combine(const uti::quaternion& a, const uti::quaternion b)
{
	return (b * a) * quaternion_conjugate(b * a);
}

uti::quaternion uti::quaternion::operator+(const uti::quaternion& right) const
{
	return uti::quaternion{ data + right.data };
}

uti::quaternion uti::quaternion::operator*(const uti::quaternion& right) const
{
	quaternion result = {};

	float rx, ry, rz, rw;
	float ax, ay, az, aw;
	ax = uti::get_x(data);
	ay = uti::get_y(data);
	az = uti::get_z(data);
	aw = uti::get_h(data);
	float bx, by, bz, bw;
	bx = uti::get_x(right.data);
	by = uti::get_y(right.data);
	bz = uti::get_z(right.data);
	bw = uti::get_h(right.data);

	////rw = bw*az - bx*ay + by*ax + bz*aw;
	////rx = bw*aw - bx*ax - by*ay - bz*az;
	////ry = bw*ax + bx*aw - by*az + bz*ay;
	////rz = bw*ay + bx*az + by*aw - bz*ax;

	//rw = aw * bw - ax * bx - ay * by - az * bz;
	//rx = aw * bx + ax * bw + ay * bz - az * by;
	//ry = aw * by - ax * bz + ay * bw + az * bx;
	//rz = aw * bz + ax * by - ay * bx + az * bw;

	//return quaternion{ uti::make_float4(rx,ry,rz,rw) };

	float4 final = uti::cross(data, right.data) + make_float4(aw) * right.data + make_float4(bw) * data;
	rx = get_x(final);
	ry = get_y(final);
	rz = get_z(final);
	rw = aw * bw - uti::get_x(uti::dot(data, right.data));

	return quaternion{ uti::make_float4(rx,ry,rz,rw) };
}
