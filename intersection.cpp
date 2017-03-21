#include "stdafx.h"

#include "intersection.h"
#include "primatives.h"
#include "float4.h"

namespace uti
{
	// TODO: [DanJ] Delete this one
	bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos, float4* norm)
	{
		return ray_vs_sphere(ray, sphere.pos, sphere.radius, pos, norm);
	}

	bool ray_vs_sphere(const Ray& ray, const float4& sphere_pos, float sphere_radius, float4* pos, float4* norm)
	{
		float4 diff = ray.dir - ray.origin;
		float4 diff2 = ray.origin - sphere_pos;

		float a = uti::get_x(uti::dot(diff, diff));
		float b = uti::get_x(uti::dot(2 * diff, diff2));
		float c = uti::get_x(uti::dot(sphere_pos, sphere_pos)) + uti::get_x(uti::dot(ray.origin, ray.origin)) + -2 * uti::get_x(uti::dot(sphere_pos, ray.origin)) - sphere_radius*sphere_radius;

		float dis = b*b - 4 * a * c;

		if (dis < 0)
			return false;
		else if (pos == nullptr && norm == nullptr)
			return true;

		float4 test = uti::make(dis, dis, dis, dis);
		test = _mm_sqrt_ss(test);
		float t = (-b - uti::get_x(test)) / 2.0f * a;

		*pos = ray.origin + t * diff;
		*norm = uti::norm((*pos - sphere_pos) / sphere_radius);

		return true;
	}

	bool ray_vs_plane(float4 ray_pos, float4 ray_dir, float4 plane_normal, float4 plane_pos, float4* pos)
	{
		float ndp = uti::get_x(uti::dot(plane_normal, ray_dir));
		if (ndp != 0.0f)
		{
			float4 rayToPlane = plane_pos - ray_pos;
			float t = uti::get_x(uti::dot(rayToPlane, plane_normal)) / ndp;
			if (t >= 0.0f)
			{
				if (pos != nullptr)
					*pos = ray_pos + t * ray_dir;

				return true;
			}
		}

		return false;
	}

	bool ray_test_bounds(const Ray& ray, model_bounds* bounds, const float44& xform, float4* hit_pos_out)
	{
		float4 xform_pos = make(xform.m[12], xform.m[13], xform.m[14], 1.0f);
		if (bounds->type == model_bounds_type::sphere)
		{
			return uti::ray_vs_sphere(ray, xform_pos, bounds->sphere.radius);
		}
		else if (bounds->type == model_bounds_type::axis_aligned_box)
		{
			float4 ray_origin = ray.origin - xform_pos;

			{
				float4 plane_pos = {};
				float4 plane_norm = {};

				// Top
				plane_pos = make(0.0f, bounds->aabox.top, 0.0f);
				plane_norm = make(0.0f, 1.0f, 0.0f);

				float4 hit_pos = {};
				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_x = get_x(hit_pos);
					float hit_z = get_z(hit_pos);

					if (!( hit_x > bounds->aabox.right || hit_x < bounds->aabox.left
						|| hit_z > bounds->aabox.back || hit_z < bounds->aabox.front))
					{
						return true;
					}
				}

				// Bottom
				plane_pos = make(0.0f, bounds->aabox.bottom, 0.0f);
				plane_norm = make(0.0f, -1.0f, 0.0f);

				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_x = get_x(hit_pos);
					float hit_z = get_z(hit_pos);

					if (!( hit_x > bounds->aabox.right || hit_x < bounds->aabox.left
						|| hit_z > bounds->aabox.back || hit_z < bounds->aabox.front))
					{
						return true;
					}
				}

				// Front
				plane_pos = make(0.0f, 0.0f, bounds->aabox.front);
				plane_norm = make(0.0f, 0.0f, -1.0f);

				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_x = get_x(hit_pos);
					float hit_y = get_y(hit_pos);

					if (!( hit_x > bounds->aabox.right || hit_x < bounds->aabox.left
						|| hit_y > bounds->aabox.top || hit_y < bounds->aabox.bottom))
					{
						return true;
					}
				}

				// Back
				plane_pos = make(0.0f, 0.0f, bounds->aabox.back);
				plane_norm = make(0.0f, 0.0f, 1.0f);

				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_x = get_x(hit_pos);
					float hit_y = get_y(hit_pos);

					if (!( hit_x > bounds->aabox.right || hit_x < bounds->aabox.left
						|| hit_y > bounds->aabox.top || hit_y < bounds->aabox.bottom))
					{
						return true;
					}
				}

				// Left
				plane_pos = make(-bounds->aabox.left, 0.0f, 0.0f);
				plane_norm = make(-1.0f, 0.0f, 0.0f);

				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_y = get_y(hit_pos);
					float hit_z = get_z(hit_pos);

					if (!( hit_y > bounds->aabox.top || hit_y < bounds->aabox.bottom
						|| hit_z > bounds->aabox.back || hit_z < bounds->aabox.front))
					{
						return true;
					}
				}

				// Right
				plane_pos = make(bounds->aabox.right, 0.0f, 0.0f);
				plane_norm = make(1.0f, 0.0f, 0.0f);

				if (ray_vs_plane(ray_origin, ray.dir, plane_norm, plane_pos, &hit_pos))
				{
					if (hit_pos_out != nullptr)
						*hit_pos_out = xform_pos + hit_pos;

					float hit_y = get_y(hit_pos);
					float hit_z = get_z(hit_pos);

					if (!( hit_y > bounds->aabox.top || hit_y < bounds->aabox.bottom
						|| hit_z > bounds->aabox.back || hit_z < bounds->aabox.front))
					{
						return true;
					}
				}

				return false;
			}

		}

		return false;
	}
}
