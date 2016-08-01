#include "stdafx.h"

#include "intersection.h"
#include "primatives.h"
#include "float4.h"

namespace uti
{
	bool rayVsSphere(const Ray& ray, const Sphere& sphere, float4* pos, float4* normal)
	{
		float4 diff = ray.dir - ray.origin;
		float4 diff2 = ray.origin - sphere.pos;

		float a = uti::get_x(uti::dot(diff, diff));
		float b = uti::get_x(uti::dot(2 * diff, diff2));
		float c = uti::get_x(uti::dot(sphere.pos, sphere.pos)) + uti::get_x(uti::dot(ray.origin, ray.origin)) + -2 * uti::get_x(uti::dot(sphere.pos, ray.origin)) - powf(sphere.radius,2.0f);

		float dis = b*b - 4 * a * c;

		if (dis < 0)
			return false;
		else if (pos == nullptr && normal == nullptr)
			return true;

		float4 test = uti::make(dis, dis, dis, dis);
		test = _mm_sqrt_ss(test);
		float t = (-b - uti::get_x(test)) / 2.0f * a;

		*pos = ray.origin + t * diff;
		*normal = uti::norm((*pos - sphere.pos) / sphere.radius);

		return true;
	}
}
