#pragma once

namespace uti
{
	/*	
		Column Matrix

		|0  4  8  12|
		|1  5  9  13|
		|2  6  10 14|
		|3  7  11 15|
	*/

	TAT_DEF float44 make(const float4& c0, const float4& c1, const float4& c2, const float4& c3);
	TAT_DEF float44 make(float* values, uti::u32 num_values);
	TAT_DEF float44 make_identity();
	TAT_DEF float44 make_scale(float scale);
	TAT_DEF float44 make_scale(float xs, float ys, float zs);
	TAT_DEF float44 make_rotate_x(float rads);
	TAT_DEF float44 make_rotate_y(float rads);
	TAT_DEF float44 make_rotate_z(float rads);
	TAT_DEF float44 make_rotate(float4 rads);
	TAT_DEF float44 make_rotate(float x, float y, float z);
	TAT_DEF float44 make_translate(const float4& offset);
	TAT_DEF float44 make_translate(float xt, float yt, float zt);
	TAT_DEF float44 make_look_at(const float4& pos, const float4& at, const float4& up);
	TAT_DEF float44 make_inverse_look_at(const float4& pos, const float4& at, const float4& up);
	TAT_DEF float44 make_projection(float aspect, float min_dist, float max_dist, float hfov);
	TAT_DEF float44 make_transposed(const float44& o);

	TAT_DEF float44 mul(const float44& left, const float44& right);
	TAT_DEF float4  mul(const float44& right,const float4 & left);
	TAT_DEF float44 operator*(const float44& left,  const float44& right);
	TAT_DEF float4  operator*(const float44& right, const float4 & left);
	TAT_DEF float44 operator*(const float  & left,  const float44& right);

	TAT_DEF float determinant_33(const float44& in);
	TAT_DEF void inverse_33(const float44& in, float44* out);
	TAT_DEF void clear_to_33(float44* in_out);
	TAT_DEF float determinant(const float44& in);
	TAT_DEF void inverse(const float44& in, float44* out);

	TAT_DEF void get_pos_only(const float44& in, float44* out);
}
