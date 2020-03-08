#include "stdafx.h"

#include "intersection.h"
#include "primatives.h"
#include "float4.h"
#include "float44.h"

namespace uti
{
	// TODO: [DanJ] Delete this one
	bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos, float4* norm)
	{
		return ray_vs_sphere(ray, sphere.pos, sphere.radius, pos, norm);
	}

	bool ray_vs_sphere(const Ray& ray, const float4& sphere_pos, float sphere_radius, float4* pos, float4* norm, float4* tan)
	{
		float4 diff = ray.dir; // - ray.origin
		float4 diff2 = ray.origin - sphere_pos;

		float a = uti::get_x(uti::dot(diff, diff));
		float b = uti::get_x(uti::dot(uti::make_float4(2.0f) * diff, diff2));
		float c = uti::get_x(uti::dot(sphere_pos, sphere_pos)) + uti::get_x(uti::dot(ray.origin, ray.origin)) + -2 * uti::get_x(uti::dot(sphere_pos, ray.origin)) - sphere_radius*sphere_radius;

		float dis = b*b - 4 * a * c;

		if (dis < 0)
			return false;
		else if (pos == nullptr && norm == nullptr && tan == nullptr)
			return true;

		float4 test = uti::make_float4(dis, dis, dis, dis);
		test = _mm_sqrt_ss(test);
		float t = (-b - uti::get_r0(test)) / 2.0f * a;

		if (pos != nullptr)
			*pos = ray.origin + uti::make_float4(t) * ray.dir;
		if(norm != nullptr)
			*norm = uti::norm((*pos - sphere_pos) / uti::make_float4(sphere_radius));
		if (tan != nullptr)
		{
			// TODO: [DanJ] This doesn't seem entirely correct
			float4 inter = uti::norm(*pos - uti::make_float4(-get_y(*pos), get_x(*pos), 0.0f));
			if (norm != nullptr)
				*tan = uti::norm(cross(inter, *norm));
			else
				*tan = uti::norm(cross(inter, uti::norm((*pos - sphere_pos) / uti::make_float4(sphere_radius))));
		}

		return true;
	}

	bool ray_vs_plane(float4 ray_pos, float4 ray_dir, float4 plane_normal, float4 plane_pos, float4* pos)
	{
		float4 ndp = uti::dot(plane_normal, ray_dir);
		if (uti::get_x(ndp) != 0.0f)
		{
			float4 rayToPlane = plane_pos - ray_pos;
			float4 rtpdn = uti::dot(rayToPlane, plane_normal);
			float4 t = rtpdn / ndp;
			if (uti::get_x(t) >= 0.0f)
			{
				if (pos != nullptr)
					*pos = ray_pos + t * ray_dir;

				return true;
			}
		}

		return false;
	}

	bool ray_test_bounds(const Ray& ray, mesh_bounds* bounds, const float44& xform, float4* hit_pos_out, float4* hit_norm_out, float4* hit_tan_out)
	{
		float4 xform_pos = make_float4(xform.m[12], xform.m[13], xform.m[14], 1.0f);
		if (bounds->type == mesh_bounds_type::sphere)
		{
			return uti::ray_vs_sphere(ray, xform_pos, bounds->sphere.radius);
		}
		else if (  bounds->type == mesh_bounds_type::sphere_segment
				|| bounds->type == mesh_bounds_type::aa_sphere_segment)
		{
			return uti::ray_vs_sphere_segment(ray, bounds, xform, hit_pos_out, hit_norm_out, hit_tan_out);
		}
		else if (bounds->type == mesh_bounds_type::aa_box)
		{
			float4 ray_origin = ray.origin - xform_pos;

			{
				// Top
				float4 plane_pos = make_float4(0.0f, bounds->aabox.top, 0.0f);
				float4 plane_norm = make_float4(0.0f, 1.0f, 0.0f);

				float4 hit_pos = uti::make_float4(0.0f,0.0f,0.0f);
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
				plane_pos = make_float4(0.0f, bounds->aabox.bottom, 0.0f);
				plane_norm = make_float4(0.0f, -1.0f, 0.0f);

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
				plane_pos = make_float4(0.0f, 0.0f, bounds->aabox.front);
				plane_norm = make_float4(0.0f, 0.0f, -1.0f);

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
				plane_pos = make_float4(0.0f, 0.0f, bounds->aabox.back);
				plane_norm = make_float4(0.0f, 0.0f, 1.0f);

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
				plane_pos = make_float4(-bounds->aabox.left, 0.0f, 0.0f);
				plane_norm = make_float4(-1.0f, 0.0f, 0.0f);

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
				plane_pos = make_float4(bounds->aabox.right, 0.0f, 0.0f);
				plane_norm = make_float4(1.0f, 0.0f, 0.0f);

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

	bool ray_vs_sphere_segment(const Ray& ray, mesh_bounds* bounds, const float44& xform, float4* hit_pos_out, float4* hit_norm_out, float4* hit_tan_out)
	{
		float4 xform_pos = make_float4(xform.m[12], xform.m[13], xform.m[14], 1.0f);
		if (bounds->type == mesh_bounds_type::aa_sphere_segment)
		{
			if (ray_vs_sphere(ray, xform_pos, bounds->sphere_segment.radius, hit_pos_out, hit_norm_out, hit_tan_out))
			{
				float4 plane_norm = uti::make_float4_zero();
				float shift_start = 0.0f;
				float shift_end = 0.0f;
				if (bounds->sphere_segment.in_axis == axis_x)
				{
					shift_start = uti::get_x(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					shift_end = uti::get_x(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;
					if (shift_start > uti::get_x(*hit_pos_out))
						return false;

					if (shift_end < uti::get_x(*hit_pos_out))
						return false;

					return true;
				}
				else if (bounds->sphere_segment.in_axis == axis_y)
				{
					shift_start = uti::get_y(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					shift_end = uti::get_y(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;
					if (shift_start > uti::get_y(*hit_pos_out))
						return false;

					if (shift_end < uti::get_y(*hit_pos_out))
						return false;

					return true;
				}
				else if (bounds->sphere_segment.in_axis == axis_z)
				{
					shift_start = uti::get_z(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					shift_end = uti::get_z(xform_pos) - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;
					if (shift_start > uti::get_z(*hit_pos_out))
						return false;

					if (shift_end < uti::get_z(*hit_pos_out))
						return false;

					return true;
				}
			}
		}
		else if (bounds->type == mesh_bounds_type::sphere_segment)
		{
			// TODO: [DanJ] Construct planes to test against by using the inverse transpose of the xform to move the normals/point-in-plane
			if (ray_vs_sphere(ray, xform_pos, bounds->sphere_segment.radius, hit_pos_out, hit_norm_out, hit_tan_out))
			{
				float4 shift_start = make_float4_zero();
				float4 shift_end = make_float4_zero();
				float4 start_norm = make_float4_zero();
				float4 end_norm = make_float4_zero();
				if (bounds->sphere_segment.in_axis == axis_x)
				{
					float shift_start_x = - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					float shift_end_x = - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;

					shift_start = xform * make_float4(shift_start_x, 0.0f, 0.0f);
					shift_end	= xform * make_float4(shift_end_x,	  0.0f, 0.0f);

					float44 inv_trans_xform = make_identity();
					inverse(xform, &inv_trans_xform);
					inv_trans_xform = make_transposed(inv_trans_xform);
					start_norm	= inv_trans_xform * make_float4(-1.0f, 0.0f, 0.0f);
					end_norm	= inv_trans_xform * make_float4( 1.0f, 0.0f, 0.0f);

					plane_position start_res = point_vs_plane(*hit_pos_out, start_norm, shift_start);
					if (start_res == plane_position_infront)
						return false;
					plane_position end_res = point_vs_plane(*hit_pos_out, end_norm, shift_end);
					if (end_res == plane_position_infront)
						return false;

					return true;
				}
				else if (bounds->sphere_segment.in_axis == axis_y)
				{
					float shift_start_y = - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					float shift_end_y = - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;

					shift_start = xform * make_float4(0.0f, shift_start_y, 0.0f);
					shift_end	= xform * make_float4(0.0f, shift_end_y,   0.0f);

					float44 inv_trans_xform = make_identity();
					inverse(xform, &inv_trans_xform);
					inv_trans_xform = make_transposed(inv_trans_xform);
					start_norm = inv_trans_xform * make_float4(0.0f, -1.0f, 0.0f);
					end_norm = inv_trans_xform * make_float4(0.0f, 1.0f, 0.0f);

					plane_position start_res = point_vs_plane(*hit_pos_out, start_norm, shift_start);
					if (start_res == plane_position_infront)
						return false;
					plane_position end_res = point_vs_plane(*hit_pos_out, end_norm, shift_end);
					if (end_res == plane_position_infront)
						return false;

					return true;
				}
				else if (bounds->sphere_segment.in_axis == axis_z)
				{
					float shift_start_z = - bounds->sphere_segment.radius + bounds->sphere_segment.start * bounds->sphere_segment.radius * 2.0f;
					float shift_end_z = - bounds->sphere_segment.radius + bounds->sphere_segment.end * bounds->sphere_segment.radius * 2.0f;

					shift_start  = xform * make_float4(0.0f, 0.0f, shift_start_z);
					shift_end	 = xform * make_float4(0.0f, 0.0f, shift_end_z);

					float44 inv_trans_xform = make_identity();
					inverse(xform, &inv_trans_xform);
					inv_trans_xform = make_transposed(inv_trans_xform);
					start_norm = inv_trans_xform * make_float4(0.0f, 0.0f, -1.0f);
					end_norm = inv_trans_xform * make_float4(0.0f, 0.0f, 1.0f);

					plane_position start_res = point_vs_plane(*hit_pos_out, start_norm, shift_start);
					if (start_res == plane_position_infront)
						return false;
					plane_position end_res = point_vs_plane(*hit_pos_out, end_norm, shift_end);
					if (end_res == plane_position_infront)
						return false;

					return true;
				}
			}
		}

		return false;
	}

	plane_position point_vs_plane(float4 point, float4 plane_normal, float4 plane_pos)
	{
		float dot_prod = uti::get_x(dot(point - plane_pos, plane_normal));

		if (fabs(dot_prod) <= float_epsilon)
			return plane_position_inside;
		else if (dot_prod > float_epsilon)
			return plane_position_infront;
		else// if (dot_prod < float_epsilon)
			return plane_position_behind;
	}

	void project_point_plane(float4 point, float4 plane_normal, float4 plane_pos, float4* proj_point)
	{
		float4 v = point - plane_pos;
		float dist = get_x(dot(v, plane_normal));
		*proj_point = point - uti::make_float4(dist)*plane_normal;
	}
}
