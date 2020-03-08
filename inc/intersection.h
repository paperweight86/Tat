#pragma once

#include "primatives.h"

namespace uti
{
	enum mesh_bounds_type : u8
	{
		none,
		sphere,
		aa_sphere_segment,
		sphere_segment,
		aa_box
	};

	enum plane_position : u8
	{
		plane_position_infront,
		plane_position_behind,
		plane_position_inside
	};

	struct bounds_sphere { float radius; };
	struct bounds_sphere_segment { float radius; float start; float end; axis in_axis; };
	struct bounds_aabox { float right; float left; float top; float bottom; float front; float back; };

	struct mesh_bounds
	{
		mesh_bounds_type type;
		union
		{
			bounds_sphere sphere;
			bounds_sphere_segment sphere_segment;
			bounds_aabox aabox;
		};
	};

	TAT_DEF bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos = nullptr, float4* norm = nullptr);

	TAT_DEF bool ray_vs_sphere(const Ray& ray, const float4& sphere_pos, float sphere_radius, float4* pos = nullptr, float4* norm = nullptr, float4* tan = nullptr);

	TAT_DEF bool ray_vs_plane(float4 ray_pos, float4 ray_dir, float4 plane_normal, float4 plane_pos, float4* pos = nullptr);

	TAT_DEF bool ray_test_bounds(const Ray& ray, mesh_bounds* bounds, const float44& xform, float4* hit_pos_out = nullptr, float4* hit_norm_out = nullptr, float4* hit_tan_out = nullptr);

	TAT_DEF bool ray_vs_sphere_segment(const Ray& ray, mesh_bounds* bounds, const float44& xform, float4* hit_pos_out = nullptr, float4* hit_norm_out = nullptr, float4* hit_tan_out = nullptr);

	TAT_DEF plane_position point_vs_plane(float4 point, float4 plane_normal, float4 plane_pos);

	TAT_DEF void project_point_plane(float4 point, float4 plane_normal, float4 plane_pos, float4* proj_point);
}
