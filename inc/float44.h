#pragma once

namespace uti
{
	TAT_DEF float44 make(float4 c0, float4 c1, float4 c2, float4 c3);
	TAT_DEF float44 make(float* values, uti::u32 num_values);
	TAT_DEF float44 make_identity();
	TAT_DEF float44 make_scale(float scale);
	TAT_DEF float44 make_scale(float xs, float ys, float zs);
	TAT_DEF float44 make_rotate_x(float rads);
	TAT_DEF float44 make_rotate_y(float rads);
	TAT_DEF float44 make_rotate_z(float rads);
	TAT_DEF float44 make_translate(float4 offset);
	TAT_DEF float44 make_translate(float xt, float yt, float zt);
	TAT_DEF float44 make_look_at(const float4& pos, const float4& at, const float4& up);
	TAT_DEF float44 make_projection(float aspect, float min_dist, float max_dist, float hfov);
	TAT_DEF float44 make_transposed(const float44& o);

	TAT_DEF float44 mul(float44 left, float44 right);
	TAT_DEF float4  mul(float4 left, float44 right);
	TAT_DEF float44 operator*(float44 left, float44 right);
	TAT_DEF float4  operator*(float4  left, float44 right);
}
