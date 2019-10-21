#pragma once

namespace uti
{
	struct quaternion
	{
		float4 data;
		TAT_DEF quaternion();
		TAT_DEF quaternion(float4 data);
		TAT_DEF uti::quaternion operator+(const uti::quaternion& right) const;
		TAT_DEF uti::quaternion operator*(const uti::quaternion& right) const;
	};

	TAT_DEF quaternion make_quaternion_identity();

	TAT_DEF quaternion make_quaternion(float angle, float axis_x, float axis_y, float axis_z);

	TAT_DEF quaternion make_quaternion(float angle, float4 axis);

	TAT_DEF quaternion make_quaternion(float w);

	TAT_DEF quaternion make_quaternion_direct(float w, float x, float y, float z);

	TAT_DEF float44 quaternion_as_matrix(const uti::quaternion& q);

	TAT_DEF quaternion quaternion_conjugate(const uti::quaternion& q);

	TAT_DEF float quaternion_modulus(const uti::quaternion& q);

	TAT_DEF quaternion quaternion_inverse(const uti::quaternion& q);

	TAT_DEF quaternion quaternion_combine(const uti::quaternion& a, const uti::quaternion b);
}
