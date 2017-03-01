#pragma once

namespace uti
{
	TAT_DEF float4 make(float x, float y, float z, float h = 1.0f);
	TAT_DEF float4 make_ordered(float r0, float r1, float r2, float r3);
	TAT_DEF float4 make_f4_zero();
	TAT_DEF float get_x(float4 v);
	TAT_DEF float get_y(float4 v);
	TAT_DEF float get_z(float4 v);
	TAT_DEF float get_h(float4 v);

	TAT_DEF float4 dot(const float4& left, const float4& right);
	TAT_DEF float4 cross(const float4& left, const float4& right);

	TAT_DEF float  len(float4 vec);
	TAT_DEF float  sqlen(float4 vec);
	TAT_DEF float4 norm(float4 vec);
};

TAT_DEF uti::float4 operator-(const uti::float4& left, const uti::float4& right);
TAT_DEF uti::float4 operator+(const uti::float4& left, const uti::float4& right);
TAT_DEF uti::float4 operator*(const uti::float4& left, const uti::float4& right);
TAT_DEF uti::float4 operator*(uti::float4 left, float right);
TAT_DEF uti::float4 operator*(float left, uti::float4 right);
TAT_DEF uti::float4 operator/(const uti::float4& left, const uti::float4& right);
TAT_DEF uti::float4 operator/(uti::float4 left, float right);
