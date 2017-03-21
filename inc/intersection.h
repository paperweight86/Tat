#pragma once

#include "primatives.h"

namespace uti
{
	enum model_bounds_type : u8
	{
		sphere,
		axis_aligned_box
	};

	struct model_bounds
	{
		model_bounds_type type;
		union
		{
			struct _sphere { float radius; } sphere;
			struct _aabox { float right; float left; float top; float bottom; float front; float back; } aabox;
		};
	};

	TAT_DEF bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos = nullptr, float4* norm = nullptr);

	TAT_DEF bool ray_vs_sphere(const Ray& ray, const float4& sphere_pos, float sphere_radius, float4* pos = nullptr, float4* norm = nullptr);

	TAT_DEF bool ray_vs_plane(float4 ray_pos, float4 ray_dir, float4 plane_normal, float4 plane_pos, float4* pos = nullptr);

	TAT_DEF bool ray_test_bounds(const Ray& ray, model_bounds* bounds, const float44& xform, float4* hit_pos_out = nullptr);
}
